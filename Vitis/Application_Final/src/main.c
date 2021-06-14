
#include "subsystemDef.h"

// Miscellaneous function definitions
int init_intr_controller();
int init_filter();
int process_image();
int check_idle(u32 baseAddress, u32 offset);

// Define ISRs
static void image_proc_isr();
static void dma_receive_isr();

/*
 * Back-end subsystem interface
 */
int main() {

	int status;

	// Initialize state
	nextState = idle_state;

	// Enable data cache
	Xil_DCacheEnable();

	// ************************************************GPIO Config************************************************

	// Initialize GPIO
    status = init_gpio();
    if (status != XST_SUCCESS) { return status; }

    // Configure OLED
	OLED_Begin(&myDevice, XPAR_PMODOLED_0_AXI_LITE_GPIO_BASEADDR, XPAR_PMODOLED_0_AXI_LITE_SPI_BASEADDR, 0x0, 0x0);

    // ************************************************GPIO Config************************************************


	// ************************************************UART Config************************************************

    // Define XUartPs variables
	XUartPs uart;
	XUartPs_Config *uartConfig;

	// Configure UART
	uartConfig = XUartPs_LookupConfig(XPAR_PS7_UART_1_DEVICE_ID);

	// Initialize UART
	status = XUartPs_CfgInitialize(&uart, uartConfig, uartConfig->BaseAddress);
	if (status != XST_SUCCESS) { return status;}

	// Configure baud rate
	status = XUartPs_SetBaudRate(&uart, baudRate);
	if (status != XST_SUCCESS) { return status; }

	// ************************************************UART Config************************************************


	// ************************************************DMA Config************************************************

    // Initialize DMA and Image Filter
    status = init_intr_controller();
    if (status != XST_SUCCESS) { return status; }

    status = init_filter();
    if (status != XST_SUCCESS) { return status; }

    // ************************************************DMA Config************************************************


    // ************************************************VDMA Config************************************************

    // Initialize VDMA Engine
    status = init_vdma();
    if (status != XST_SUCCESS) { return status; }

	status = vdma_start();
	if (status != XST_SUCCESS) { return status; }

	// ************************************************VDMA Config************************************************

	// Initialize configuration variables
	u8 mode = 2;
	int numFrames = 1;
	float distanceThreshold = 0.0f;

	// Finite state machine
	while (1) {

		OLED_ClearBuffer(&myDevice);
		OLED_SetCursor(&myDevice, 0, 0);

		// Monitor nextState
		switch (nextState) {

			// In idle_state, wait for button1 to be pressed
			case idle_state:
				OLED_PutString(&myDevice, "-Idle State-");
				nextState = idle_state_handler(uartConfig, mode);
				break;

			// In config_state, allow the user to configure the system
			case config_state:
				OLED_PutString(&myDevice, "-Config State-");
				nextState = config_state_handler(uartConfig, &mode, &numFrames, &distanceThreshold);
				break;

			// In init_state, wait for RPi to initialize
			case init_state:
				OLED_PutString(&myDevice, "-Init State-");
				nextState = init_state_handler(uartConfig, numFrames);
				break;

			// In the collect_state, wait for the RPi to send all frames
			case collect_dist:
				OLED_PutString(&myDevice, "-Collect State-");
				nextState = collect_dist_state_handler(&uart, uartConfig, numFrames);
				break;

			// In the collect_state, wait for the RPi to send all frames
			case collect_image:
				OLED_PutString(&myDevice, "-Collect State-");
				nextState = collect_image_state_handler(&uart, uartConfig, numFrames);
				break;

			// In start_state, continuously read and store RPi data
			case start_state:
				OLED_PutString(&myDevice, "-Stream State-");
				nextState = start_state_handler(&uart, uartConfig, numFrames, distanceThreshold);
				break;

			// In stop_state, wait for button1 or button2 to be pressed
			case stop_state:
				OLED_PutString(&myDevice, "-Pause State-");
				nextState = stop_state_handler(uartConfig);
				break;

			// In end_state, wait for RPi to terminate
			case end_state:
				OLED_PutString(&myDevice, "-End State-");
				nextState = end_state_handler(uartConfig);
				break;

			default:
				break;
		}

		// Sleep between states
		if (nextState == config_state || nextState == stop_state || (nextState == start_state && XGpio_DiscreteRead(&switch0, 1) == 1)) {
			usleep(100000);
		} else {
			usleep(25000);
		}
	}

    return 0;
}

/**
 * Function for initializing the interrupt controller
 */
int init_intr_controller() {
	int status;
	XScuGic_Config *IntcConfig;
	IntcConfig = XScuGic_LookupConfig(XPAR_PS7_SCUGIC_0_DEVICE_ID);
	status =  XScuGic_CfgInitialize(&intcInstance, IntcConfig, IntcConfig->CpuBaseAddress);
	if(status != XST_SUCCESS){ return status; }

	Xil_ExceptionInit();
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT, (Xil_ExceptionHandler) XScuGic_InterruptHandler, (void *) &intcInstance);
	Xil_ExceptionEnable();

	return XST_SUCCESS;
}

/**
 * Function for initializing the filter IP
 */
int init_filter() {
	// Define XAxiDma variables
	int status;
	XAxiDma_Config *dmaConfig;

    //DMA Controller Configuration
	dmaConfig = XAxiDma_LookupConfigBaseAddr(XPAR_AXI_DMA_0_BASEADDR);
	status = XAxiDma_CfgInitialize(&dma, dmaConfig);
	if(status != XST_SUCCESS){ return status; }

	XAxiDma_IntrEnable(&dma, XAXIDMA_IRQ_IOC_MASK, XAXIDMA_DEVICE_TO_DMA);

	// Configure ISR when image filter is done with processing data
	XScuGic_SetPriorityTriggerType(&intcInstance, XPAR_FABRIC_IMAGEPROCESSTOP_0_O_INTR_INTR, 0x8, 0x3);

	status = XScuGic_Connect(&intcInstance, XPAR_FABRIC_IMAGEPROCESSTOP_0_O_INTR_INTR, (Xil_InterruptHandler) image_proc_isr, 0);
	if(status != XST_SUCCESS){ return status; }

	XScuGic_Enable(&intcInstance, XPAR_FABRIC_IMAGEPROCESSTOP_0_O_INTR_INTR);

	// Configure ISR when data is received by DMA
	XScuGic_SetPriorityTriggerType(&intcInstance, XPAR_FABRIC_AXI_DMA_0_S2MM_INTROUT_INTR, 0x10, 0x3);

	status = XScuGic_Connect(&intcInstance, XPAR_FABRIC_AXI_DMA_0_S2MM_INTROUT_INTR, (Xil_InterruptHandler) dma_receive_isr, 0);
	if(status != XST_SUCCESS){ return status; }

	XScuGic_Enable(&intcInstance, XPAR_FABRIC_AXI_DMA_0_S2MM_INTROUT_INTR);

	return XST_SUCCESS;
}

/**
 * Function to initiate the image filtering process
 */
int process_image() {
	int status;

	imageProcDone = 0;

	Xil_DCacheFlush();

	status = XAxiDma_SimpleTransfer(&dma, (UINTPTR) filteredDataPtr, imageSize, XAXIDMA_DEVICE_TO_DMA);
	if(status != XST_SUCCESS){ return status; }

//	Xil_DCacheFlush();

	status = XAxiDma_SimpleTransfer(&dma, (UINTPTR) frameDataPtr, 4 * imageHorizontalSize, XAXIDMA_DMA_TO_DEVICE);
	if(status != XST_SUCCESS){ return status; }

//	Xil_DCacheFlush();

	return status;
}

/**
 * Check if the DMA controller is idle
 */
int check_idle(u32 baseAddress, u32 offset) {
	int status;
	status = (XAxiDma_ReadReg(baseAddress, offset)) & XAXIDMA_IDLE_MASK;
	return status;
}

/**
 * image_proc_isr is called when the image filter is finished processing one line
 */
static void image_proc_isr() {
	static int i = 4;

	// Temporarily disable interrupt
	XScuGic_Disable(&intcInstance, XPAR_FABRIC_IMAGEPROCESSTOP_0_O_INTR_INTR);

	// Wait until last data transmission is complete
	while (check_idle(XPAR_AXI_DMA_0_BASEADDR, 0x4) == 0) { }

	if (i < (imageVerticalSize + 2)) {
		Xil_DCacheFlush();
		XAxiDma_SimpleTransfer(&dma, (UINTPTR) &frameDataPtr[i * imageHorizontalSize], imageHorizontalSize, XAXIDMA_DMA_TO_DEVICE);
		i += 1;
	}

	// Re-enable interrupt
	XScuGic_Enable(&intcInstance, XPAR_FABRIC_IMAGEPROCESSTOP_0_O_INTR_INTR);
}

/**
 * dma_receive_isr is called when all of the data for a frame has been processed
 */
static void dma_receive_isr() {
	// Temporarily disable interrupt
	XAxiDma_IntrDisable(&dma, XAXIDMA_IRQ_IOC_MASK, XAXIDMA_DEVICE_TO_DMA);

	// Clear interrupt status register
	XAxiDma_IntrAckIrq(&dma, XAXIDMA_IRQ_IOC_MASK, XAXIDMA_DEVICE_TO_DMA);

	// Indicate that image processing is complete
	imageProcDone = 1;

	// Re-enable interrupt
	XAxiDma_IntrEnable(&dma, XAXIDMA_IRQ_IOC_MASK, XAXIDMA_DEVICE_TO_DMA);
}


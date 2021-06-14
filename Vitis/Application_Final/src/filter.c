//
//#include "filter.h"
//
///**
// *
// */
//int initIntrController() {
//	int status;
//	XScuGic_Config *IntcConfig;
//	IntcConfig = XScuGic_LookupConfig(XPAR_PS7_SCUGIC_0_DEVICE_ID);
//	status =  XScuGic_CfgInitialize(&intcInstance, IntcConfig, IntcConfig->CpuBaseAddress);
//	if(status != XST_SUCCESS){ return status; }
//
//	Xil_ExceptionInit();
//	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT, (Xil_ExceptionHandler) XScuGic_InterruptHandler, (void *) &intcInstance);
//	Xil_ExceptionEnable();
//
//	return XST_SUCCESS;
//}
//
///**
// *
// */
//int init_filter() {
//	// Define XAxiDma variables
//	int status;
//	imageProcDone = 0;
//	XAxiDma_Config *dmaConfig;
//	XScuGic_Config *IntcConfig;
//
//	OLED_ClearBuffer(&myDevice);
//	OLED_SetCursor(&myDevice, 0, 0);
//	OLED_PutString(&myDevice, "Inside init_filter");
//
//	//Interrupt Controller Configuration
//	IntcConfig = XScuGic_LookupConfig(XPAR_PS7_SCUGIC_0_DEVICE_ID);
//	status =  XScuGic_CfgInitialize(&intcInstance, IntcConfig, IntcConfig->CpuBaseAddress);
//	if(status != XST_SUCCESS){ return status;}
//
//	OLED_ClearBuffer(&myDevice);
//	OLED_SetCursor(&myDevice, 0, 0);
//	OLED_PutString(&myDevice, "Test1");
//
//    //DMA Controller Configuration
//	dmaConfig = XAxiDma_LookupConfigBaseAddr(XPAR_AXI_DMA_0_BASEADDR);
//	status = XAxiDma_CfgInitialize(&dma, dmaConfig);
//	if(status != XST_SUCCESS){ return XST_FAILURE; }
//
//	OLED_ClearBuffer(&myDevice);
//	OLED_SetCursor(&myDevice, 0, 0);
//	OLED_PutString(&myDevice, "Test2");
//
//	XAxiDma_IntrEnable(&dma, XAXIDMA_IRQ_IOC_MASK, XAXIDMA_DEVICE_TO_DMA);
//
//	OLED_ClearBuffer(&myDevice);
//	OLED_SetCursor(&myDevice, 0, 0);
//	OLED_PutString(&myDevice, "Test3");
//
//	// Configure ISR when image filter is done with processing data
//	XScuGic_SetPriorityTriggerType(&intcInstance, XPAR_FABRIC_IMAGEPROCESSTOP_0_O_INTR_INTR, 0xA0, 0x3);
//
//	OLED_ClearBuffer(&myDevice);
//	OLED_SetCursor(&myDevice, 0, 0);
//	OLED_PutString(&myDevice, "Test4");
//
//	status = XScuGic_Connect(&intcInstance, XPAR_FABRIC_IMAGEPROCESSTOP_0_O_INTR_INTR, (Xil_InterruptHandler) image_proc_isr, 0);
//
//	OLED_ClearBuffer(&myDevice);
//	OLED_SetCursor(&myDevice, 0, 0);
//	OLED_PutString(&myDevice, "Test5");
//
//	if(status != XST_SUCCESS){ return status; }
//
//	OLED_ClearBuffer(&myDevice);
//	OLED_SetCursor(&myDevice, 0, 0);
//	OLED_PutString(&myDevice, "Test5");
//
//	XScuGic_Enable(&intcInstance, XPAR_FABRIC_IMAGEPROCESSTOP_0_O_INTR_INTR);
//
//	OLED_ClearBuffer(&myDevice);
//	OLED_SetCursor(&myDevice, 0, 0);
//	OLED_PutString(&myDevice, "Test6");
//
//	// Configure ISR when data is received by DMA
//	XScuGic_SetPriorityTriggerType(&intcInstance, XPAR_FABRIC_AXI_DMA_0_S2MM_INTROUT_INTR, 0xA8, 0x3);
//
//	OLED_ClearBuffer(&myDevice);
//	OLED_SetCursor(&myDevice, 0, 0);
//	OLED_PutString(&myDevice, "Test7");
//
//	status = XScuGic_Connect(&intcInstance, XPAR_FABRIC_AXI_DMA_0_S2MM_INTROUT_INTR, (Xil_InterruptHandler) dma_receive_isr, 0);
//
//	OLED_ClearBuffer(&myDevice);
//	OLED_SetCursor(&myDevice, 0, 0);
//	OLED_PutString(&myDevice, "Test8");
//
//	if(status != XST_SUCCESS){ return status; }
//
//	OLED_ClearBuffer(&myDevice);
//	OLED_SetCursor(&myDevice, 0, 0);
//	OLED_PutString(&myDevice, "Test9");
//
//	XScuGic_Enable(&intcInstance, XPAR_FABRIC_AXI_DMA_0_S2MM_INTROUT_INTR);
//
//	OLED_ClearBuffer(&myDevice);
//	OLED_SetCursor(&myDevice, 0, 0);
//	OLED_PutString(&myDevice, "Test10");
//
//	// Connect interrupt controller with the PS
//	Xil_ExceptionInit();
//
//	OLED_ClearBuffer(&myDevice);
//	OLED_SetCursor(&myDevice, 0, 0);
//	OLED_PutString(&myDevice, "Test11");
//
//	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT, (Xil_ExceptionHandler) XScuGic_InterruptHandler, (void *) &intcInstance);
//
//	OLED_ClearBuffer(&myDevice);
//	OLED_SetCursor(&myDevice, 0, 0);
//	OLED_PutString(&myDevice, "Test12");
//
//	Xil_ExceptionEnable();
//
//	OLED_ClearBuffer(&myDevice);
//	OLED_SetCursor(&myDevice, 0, 0);
//	OLED_PutString(&myDevice, "Test13");
//
////	// Transfer data from filter IP to DMA controller
////	status = XAxiDma_SimpleTransfer(&dma, (u32) &frameData, imageHorizontalSize * imageVerticalSize, XAXIDMA_DEVICE_TO_DMA);
////	if(status != XST_SUCCESS){ return status; }
////
////	// Transfer data from DMA controller to filter IP
////	status = XAxiDma_SimpleTransfer(&dma, (u32) &imageData, 4 * imageHorizontalSize, XAXIDMA_DMA_TO_DEVICE);
////	if(status != XST_SUCCESS){ return status; }
//
//	return XST_SUCCESS;
//}
//
///**
// *
// */
//int startImageProcessing(){
//	OLED_ClearBuffer(&myDevice);
//	OLED_SetCursor(&myDevice, 0, 0);
//	OLED_PutString(&myDevice, "Inside startImageProcessing");
//
//	int status;
//	status = XAxiDma_SimpleTransfer(&dma, (UINTPTR) filteredData, imageHorizontalSize * imageVerticalSize, XAXIDMA_DEVICE_TO_DMA);
//
//	OLED_ClearBuffer(&myDevice);
//	OLED_SetCursor(&myDevice, 0, 0);
//	OLED_PutString(&myDevice, "Test1.0");
//
//	if(status != XST_SUCCESS){ return status; }
//
//	OLED_ClearBuffer(&myDevice);
//	OLED_SetCursor(&myDevice, 0, 0);
//	OLED_PutString(&myDevice, "Test1.1");
//
//	status = XAxiDma_SimpleTransfer(&dma, (UINTPTR) frameData, 4 * imageHorizontalSize, XAXIDMA_DMA_TO_DEVICE);
//
//	OLED_ClearBuffer(&myDevice);
//	OLED_SetCursor(&myDevice, 0, 0);
//	OLED_PutString(&myDevice, "Test1.2");
//
//	if(status != XST_SUCCESS){ return status; }
//
//	OLED_ClearBuffer(&myDevice);
//	OLED_SetCursor(&myDevice, 0, 0);
//	OLED_PutString(&myDevice, "Test1.3");
//
//	return status;
//}
//
///**
// * Check if the DMA controller is idle
// */
//int check_idle(u32 baseAddress, u32 offset) {
//	int status;
//	status = (XAxiDma_ReadReg(baseAddress, offset)) & XAXIDMA_IDLE_MASK;
//	return status;
//}
//
///**
// * image_proc_isr is called when the image filter is finished processing one line
// */
//static void image_proc_isr() {
//	int status;
//	static int i = 4;
//
//	// Temporarily disable interrupt
//	XScuGic_Disable(&intcInstance, XPAR_FABRIC_IMAGEPROCESSTOP_0_O_INTR_INTR);
//
//	// Wait until last data transmission is complete
//	status = check_idle(XPAR_AXI_DMA_0_BASEADDR, 0x4);
//	while (status == 0) {
//		status = check_idle(XPAR_AXI_DMA_0_BASEADDR, 0x4);
//	}
//
//	if (i < imageVerticalSize + 2) {
//		XAxiDma_SimpleTransfer(&dma, (u32) &frameData[i * imageHorizontalSize], imageHorizontalSize, XAXIDMA_DMA_TO_DEVICE);
//		i += 1;
//	}
//
//	// Re-enable interrupt
//	XScuGic_Enable(&intcInstance, XPAR_FABRIC_IMAGEPROCESSTOP_0_O_INTR_INTR);
//}
//
///**
// * dma_receive_isr is called when all of the data for a frame has been processed
// */
//static void dma_receive_isr() {
//	// Temporarily disable interrupt
//	XAxiDma_IntrDisable(&dma, XAXIDMA_IRQ_IOC_MASK, XAXIDMA_DEVICE_TO_DMA);
//
//	// Clear interrupt status register
//	XAxiDma_IntrAckIrq(&dma, XAXIDMA_IRQ_IOC_MASK, XAXIDMA_DEVICE_TO_DMA);
//
//	// Indicate that image processing is complete
//	imageProcDone = 1;
//
//	// Re-enable interrupt
//	XAxiDma_IntrEnable(&dma, XAXIDMA_IRQ_IOC_MASK, XAXIDMA_DEVICE_TO_DMA);
//}

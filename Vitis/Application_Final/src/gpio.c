
#include "gpio.h"

/*
 * Function for initializing GPIO
 */
int init_gpio() {
	// Define XGpio variables
	int status;

    // Initialize AXI GPIO instance
    status = XGpio_Initialize(&button1, XPAR_AXI_GPIO_1_DEVICE_ID);
    if (status != XST_SUCCESS) { return status; }

    status = XGpio_Initialize(&button2, XPAR_AXI_GPIO_2_DEVICE_ID);
    if (status != XST_SUCCESS) { return status; }

    status = XGpio_Initialize(&button3, XPAR_AXI_GPIO_3_DEVICE_ID);
    if (status != XST_SUCCESS) { return status; }

    status = XGpio_Initialize(&switch0, XPAR_AXI_GPIO_4_DEVICE_ID);
    if (status != XST_SUCCESS) { return status; }

    status = XGpio_Initialize(&switch1, XPAR_AXI_GPIO_5_DEVICE_ID);
    if (status != XST_SUCCESS) { return status; }

    status = XGpio_Initialize(&switch2, XPAR_AXI_GPIO_6_DEVICE_ID);
    if (status != XST_SUCCESS) { return status; }

    status = XGpio_Initialize(&switch3, XPAR_AXI_GPIO_7_DEVICE_ID);
    if (status != XST_SUCCESS) { return status; }

    // Set data direction registers for buttons
    XGpio_SetDataDirection(&button1, 1, 1);
    XGpio_SetDataDirection(&button2, 1, 1);
    XGpio_SetDataDirection(&button3, 1, 1);

    // Set data direction registers for switches
    XGpio_SetDataDirection(&switch0, 1, 1);
    XGpio_SetDataDirection(&switch1, 1, 1);
    XGpio_SetDataDirection(&switch2, 1, 1);
    XGpio_SetDataDirection(&switch3, 1, 1);

	return XST_SUCCESS;
}

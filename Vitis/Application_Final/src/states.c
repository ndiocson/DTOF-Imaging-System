
#include "states.h"

/*
 * Function for handling the idle_state
 */
eSystemState idle_state_handler(XUartPs_Config *myUartConfig, u8 mode) {
	display_blank();
	lastState = idle_state;

	// Initialize frame pointers
	frameDataPtr = frameData;
	filteredDataPtr = filteredData;

	// Configure system if swith0 is toggled
	if (XGpio_DiscreteRead(&switch0, 1) == 1) {
		return config_state;
	} else {
		// Button 1 pressed
		if (XGpio_DiscreteRead(&button1, 1) == 1) {
			// Send state change to RPi
			XUartPs_SendByte(myUartConfig->BaseAddress, (u8) mode);
			return init_state;
		}

		// Button 1 not pressed
		else {
			return idle_state;
		}
	}
}

/**
 * Function for handling the config_state
 */
eSystemState config_state_handler(XUartPs_Config *myUartConfig, u8 *mode, int *numFrames, float *distanceThreshold) {
	// Allow user to configure the system
	if (lastState == idle_state) {
		config_distance_threshold(distanceThreshold);
		config_number_frames(numFrames);
		config_mode(mode);
	}
	else if (lastState == stop_state) {
		config_distance_threshold(distanceThreshold);
	}

	if (XGpio_DiscreteRead(&switch0, 1) == 1) {
		return config_state;
	} else {
		return lastState;
	}
}

/*
 * Function for handling the init_state
 */
eSystemState init_state_handler(XUartPs_Config *myUartConfig, int numFrames) {
	// Allocate memory for frameData and distanceData
	isProcessed = malloc(sizeof(int) * numFrames);
	frameData = malloc(sizeof(u8) * imageSize * numFrames);
	filteredData = malloc(sizeof(u8) * imageSize * numFrames);
	distanceData = malloc(sizeof(u8) * imageSize * numFrames);

	for(int i = 0; i < numFrames; i++) {
		isProcessed[i] = 0;
	}

	// Read byte from RPi
	u8 receivedByte = XUartPs_RecvByte(myUartConfig->BaseAddress);

	// RPi initialized
	if (receivedByte == (u8) 2) {
		// Tell RPi how many frames to send
		XUartPs_SendByte(myUartConfig->BaseAddress, (u8) numFrames);
		while (XUartPs_RecvByte(myUartConfig->BaseAddress) != (u8) 3) { }
		return collect_dist;
	}

	// RPi not yet initialized
	else {
		return init_state;
	}
}

/**
 * Function for handling the collect_dist state
 */
eSystemState collect_dist_state_handler(XUartPs *myUart, XUartPs_Config *myUartConfig, int numFrames) {
	// Tell RPi to send distance data
	XUartPs_SendByte(myUartConfig->BaseAddress, (u8) 3);

	// Read frame data from RPi
	u32 receivedBytes = 0;
	u32 totalReceivedBytes = 0;
	while (totalReceivedBytes < imageSize * numFrames) {
		receivedBytes = XUartPs_Recv(myUart, &distanceData[totalReceivedBytes], 1);
		totalReceivedBytes += receivedBytes;
	}

	// TODO: Process distance data

	return collect_image;
}

/*
 * Function for handling the collect_image state
 */
eSystemState collect_image_state_handler(XUartPs *myUart, XUartPs_Config *myUartConfig, int numFrames) {
	int status;

	// Tell RPi to send image data
	XUartPs_SendByte(myUartConfig->BaseAddress, (u8) 4);

	// Read frame data from RPi
	u32 receivedBytes = 0;
	u32 totalReceivedBytes = 0;
	while (totalReceivedBytes < imageSize * numFrames) {
		receivedBytes = XUartPs_Recv(myUart, &frameData[totalReceivedBytes], 1);
		totalReceivedBytes += receivedBytes;
	}

//	frameDataPtr = &frameData[0];
//	filteredDataPtr = &filteredData[0];
//
//	for (int frame = 0; frame < numFrames; frame++) {
//		// Process frames
//		status = process_image();
//		if (status != XST_SUCCESS) { return status; }
//
//		usleep(500000);
//
//		// Wait for frames to be processed
//		while (!imageProcDone && ((XGpio_DiscreteRead(&button1, 1) != 1))) {
//			OLED_ClearBuffer(&myDevice);
//			OLED_SetCursor(&myDevice, 0, 0);
//			OLED_PutString(&myDevice, "Processing");
//		}
//
//		frameDataPtr = &frameData[imageSize * frame];
//		filteredDataPtr = &filteredData[imageSize * frame];
//	}

	return start_state;
}

/*
 * Function for handling the start_state
 */
eSystemState start_state_handler(XUartPs *myUart, XUartPs_Config *myUartConfig, int numFrames, float distanceThreshold) {
	// Button 2 pressed
	if (XGpio_DiscreteRead(&button2, 1) == 1) {
		return stop_state;
	} else {

		frameDataPtr = &frameData[0];
		filteredDataPtr = &filteredData[0];

		// Loop through frames
		for (int frame = 0; frame < numFrames; frame++) {

			// Clear digits
			for (int i = 0; i < 15; i++) {
				clear_digit(i * 15);
			}

			// TODO: Get min distance of current frame

			// Display the detected distance of the current frame
			if (distanceThreshold == 0.00f || (int) distanceData[153279 + (imageSize * frame)] > (int) distanceThreshold) {
				draw_int((int) distanceData[153279 + (imageSize * frame)], 0, 0xFF, 0xFF, 0xFF);
				draw_m(get_num_digs((int) distanceData[153279 + (imageSize * frame)]) * 15, 0xFF, 0xFF, 0xFF);
			} else {
				draw_int((int) distanceData[153279 + (imageSize * frame)], 0, 0xFF, 0x00, 0x00);
				draw_m(get_num_digs((int) distanceData[153279 + (imageSize * frame)]) * 15, 0xFF, 0x00, 0x00);
			}

			// Configure streaming mode
			if (XGpio_DiscreteRead(&switch0, 1) == 0) {
				OLED_SetCursor(&myDevice, 0, 1);
				OLED_PutString(&myDevice, "Normal");
			} else {
				OLED_SetCursor(&myDevice, 0, 1);
				OLED_PutString(&myDevice, "Slide Show");

				while (XGpio_DiscreteRead(&button1, 1) != 1) { }
			}

			frameDataPtr = &frameData[imageSize * frame];
			filteredDataPtr = &filteredData[imageSize * frame];

			if (!isProcessed[frame]) {
				// Process frames
				process_image();

				usleep(500000);

				// Wait for frames to be processed
				while (!imageProcDone && ((XGpio_DiscreteRead(&button1, 1) != 1))) {
					OLED_ClearBuffer(&myDevice);
					OLED_SetCursor(&myDevice, 0, 0);
					OLED_PutString(&myDevice, "Processing");
				}

				isProcessed[frame] = 1;
			}

			Xil_DCacheInvalidateRange((INTPTR) frameDataPtr, imageSize);
			Xil_DCacheInvalidateRange((INTPTR) filteredDataPtr, imageSize);

			// Loop through rows
			for (int i = verticalOffset; i < verticalOffset + imageVerticalSize; i++) {

				// Loop through columns
				for (int j = horizontalOffset; j < horizontalOffset + imageHorizontalSize; j++) {

					// Display filtered image
					if (XGpio_DiscreteRead(&switch3, 1) == 1) {

						// Display complemented image
						if (XGpio_DiscreteRead(&switch2, 1) == 1) {
							buffer[(i * screenHorizontalSize * 3) + (j * 3)] = 255 - *filteredDataPtr;
							buffer[(i * screenHorizontalSize * 3) + (j * 3) + 1] = 255 - *filteredDataPtr;
							buffer[(i * screenHorizontalSize * 3) + (j * 3) + 2] = 255 - *filteredDataPtr;
						}

						// Display normal image
						else {
							buffer[(i * screenHorizontalSize * 3) + (j * 3)] = *filteredDataPtr;
							buffer[(i * screenHorizontalSize * 3) + (j * 3) + 1] = *filteredDataPtr;
							buffer[(i * screenHorizontalSize * 3) + (j * 3) + 2] = *filteredDataPtr;
						}
					}

					// Display un-filtered image
					else {

						// Display complemented image
						if (XGpio_DiscreteRead(&switch2, 1) == 1) {
							buffer[(i * screenHorizontalSize * 3) + (j * 3)] = 255 - *frameDataPtr;
							buffer[(i * screenHorizontalSize * 3) + (j * 3) + 1] = 255 - *frameDataPtr;
							buffer[(i * screenHorizontalSize * 3) + (j * 3) + 2] = 255 - *frameDataPtr;
						}

						// Display normal image
						else {
							buffer[(i * screenHorizontalSize * 3) + (j * 3)] = *frameDataPtr;
							buffer[(i * screenHorizontalSize * 3) + (j * 3) + 1] = *frameDataPtr;
							buffer[(i * screenHorizontalSize * 3) + (j * 3) + 2] = *frameDataPtr;
						}
					}

					frameDataPtr++;
					filteredDataPtr++;
				}
			}
		}

		return start_state;
	}
}

/*
 * Function for handling the stop_state
 */
eSystemState stop_state_handler(XUartPs_Config *myUartConfig) {
	lastState = stop_state;

	// Read button 1 and 2
	int user_input1 = XGpio_DiscreteRead(&button1, 1);
	int user_input2 = XGpio_DiscreteRead(&button2, 1);

	// Configure system if swith0 is toggled
	if (XGpio_DiscreteRead(&switch0, 1) == 1) {
		return config_state;
	} else {
		// No button pressed
		if (user_input1 == 0 && user_input2 == 0) {
			return stop_state;
		}

		// Button 2 pressed
		else if (user_input1 == 0 && user_input2 == 1) {
			return end_state;
		}

		// Button 1 pressed
		else if (user_input1 == 1 && user_input2 == 0) {
			return start_state;
		}

		// Both buttons pressed
		else {
			return start_state;
		}
	}
}

/*
 * Function for handling the end_state
 */
eSystemState end_state_handler(XUartPs_Config *myUartConfig) {
	free(frameData);
	free(filteredData);
	free(distanceData);
	return idle_state;
}

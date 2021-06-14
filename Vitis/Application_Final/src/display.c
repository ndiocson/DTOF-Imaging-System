
#include "display.h"

/**
 * Function for initializing VDMA
 */
int init_vdma() {
	// Define XAxiVdma variables
	int status;
	u32 addr;
	XAxiVdma_Config *config = XAxiVdma_LookupConfig(XPAR_AXI_VDMA_0_DEVICE_ID);
	XAxiVdma_DmaSetup ReadCfg;

	status = XAxiVdma_CfgInitialize(&vdma, config, config->BaseAddress);
    if(status != XST_SUCCESS){ return status; }

//    u32 stride = screenHorizontalSize * (config->Mm2SStreamWidth>>3);

    ReadCfg.VertSizeInput = screenVerticalSize;
    ReadCfg.HoriSizeInput = screenHorizontalSize * 3;
    ReadCfg.Stride = screenHorizontalSize * 3;
    ReadCfg.FrameDelay = 0;
    ReadCfg.EnableCircularBuf = 1;
    ReadCfg.EnableSync = 0;
    ReadCfg.PointNum = 0;
    ReadCfg.EnableFrameCounter = 0;
    ReadCfg.FixedFrameStoreAddr = 0;

    status = XAxiVdma_DmaConfig(&vdma, XAXIVDMA_READ, &ReadCfg);
    if (status != XST_SUCCESS) { return status; }

    addr = (u32) & (buffer[0]);
	for(int i = 0; i < vdma.MaxNumFrames; i++) {
		ReadCfg.FrameStoreStartAddr[i] = addr;
		addr += frameSize;
	}

	status = XAxiVdma_DmaSetBufferAddr(&vdma, XAXIVDMA_READ, ReadCfg.FrameStoreStartAddr);
	if (status != XST_SUCCESS) { return status; }

//	status = XAxiVdma_DmaSetBufferAddr(&vdma, XAXIVDMA_READ, (UINTPTR *) &buffer);
//	if (status != XST_SUCCESS) { return status; }

//	XAxiVdma_IntrEnable(&myVDMA, XAXIVDMA_IXR_COMPLETION_MASK, XAXIVDMA_READ);
//	SetupIntrSystem(&myVDMA, XPAR_FABRIC_AXI_VDMA_0_MM2S_INTROUT_INTR);

//	status = XAxiVdma_DmaStart(&vdma, XAXIVDMA_READ);
//	if (status != XST_SUCCESS) { return XST_FAILURE; }

	return XST_SUCCESS;
}

/**
 *
 */
int vdma_start() {
	int status;
	status = XAxiVdma_DmaStart(&vdma, XAXIVDMA_READ);
	if (status != XST_SUCCESS) { return status; }

	return XST_SUCCESS;
}

/*
 * Function for displaying a blank screen
 */
void display_blank() {
	// Set all pixels black
	for (int i = 0; i < frameSize; i++) {
		buffer[i] = 0x00;
	}
}

/**
 *
 */
void draw_dot(int index, u8 red, u8 green, u8 blue) {
	for (int i = 0; i < 3; i++) {
		buffer[index + (frameSize * i)] = green;
		buffer[index + (frameSize * i) + 1] = blue;
		buffer[index + (frameSize * i) + 2] = red;
	}
}

/**
 *
 */
void clear_dot(int index) {
	for (int i = 0; i < 3; i++) {
		buffer[index + (frameSize * i)] = 0x00;
		buffer[index + (frameSize * i) + 1] = 0x00;
		buffer[index + (frameSize * i) + 2] = 0x00;
	}
}

/**
 *
 */
void clear_digit(int offset) {
	int index1 = drawStartPoint + (offset * 3);

	for (int i = 0; i < digitHeight; i++) {
		for (int i = 0; i < digitWidth; i++) {
			clear_dot(index1);
			index1 += 3;
		}

		index1 += (screenHorizontalSize * 3) - (digitWidth * 3);
	}
}

/**
 *
 */
void draw_decimal_point(int offset, u8 red, u8 green, u8 blue) {
	int index1 = drawStartPoint + (13 * screenHorizontalSize * 3) + (3 * 3) + (offset * 3);

	// Draw vertical
	for (int i = 0; i < 2; i++) {
		draw_dot(index1, red, green, blue);
		draw_dot(index1 + (1 * 3), red, green, blue);
		index1 += (screenHorizontalSize * 3);
	}
}

/**
 *
 */
void draw_m(int offset, u8 red, u8 green, u8 blue) {
	int index1 = drawStartPoint + (7 * screenHorizontalSize * 3) + (offset * 3);
	int index2 = drawStartPoint + (7 * screenHorizontalSize * 3) + (offset * 3);

	// Draw horizontal
	for (int i = 0; i < digitWidth; i++) {
		draw_dot(index1, red, green, blue);
		index1 += 3;
	}

	// Draw vertical
	for (int i = 0; i < 8; i++) {
		draw_dot(index2, red, green, blue);
		draw_dot(index2 + (4 * 3), red, green, blue);
		draw_dot(index2 + (digitWidth * 3), red, green, blue);
		index2 += (screenHorizontalSize * 3);
	}
}

/**
 *
 */
int get_num_digs(int num) {
	int numDigits = 1;
	int numTemp = num;
	while (numTemp /= 10) {
		numDigits += 1;
	}

	return numDigits;
}

/**
 * Function for drawing the number 0 to the screen
 */
void draw_zero(int offset, u8 red, u8 green, u8 blue) {
	int index1 = drawStartPoint + (offset * 3);
	int index2 = drawStartPoint + (offset * 3);

	// Draw horizontal
	for (int i = 0; i < digitWidth; i++) {
		draw_dot(index1, red, green, blue);
		draw_dot(index1 + (14 * screenHorizontalSize * 3), red, green, blue);
		index1 += 3;
	}

	// Draw vertical
	for (int i = 0; i < digitHeight; i++) {
		draw_dot(index2, red, green, blue);
		draw_dot(index2 + (7 * 3), red, green, blue);
		index2 += (screenHorizontalSize * 3);
	}
}

/**
 * Function for drawing the number 1 to the screen
 */
void draw_one(int offset, u8 red, u8 green, u8 blue) {
	int index1 = drawStartPoint + (7 * 3) + (offset * 3);

	// Draw vertical
	for (int i = 0; i < digitHeight; i++) {
		draw_dot(index1, red, green, blue);
		index1 += (screenHorizontalSize * 3);
	}
}

/**
 * Function for drawing the number 2 to the screen
 */
void draw_two(int offset, u8 red, u8 green, u8 blue) {
	int index1 = drawStartPoint + (offset * 3);
	int index2 = drawStartPoint + (7 * 3) + (offset * 3);

	// Draw horizontal
	for (int i = 0; i < digitWidth; i++) {
		draw_dot(index1, red, green, blue);
		draw_dot(index1 + (7 * screenHorizontalSize * 3), red, green, blue);
		draw_dot(index1 + (14 * screenHorizontalSize * 3), red, green, blue);
		index1 += 3;
	}

	// Draw vertical
	for (int i = 0; i < 8; i++) {
		draw_dot(index2, red, green, blue);
		draw_dot(index2 - (7 * 3) + (7 * screenHorizontalSize * 3), red, green, blue);
		index2 += (screenHorizontalSize * 3);
	}
}

/**
 * Function for drawing the number 3 to the screen
 */
void draw_three(int offset, u8 red, u8 green, u8 blue) {
	int index1 = drawStartPoint + (offset * 3);
	int index2 = drawStartPoint + (7 * 3) + (offset * 3);

	// Draw horizontal
	for (int i = 0; i < digitWidth; i++) {
		draw_dot(index1, red, green, blue);
		draw_dot(index1 + (7 * screenHorizontalSize * 3), red, green, blue);
		draw_dot(index1 + (14 * screenHorizontalSize * 3), red, green, blue);
		index1 += 3;
	}

	// Draw vertical
	for (int i = 0; i < digitHeight; i++) {
		draw_dot(index2, red, green, blue);
		index2 += (screenHorizontalSize * 3);
	}
}

/**
 * Function for drawing the number 4 to the screen
 */
void draw_four(int offset, u8 red, u8 green, u8 blue) {
	int index1 = drawStartPoint + (6 * screenHorizontalSize * 3) + (offset * 3);
	int index2 = drawStartPoint + (offset * 3);
	int index3 = drawStartPoint + (7 * 3) + (offset * 3);

	// Draw horizontal
	for (int i = 0; i < digitWidth; i++) {
		draw_dot(index1, red, green, blue);
		index1 += 3;
	}

	// Draw vertical
	for (int i = 0; i < 6; i++) {
		draw_dot(index2, red, green, blue);
		index2 += (screenHorizontalSize * 3);
	}

	// Draw vertical
	for (int i = 0; i < digitHeight; i++) {
		draw_dot(index3, red, green, blue);
		index3 += (screenHorizontalSize * 3);
	}
}

/**
 * Function for drawing the number 5 to the screen
 */
void draw_five(int offset, u8 red, u8 green, u8 blue) {
	int index1 = drawStartPoint + (offset * 3);
	int index2 = drawStartPoint + (offset * 3);

	// Draw horizontal
	for (int i = 0; i < digitWidth; i++) {
		draw_dot(index1, red, green, blue);
		draw_dot(index1 + (7 * screenHorizontalSize * 3), red, green, blue);
		draw_dot(index1 + (14 * screenHorizontalSize * 3), red, green, blue);
		index1 += 3;
	}

	// Draw vertical
	for (int i = 0; i < 8; i++) {
		draw_dot(index2, red, green, blue);
		draw_dot(index2 + (7 * screenHorizontalSize * 3) + (7 * 3), red, green, blue);
		index2 += (screenHorizontalSize * 3);
	}
}

/**
 * Function for drawing the number 6 to the screen
 */
void draw_six(int offset, u8 red, u8 green, u8 blue) {
	int index1 = drawStartPoint + (7 * screenHorizontalSize * 3) + (offset * 3);
	int index2 = drawStartPoint + (7 * screenHorizontalSize * 3) + (7 * 3) + (offset * 3);
	int index3 = drawStartPoint + (offset * 3);

	// Draw horizontal
	for (int i = 0; i < digitWidth; i++) {
		draw_dot(index1, red, green, blue);
		draw_dot(index1 + (7 * screenHorizontalSize * 3), red, green, blue);
		index1 += 3;
	}

	// Draw vertical
	for (int i = 0; i < 7; i++) {
		draw_dot(index2, red, green, blue);
		index2 += (screenHorizontalSize * 3);
	}

	// Draw vertical
	for (int i = 0; i < digitHeight; i++) {
		draw_dot(index3, red, green, blue);
		index3 += (screenHorizontalSize * 3);
	}
}

/**
 * Function for drawing the number 7 to the screen
 */
void draw_seven(int offset, u8 red, u8 green, u8 blue) {
	int index1 = drawStartPoint + (offset * 3);
	int index2 = drawStartPoint + (7 * 3) + (offset * 3);

	// Draw horizontal
	for (int i = 0; i < digitWidth; i++) {
		draw_dot(index1, red, green, blue);
		index1 += 3;
	}

	// Draw vertical
	for (int j = 0; j < digitHeight; j++) {
		draw_dot(index2, red, green, blue);
		index2 += (screenHorizontalSize * 3);
	}
}

/**
 * Function for drawing the number 8 to the screen
 */
void draw_eight(int offset, u8 red, u8 green, u8 blue) {
	int index1 = drawStartPoint + (offset * 3);
	int index2 = drawStartPoint + (offset * 3);

	// Draw horizontal
	for (int i = 0; i < digitWidth; i++) {
		draw_dot(index1, red, green, blue);
		draw_dot(index1 + (7 * screenHorizontalSize * 3), red, green, blue);
		draw_dot(index1 + (14 * screenHorizontalSize * 3), red, green, blue);
		index1 += 3;
	}

	// Draw vertical
	for (int i = 0; i < digitHeight; i++) {
		draw_dot(index2, red, green, blue);
		draw_dot(index2 + (7 * 3), red, green, blue);
		index2 += (screenHorizontalSize * 3);
	}
}

/**
 * Function for drawing the number 9 to the screen
 */
void draw_nine(int offset, u8 red, u8 green, u8 blue) {
	int index1 = drawStartPoint + (offset * 3);
	int index2 = drawStartPoint + (offset * 3);
	int index3 = drawStartPoint + (7 * 3) + (offset * 3);

	// Draw horizontal
	for (int i = 0; i < digitWidth; i++) {
		draw_dot(index1, red, green, blue);
		draw_dot(index1 + (6 * screenHorizontalSize * 3), red, green, blue);
		index1 += 3;
	}

	// Draw vertical
	for (int i = 0; i < 6; i++) {
		draw_dot(index2, red, green, blue);
		index2 += (screenHorizontalSize * 3);
	}

	// Draw vertical
	for (int i = 0; i < digitHeight; i++) {
		draw_dot(index3, red, green, blue);
		index3 += (screenHorizontalSize * 3);
	}
}

/**
 * Function for drawing a single digit number between 0 and 9 to the screen
 */
void draw_int(int num, int offset, u8 red, u8 green, u8 blue) {
	int numDigits = get_num_digs(num);

	switch (num) {
		case 0:
			draw_zero(offset, red, green, blue);
			break;

		case 1:
			draw_one(offset, red, green, blue);
			break;

		case 2:
			draw_two(offset, red, green, blue);
			break;

		case 3:
			draw_three(offset, red, green, blue);
			break;

		case 4:
			draw_four(offset, red, green, blue);
			break;

		case 5:
			draw_five(offset, red, green, blue);
			break;

		case 6:
			draw_six(offset, red, green, blue);
			break;

		case 7:
			draw_seven(offset, red, green, blue);
			break;

		case 8:
			draw_eight(offset, red, green, blue);
			break;

		case 9:
			draw_nine(offset, red, green, blue);
			break;

		default:
			offset += (15 * (numDigits - 1));
			while(num > 0) {
				int digit = num % 10;
				draw_int(digit, offset, red, green, blue);
				num /= 10;
				offset -= 15;
			}
			break;
	}
}

/**
 *
 */
void draw_float(float num, int offset) {

}

/*
 * Function for displaying a single frame of pixel data to the monitor
 */
void draw_frame(u8 *pixelPtr) {
	// Loop through rows
	for (int i = verticalOffset; i < verticalOffset + imageVerticalSize; i++) {

		// Loop through columns
		for (int j = horizontalOffset; j < horizontalOffset + imageHorizontalSize; j++) {

			// Write pixel value to buffer
			buffer[(i * screenHorizontalSize * 3) + (j * 3)] = *pixelPtr;
			buffer[(i * screenHorizontalSize * 3) + (j * 3) + 1] = *pixelPtr;
			buffer[(i * screenHorizontalSize * 3) + (j * 3) + 2] = *pixelPtr;
			pixelPtr++;
		}
	}
}

/**
 * Function for displaying the complement of a single frame of pixel data to the monitor
 */
void draw_complement_frame(u8 *pixelPtr) {
	// Loop through rows
	for (int i = verticalOffset; i < verticalOffset + imageVerticalSize; i++) {

		// Loop through columns
		for (int j = horizontalOffset; j < horizontalOffset + imageHorizontalSize; j++) {

			// Write pixel value to buffer
			buffer[(i * screenHorizontalSize * 3) + (j * 3)] = 255 - *pixelPtr;
			buffer[(i * screenHorizontalSize * 3) + (j * 3) + 1] = 255 - *pixelPtr;
			buffer[(i * screenHorizontalSize * 3) + (j * 3) + 2] = 255 - *pixelPtr;
			pixelPtr++;
		}
	}
}

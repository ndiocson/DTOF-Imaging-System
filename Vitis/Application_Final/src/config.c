
#include "config.h"

/**
 * Function for configuring the distance threshold
 */
void config_distance_threshold(float *distanceThreshold) {
	// Increase or decrease distance threshold
	if (XGpio_DiscreteRead(&button1, 1) == 1) {

		// Increase threshold
		if (XGpio_DiscreteRead(&switch1, 1) == 1) {
			if (*distanceThreshold < 9.9f) {
				*distanceThreshold += 0.1f;
			}
		}

		// Decrease threshold
		else {
			if (*distanceThreshold > 0.1f) {
				*distanceThreshold -= 0.1f;
			}
		}
	}

	// Convert distanceThreshold threshold to char array
	char *thresholdCharBuf[2];
	gcvt(*distanceThreshold, 2, thresholdCharBuf);
	strcat(thresholdCharBuf, "m");

	// Draw to OLED
	OLED_SetCursor(&myDevice, 0, 1);
	OLED_PutString(&myDevice, thresholdCharBuf);
}

/**
 * Function for configuring the number of frames to collect
 */
void config_number_frames(int *numFrames) {
	// Increase or decrease number of frames to collect
	if (XGpio_DiscreteRead(&button2, 1) == 1) {

		// Increase frames
		if (XGpio_DiscreteRead(&switch1, 1) == 1) {
			if (*numFrames < maxFrames) {
				*numFrames += 1;
			}
		}

		// Decrease frames
		else {
			if (*numFrames > 1) {
				*numFrames -= 1;
			}
		}
	}

	int numDigs = 1;
	if (*numFrames > 9) {
		numDigs = 2;
	}

	char *numFramesCharBuf = to_array(*numFrames, numDigs);
	strcat(numFramesCharBuf, " frames");

	// Draw to OLED
	OLED_SetCursor(&myDevice, 0, 2);
	OLED_PutString(&myDevice, numFramesCharBuf);
}

/**
 * Function for configuring the mode of the front-end kit
 */
void config_mode(u8 *mode) {
	// Increase or decrease mode
	if (XGpio_DiscreteRead(&button3, 1) == 1) {

		// Increase mode
		if (XGpio_DiscreteRead(&switch1, 1) == 1) {
			if (*mode < 3) {
				*mode += 1;
			}
		}

		// Decrease mode
		else {
			if (*mode > 1) {
				*mode -= 1;
			}
		}
	}

	// Draw to OLED
	switch (*mode) {
		case 1:
			OLED_SetCursor(&myDevice, 0, 3);
			OLED_PutString(&myDevice, "Near mode");
			break;

		case 2:
			OLED_SetCursor(&myDevice, 0, 3);
			OLED_PutString(&myDevice, "Medium mode");
			break;

		case 3:
			OLED_SetCursor(&myDevice, 0, 3);
			OLED_PutString(&myDevice, "Far mode");
			break;

		default:
			OLED_SetCursor(&myDevice, 0, 3);
			OLED_PutString(&myDevice, "Unknown mode");
			break;
	}
}

/**
 * Function for converting an integer to a char array
 */
char * to_array(int number, int numDigs) {
	char *numberArray = calloc(numDigs, sizeof(char));
	for (int i = numDigs - 1; i >= 0; --i, number /= 10) {
		numberArray[i] = (number % 10) + '0';
	}

	return numberArray;
}

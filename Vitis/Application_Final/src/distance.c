
#include "distance.h"

// for testing purposes
// uint8_t distanceData[] = { 20, 30, 109, 180, 199, 200, 100, 110 };

/**
 *
 */
void findLargestNum(int* largestNum, int* largestNumIndex) {
	for (int i = 1; i < sizeof(distanceData); ++i) {
		if (distanceData[i] > * largestNum) {
//			return i;
			*largestNum = distanceData[i];
			*largestNumIndex = i;
		}
	}
}

/**
 *
 */
void findSmallestNum(int* smallestNum, int* smallestNumIndex) {
	for (int i = 1; i < sizeof(distanceData); ++i) {
		if ((distanceData[i] < *smallestNum) && (distanceData[i] != 0)) {
//			return i;
			*smallestNum = distanceData[i];
			*smallestNumIndex = i;
		}
	}
}

// 640 horizontal, 480 vertically
// ---------------------------
// |                         |
// |        ********         |
// |        ********         |
// |        ********         |
// |                         |		480
// ---------------------------
//				640

// 		480 / 4 = 120 
// 		640 / 4 = 160

// ---------------------------
// |                         |
// | 160,120********480,120  |
// |        ********         |		these dimensions makes a square inthe middle
// | 160,360********480,360  |
// |                         |		
// ---------------------------

// actual indexes? 
	// 160,120: 120th row, so 640pixels per row * 120rows = 76800 + (160) = 76960 (STARTING INDEX)
	// 76960 is the first index of the first row, each successive row is + 640 elements

	// 77280 (76800 + 480) end of first row
	// aka each row iteration goes 320 indexes 

// rn the current thoughts is doing the middle,
// like a floating object so that the middle object 
// is most likely to be the closest object
/**
 *
 */
void middleOfImage(int* smallestNum, int* smallestNumIndex) {
	//  first element of first row      element 1 of last row
	// goes downwards
	for (int i = 76960; i < 230560; i += 640) {

		// goes right
		for (int j = 0; j < 320; ++j) {

			// need to get the right index
			if (distanceData[i + j] < *smallestNum) {
				*smallestNum = distanceData[i];
				*smallestNumIndex = i;
			}
		}
	}
}

// Not sure if we need this but it was easy enough to implement
/**
 *
 */
void findAvgNum(float* avgNum) {
	int n = 0;
	for (int i = 1; i < sizeof(distanceData); ++i) {
		if (distanceData[i] != 0) {
			*avgNum += distanceData[i];
			n++;
		}
	}

	*avgNum = *avgNum / n;
}

// Note that this doesn't work if the array is not uint8_t but it always is so ...
/**
 *
 */
void maxThreshold(int* maxRange) {
	// Assuming an array is given
	for (int i = 0; i < sizeof(distanceData); i++) {
		if (distanceData[i] > * maxRange) {
			distanceData[i] = 0;
		}
	}
}

/**
 *
 */
void findBoth(int* smallestNum, int* smallestNumIndex, int* largestNum, int* largestNumIndex) {
	for (int i = 1; i < sizeof(distanceData); ++i) {
		// printf("Index and Number %d, %d \r\n", i, distanceData[i]);
		// printf("Size of distanceData: %d\r\n", sizeof(distanceData));
		// printf("largest num: %d\r\n", *largestNum);
		// printf("largest num index: %d\r\n", *largestNumIndex);

		if (distanceData[i] > * largestNum) {
			*largestNum = distanceData[i];
			*largestNumIndex = i;
		}

		if ((distanceData[i] < *smallestNum) && (distanceData[i] != 0)) {
			*smallestNum = distanceData[i];
			*smallestNumIndex = i;
			// printf("smallest num: %d\r\n", *smallestNum);
		}
	}
}

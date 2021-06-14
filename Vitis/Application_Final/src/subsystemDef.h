
#ifndef __SUBSYSTEMDEF_H_
#define __SUBSYSTEMDEF_H_

// Xilinx header files
#include <stdio.h>
#include <stdlib.h>
#include "sleep.h"
#include "xil_io.h"
#include "xparameters.h"
#include "xgpio.h"
#include "xuartps.h"
#include "xscugic.h"
#include "xaxidma.h"
#include "xaxivdma.h"
#include "xil_cache.h"
#include "PmodOLED.h"

// User-defined header files
#include "config.h"
#include "display.h"
//#include "filter.h"
#include "gpio.h"
#include "states.h"
#include "distance.h"

#define baudRate 	921600
#define maxFrames	99

u8 *frameData;
u8 *filteredData;
u8 *distanceData;
u8 *frameDataPtr;
u8 *filteredDataPtr;

int *isProcessed;

XAxiDma dma;
int imageProcDone;
XScuGic intcInstance;
PmodOLED myDevice;

#endif

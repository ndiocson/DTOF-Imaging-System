
#ifndef __STATES_H_
#define __STATES_H_

#include "subsystemDef.h"

// FSM enumerated states
typedef enum {
	idle_state,		// State 0
	config_state,	// State 1
	init_state,		// State 2
	collect_image,	// State 3
	collect_dist,	// State 4
	start_state,	// State 5
	stop_state,		// State 6
	end_state		// State 7
} eSystemState;

eSystemState nextState;
eSystemState lastState;

eSystemState idle_state_handler(XUartPs_Config *myUartConfig, u8 mode);
eSystemState config_state_handler(XUartPs_Config *myUartConfig, u8 *mode, int *numFrames, float *distanceThreshold);
eSystemState init_state_handler(XUartPs_Config *myUartConfig, int numFrames);
eSystemState collect_image_state_handler(XUartPs *myUart, XUartPs_Config *myUartConfig, int numFrames);
eSystemState collect_dist_state_handler(XUartPs *myUart, XUartPs_Config *myUartConfig, int numFrames);
eSystemState start_state_handler(XUartPs *myUart, XUartPs_Config *myUartConfig, int numFrames, float distanceThreshold);
eSystemState stop_state_handler(XUartPs_Config *myUartConfig);
eSystemState end_state_handler(XUartPs_Config *myUartConfig);

#endif

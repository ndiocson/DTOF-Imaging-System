
#ifndef _FILTER_H_
#define _FILTER_H_

#include "subsystemDef.h"

int initIntrController();
int init_filter();
int startImageProcessing();
int check_idle(u32 baseAddress, u32 offset);
static void image_proc_isr();
static void dma_receive_isr();

#endif

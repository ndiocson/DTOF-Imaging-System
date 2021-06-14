
#ifndef __DISPLAY_H_
#define __DISPLAY_H_

#include "subsystemDef.h"

// BOUNDS
// WIDTH: 8
// HEIGHT: 15
// TOP-LEFT: 1614720
// TOP-RIGHT: 1614732 = (1614720 + (7 * 3))
// BOT-LEFT: 1695360 = (1614720 + (14 * 1920 * 3))
// BOT-RIGHT: 1641612 = (1695360 + (4 * 3))
#define drawStartPoint			1614720
#define digitHeight				15
#define digitWidth				8

#define screenHorizontalSize 	1920
#define screenVerticalSize 		1080
#define imageHorizontalSize 	640
#define imageVerticalSize 		480

#define	imageSize				imageHorizontalSize * imageVerticalSize
#define frameSize 				screenHorizontalSize * screenVerticalSize * 3
#define horizontalOffset		(screenHorizontalSize - imageHorizontalSize) / 2
#define verticalOffset			(screenVerticalSize - imageVerticalSize) / 2

XAxiVdma vdma;

/*
 * Frame buffer for pixel data
 */
unsigned char buffer[frameSize];

int init_vdma();
int vdma_start();
void display_blank();
void draw_dot(int index, u8 red, u8 green, u8 blue);
void clear_dot(int index);
void clear_digit(int offset);
void draw_decimal_point(int offset, u8 red, u8 green, u8 blue);
void draw_m(int offset, u8 red, u8 green, u8 blue);
int get_num_digs(int num);
void draw_zero(int offset, u8 red, u8 green, u8 blue);
void draw_one(int offset, u8 red, u8 green, u8 blue);
void draw_two(int offset, u8 red, u8 green, u8 blue);
void draw_three(int offset, u8 red, u8 green, u8 blue);
void draw_four(int offset, u8 red, u8 green, u8 blue);
void draw_five(int offset, u8 red, u8 green, u8 blue);
void draw_six(int offset, u8 red, u8 green, u8 blue);
void draw_seven(int offset, u8 red, u8 green, u8 blue);
void draw_eight(int offset, u8 red, u8 green, u8 blue);
void draw_nine(int offset, u8 red, u8 green, u8 blue);
void draw_int(int num, int offset, u8 red, u8 green, u8 blue);
void draw_float(float num, int offset);
void draw_frame(u8 *pixelPtr);
void draw_complement_frame(u8 *pixelPtr);

#endif

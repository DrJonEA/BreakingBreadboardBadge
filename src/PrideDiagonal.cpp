/*
 * PrideDiagonal.cpp
 *
 *  Created on: 17 Sep 2026
 *      Author: jondurrant
 */

#include "PrideDiagonal.h"

/***
 * Default constructor
 * SetStrip must be called after this
 */
PrideDiagonal::PrideDiagonal() : RingAnimation() {
	xColours[0] = PicoLed::RGB(0xE4, 0x03, 0x03); //Red
	xColours[1] = PicoLed::RGB(0xFF, 0x8C, 0x00); //Orange
	xColours[2] = PicoLed::RGB(0xFF, 0xED, 0x00); //Yellow
	xColours[3] = PicoLed::RGB(0x00, 0x80, 0x26); //Green
	xColours[4] = PicoLed::RGB(0x00, 0x4D, 0xFF); //Blue
	xColours[5] = PicoLed::RGB(0x73, 0x29, 0x82); //Violet
}

/***
 * Construct the object
 * @param strip - PicoLed strip object
 * @param width - number of columns in the matrix
 * @param height - number of rows in the matrix
 * @param stepMS - time in milliseconds between each step of animation
 */
PrideDiagonal::PrideDiagonal(
	PicoLed::PicoLedController *strip,
	uint8_t width,
	uint8_t height,
	uint16_t stepMS):
	RingAnimation(strip, width * height, PicoLed::RGB(0, 0, 0), stepMS){
	xWidth = width;
	xHeight = height;
	xMarginX = (width > CENTRAL_SIZE) ? ((width - CENTRAL_SIZE) / 2) : 0;
	xMarginY = (height > CENTRAL_SIZE) ? ((height - CENTRAL_SIZE) / 2) : 0;

	xColours[0] = PicoLed::RGB(0xE4, 0x03, 0x03); //Red
	xColours[1] = PicoLed::RGB(0xFF, 0x8C, 0x00); //Orange
	xColours[2] = PicoLed::RGB(0xFF, 0xED, 0x00); //Yellow
	xColours[3] = PicoLed::RGB(0x00, 0x80, 0x26); //Green
	xColours[4] = PicoLed::RGB(0x00, 0x4D, 0xFF); //Blue
	xColours[5] = PicoLed::RGB(0x73, 0x29, 0x82); //Violet
}

/***
 * Destructor
 */
PrideDiagonal::~PrideDiagonal() {
	// NOP
}

/***
 * Perform step of animation
 */
void PrideDiagonal::step(){
	if (pStrip != NULL){
		//Every pixel in the central square is repainted each step, so no
		//need to clear first - avoids wiping out other animations sharing
		//the strip outside this square
		uint8_t rows = (xHeight < CENTRAL_SIZE) ? xHeight : CENTRAL_SIZE;
		uint8_t cols = (xWidth < CENTRAL_SIZE) ? xWidth : CENTRAL_SIZE;
		for (uint8_t localRow = 0; localRow < rows; localRow++){
			for (uint8_t localCol = 0; localCol < cols; localCol++){
				//Diagonal (45 degree) stripes, one per pride flag colour
				uint8_t colourIdx = (localRow + localCol + xOffset) % COLOUR_COUNT;
				uint8_t row = xMarginY + localRow;
				uint8_t col = xMarginX + localCol;
				pStrip->setPixelColor((row * xWidth) + col, xColours[colourIdx]);
			}
		}

		pStrip->show();
	}
	xOffset = (xOffset + 1) % COLOUR_COUNT;
}

/***
 * Reset animation to start position
 */
void PrideDiagonal::reset(){
	RingAnimation::reset();
	xOffset = 0;
}

/*
 * MatrixOutline.cpp
 *
 *  Created on: 17 Sep 2026
 *      Author: jondurrant
 */

#include "MatrixOutline.h"

/***
 * Default constructor
 * SetStrip must be called after this
 */
MatrixOutline::MatrixOutline() : RingAnimation() {
	buildOutline();
}

/***
 * Construct the object
 * @param strip - PicoLed strip object
 * @param width - number of columns in the matrix
 * @param height - number of rows in the matrix
 * @param colour - colour to use for the animation
 * @param stepMS - time in milliseconds between each step of animation
 */
MatrixOutline::MatrixOutline(
	PicoLed::PicoLedController *strip,
	uint8_t width,
	uint8_t height,
	PicoLed::Color colour,
	uint16_t stepMS):
	RingAnimation(strip, width * height, colour, stepMS){
	xWidth = width;
	xHeight = height;
	buildOutline();
}

/***
 * Destructor
 */
MatrixOutline::~MatrixOutline() {
	if (pOutline != NULL){
		delete[] pOutline;
		pOutline = NULL;
	}
}

/***
 * Build the ordered list of strip indexes that trace the outer edge
 * of the matrix, assuming row major (row * width + col) wiring
 */
void MatrixOutline::buildOutline(){
	if (pOutline != NULL){
		delete[] pOutline;
		pOutline = NULL;
	}
	xOutlineLen = 0;

	if ((xWidth == 0) || (xHeight == 0)){
		return;
	}

	uint16_t maxLen = (2 * xWidth) + (2 * xHeight) - 4;
	if (maxLen < 1){
		maxLen = 1;
	}
	pOutline = new uint8_t[maxLen];

	//Top row, left to right
	for (uint8_t col = 0; col < xWidth; col++){
		pOutline[xOutlineLen++] = (0 * xWidth) + col;
	}

	//Right column, top+1 to bottom
	for (uint8_t row = 1; row < xHeight; row++){
		pOutline[xOutlineLen++] = (row * xWidth) + (xWidth - 1);
	}

	//Bottom row, right-1 to left
	if (xHeight > 1){
		for (int16_t col = xWidth - 2; col >= 0; col--){
			pOutline[xOutlineLen++] = ((xHeight - 1) * xWidth) + col;
		}
	}

	//Left column, bottom-1 to top+1
	if (xWidth > 1){
		for (int16_t row = xHeight - 2; row >= 1; row--){
			pOutline[xOutlineLen++] = (row * xWidth) + 0;
		}
	}
}

/***
 * Perform step of animation
 */
void MatrixOutline::step(){
	//If step has reached end restart
	if (xStep >= xOutlineLen){
		xStep = 0;
	}

	//Only animate if we have a strip and an outline to follow
	if ((pStrip != NULL) && (xOutlineLen > 0)){
		//Only turn off the previously lit pixel so other animations sharing
		//the strip are left untouched
		if (xPrevIndex >= 0){
			pStrip->setPixelColor(xPrevIndex, PicoLed::RGB(0, 0, 0));
		}
		pStrip->setPixelColor(pOutline[xStep], xColour);
		pStrip->show();
		xPrevIndex = pOutline[xStep];
	}
	xStep++;
}

/***
 * Reset animation to start position
 */
void MatrixOutline::reset(){
	RingAnimation::reset();
	if ((pStrip != NULL) && (xPrevIndex >= 0)){
		pStrip->setPixelColor(xPrevIndex, PicoLed::RGB(0, 0, 0));
		pStrip->show();
	}
	xStep = 0;
	xPrevIndex = -1;
}

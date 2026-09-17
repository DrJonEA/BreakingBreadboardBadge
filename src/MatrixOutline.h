/*
 * MatrixOutline.h
 *
 * WS2812B matrix animation that lights a single pixel at a time as it
 * travels around the outer edge of a row-major wired WxH matrix.
 *
 *  Created on: 17 Sep 2026
 *      Author: jondurrant
 */

#ifndef WS2812B_ANIMATIONS_SRC_MATRIXOUTLINE_H_
#define WS2812B_ANIMATIONS_SRC_MATRIXOUTLINE_H_

#include "RingAnimation.h"

class MatrixOutline : public RingAnimation{
public:
	/***
	 * Default constructor
	 * SetStrip must be called after this
	 */
	MatrixOutline();

	/***
	 * Construct the object
	 * @param strip - PicoLed strip object
	 * @param width - number of columns in the matrix
	 * @param height - number of rows in the matrix
	 * @param colour - colour to use for the animation
	 * @param stepMS - time in milliseconds between each step of animation
	 */
	MatrixOutline(
			PicoLed::PicoLedController *strip,
			uint8_t width,
			uint8_t height,
			PicoLed::Color colour,
			uint16_t stepMS);

	/***
	 * Destructor
	 */
	virtual ~MatrixOutline();

	/***
	 * Reset animation to start position
	 */
	virtual void reset();

protected:
	/***
	 * Perform step of animation
	 */
	virtual void step();

private:
	/***
	 * Build the ordered list of strip indexes that trace the outer edge
	 * of the matrix, assuming row major (row * width + col) wiring
	 */
	void buildOutline();

	//Matrix dimensions
	uint8_t xWidth = 8;
	uint8_t xHeight = 8;

	//Step count
	uint8_t xStep = 0;

	//Strip index last lit, so it alone can be turned off on the next step
	int16_t xPrevIndex = -1;

	//Ordered strip indexes tracing the outline of the matrix
	uint8_t *pOutline = NULL;
	uint8_t xOutlineLen = 0;
};

#endif /* WS2812B_ANIMATIONS_SRC_MATRIXOUTLINE_H_ */

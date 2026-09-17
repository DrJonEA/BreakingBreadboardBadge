/*
 * PrideDiagonal.h
 *
 * WS2812B matrix animation restricted to the central 6x6 pixels of the
 * matrix, scrolling diagonal stripes of the pride flag colours at 45
 * degrees.
 *
 *  Created on: 17 Sep 2026
 *      Author: jondurrant
 */

#ifndef WS2812B_ANIMATIONS_SRC_PRIDEDIAGONAL_H_
#define WS2812B_ANIMATIONS_SRC_PRIDEDIAGONAL_H_

#include "RingAnimation.h"

class PrideDiagonal : public RingAnimation{
public:
	/***
	 * Default constructor
	 * SetStrip must be called after this
	 */
	PrideDiagonal();

	/***
	 * Construct the object
	 * @param strip - PicoLed strip object
	 * @param width - number of columns in the matrix
	 * @param height - number of rows in the matrix
	 * @param stepMS - time in milliseconds between each step of animation
	 */
	PrideDiagonal(
			PicoLed::PicoLedController *strip,
			uint8_t width,
			uint8_t height,
			uint16_t stepMS);

	/***
	 * Destructor
	 */
	virtual ~PrideDiagonal();

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
	//Number of stripe colours in the pride flag
	static const uint8_t COLOUR_COUNT = 6;

	//Size of the central square that is animated
	static const uint8_t CENTRAL_SIZE = 6;

	//Matrix dimensions
	uint8_t xWidth = 8;
	uint8_t xHeight = 8;

	//Top left offset of the central CENTRAL_SIZE x CENTRAL_SIZE square
	uint8_t xMarginX = 1;
	uint8_t xMarginY = 1;

	//Diagonal scroll offset
	uint8_t xOffset = 0;

	//Pride flag stripe colours, red to violet
	PicoLed::Color xColours[COLOUR_COUNT];
};

#endif /* WS2812B_ANIMATIONS_SRC_PRIDEDIAGONAL_H_ */

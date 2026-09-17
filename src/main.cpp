/*
 * main.cpp
 * Drive an 8x8 WB2812B matrix (64 LEDs) on GP25
 * Produce a chaser pattern
 *
 *  Created on: 15 Jun 2021
 *      Author: jondurrant
 */


#include "pico/stdlib.h"
#include <stdexcept>

#include <PicoLed.hpp>
#include "RingAnimation.h"
#include "RingChaser.h"
#include "TriTurn.h"
#include "DialUpDown.h"
#include "MatrixOutline.h"
#include "PrideDiagonal.h"

#define LEDS_PIN 25
#define MATRIX_WIDTH 8
#define MATRIX_HEIGHT 8
#define LEDS_LENGTH (MATRIX_WIDTH * MATRIX_HEIGHT)




int main(){

	stdio_init_all();

    // Initialize LED strip
	auto ledStrip = PicoLed::addLeds<PicoLed::WS2812B>(pio0, 0, LEDS_PIN, LEDS_LENGTH, PicoLed::FORMAT_GRB);

	//Keep brightness down as we are running at 3.3v
	ledStrip.setBrightness(34);

	// Initialise the LED to all off
	ledStrip.fill( PicoLed::RGB(0x00, 0x00, 0x00 ));
	ledStrip.show();
	sleep_ms(2000);


	PicoLed::Color c = PicoLed::RGB(0xFF, 0xA5, 0x00);
	MatrixOutline *matrixOutline =  new MatrixOutline(
					&ledStrip,
					MATRIX_WIDTH,
					MATRIX_HEIGHT,
					c,
					100);

	PrideDiagonal *prideDiagonal = new PrideDiagonal(
					&ledStrip,
					MATRIX_WIDTH,
					MATRIX_HEIGHT,
					150);

	// Run both animations at once - they occupy disjoint pixel regions
	// (the outer ring vs the central 6x6 square) so they don't conflict
	while(true){
		matrixOutline->poll();
		prideDiagonal->poll();
	}

}

/* Trevor Calderwood
 * Sound reactive LED necklace
 * Designed for use with Arduino Uno
 */
#include <avr/io.h>

/* -------------------------------- CONFIG --------------------------------- */
// Arduino board pins
#define LED_PIN PB3 // nano pin 11, must be capable of PWM output
#define LED_DDR DDRB
#define LED_PORT PORTB
#define MIC_PIN PC0 // nano pin A0, must allow analog reads
#define MIC_DDR DDRC
#define MIC_PORT PORTC
// sample and average defns
#define PEAK 1.9 // Max brightness when volume >= continuousAvg * PEAK
#define VALLEY 0.7 // Min brightness when volume <= continuousAvg * VALLEY
#define SAMPLE_TIME 10 // n milliseconds in volume sample in getVolume()
#define WINDOW_SIZE 50 // n averages in continuous window
#define RUNNING_ITERS 10 // n samples in local average in setup() and loop()
/* Tunings:
 * Arduino Uno: (5V): 2.0, 0.7, 20, 50, 3
 */

/* ------------------------------- HELPERS -------------------------------- */
// returns the volume (amplitude) of MIC sampled for SAMPLE_ITERS times
unsigned long int getVolume() {
	unsigned long int sample, volume;
	int max = 0;
	int min = 1023;
	
	unsigned long startTime = millis();
	while(millis() - startTime < SAMPLE_TIME) {
		sample = analogRead(MIC_PIN);
		if(sample > max) {
			max = sample;
		}
		if(sample < min) {
			min = sample;
		}
	}
	volume = max - min;
	return volume;
}

void lightLed(unsigned long int volume, unsigned long int average) {
	///
	int brightnesss = map(volume, average * VALLEY, average * PEAK, 0, 255);
	///
	brightness = constrain(brightness, 0, 255);
	///
	analogWrite(LED_PIN, brightness);
}

/* --------------------------------- MAIN ---------------------------------- */
int main() {
	unsigned long int volume;
	unsigned long int innerAvg;
	// continuous average is not divided by WINDOW_SIZE to increase accuracy
	unsigned long int continuousAvg = 0;
	// buffer of innerAvg's. Oldest val is replaced by newest val, each iter
	unsigned long int averageWindow[WINDOW_SIZE];
	int wx; // window index

	// set LED_PIN as output
	LED_DDR |= (1 << LED_PIN);
	// set MIC_PIN as input
	MIC_DDR &= (~(1 << LED_PIN));
	///
	digitalWrite(LED_PIN, HIGH);
	
	// get initial averages and fill window
	for(wx = 0; wx < WINDOW_SIZE; wx++) {
		innerAvg = 0;
		for(int i = 0; i < RUNNING_ITERS; i++) {
			volume = getVolume();
			innerAvg += volume;
		}
		innerAvg /= RUNNING_ITERS;
		averageWindow[wx] = innerAvg;
		continuousAvg += innerAvg;
	}
	wx = 0;
	///
	digitalWrite(LED_PIN, LOW);

	while(1) {
		// Calculate innerAvg for RUNNING_ITERS. Replaces oldest averageWindow[]
		// with innerAvg. Also light LEDs with each new volume reading.
		innerAvg = 0;
		// calculate inner average
		for(int j = 0; j < RUNNING_ITERS; j++) {
			volume = getVolume();
			innerAvg += volume;
			// * by WINDOW_SIZE because continuousAvg is not / by WINDOW_SIZE
			lightLed(volume * WINDOW_SIZE, continuousAvg); 
		}
		innerAvg /= RUNNING_ITERS;
		// update continuousAvg and replace oldest value in window
		continuousAvg -= averageWindow[wx];
		continuousAvg += innerAvg;
		averageWindow[wx] = innerAvg;
		wx++;
		if(wx == WINDOW_SIZE) {
			wx = 0;
		}
	}
}

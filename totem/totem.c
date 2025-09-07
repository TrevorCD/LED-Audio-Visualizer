/* Trevor Calderwood
 * Sound reactive LED necklace
 * Designed for use with Arduino Uno
 */
/* -------------------------------- CONFIG --------------------------------- */
/* DEBUG bits:
 * bit 1: Print Volume, Average, and Brightness in lightLED()
 * bit 2: Print "Complete window refresh" every time wx = 0
 * bit 3: Print iteration inside of getVolume
 * bit 4: Print milliseconds elapsed inside of getVolume() for each iteration
 */
#define DEBUG 1
// Arduino board pins
#define LED_PIN 11 // must be capable of PWM output
#define MIC_PIN A0 // must allow analog reads
#define BUTTON_PIN 5 // must have internal pullup
// sample and average defns
#define PEAK 1.9 // Max brightness when volume >= continuousAvg * PEAK
#define VALLEY 0.7 // Min brightness when volume <= continuousAvg * VALLEY
#define SAMPLE_TIME 10 // n milliseconds in volume sample in getVolume()
#define WINDOW_SIZE 50 // n averages in continuous window
#define RUNNING_ITERS 10 // n samples in local average in setup() and loop()
/* Tunings:
 * Arduino Uno: (5V): 2.0, 0.7, 20, 50, 3
 */

/* ------------------------------- GLOBALS -------------------------------- */
// continuous average. Is not divided by WINDOW_SIZE to increase accuracy
unsigned long int continuousAvg;
// window (buffer) of average values. Oldest value is replaced by newest value
unsigned long int averageWindow[WINDOW_SIZE];
int wx; // window index

/* ------------------------------- HELPERS -------------------------------- */
// returns the volume (amplitude) of MIC sampled for SAMPLE_ITERS times
unsigned long int getVolume() {
  #if DEBUG & 4
  int i = 0;
  #endif
  unsigned long int sample, volume;
  int max = 0;
  int min = 1023;

  unsigned long startTime = millis();
  while(millis() - startTime < SAMPLE_TIME) {
    #if DEBUG & 8
    Serial.println(millis() - startTime);
    #endif
    sample = analogRead(MIC_PIN);
    if(sample > max) {
      max = sample;
    }
    if(sample < min) {
      min = sample;
    }
    #if DEBUG & 4
    i++;
    #endif
  }
  #if DEBUG & 4
  Serial.println(i);
  #endif
  volume = max - min;
  return volume;
}

void lightLed(unsigned long int volume, unsigned long int average) {
  #if DEBUG & 1
  Serial.print("V: ");
  Serial.print(volume);
  Serial.print("  A: ");
  Serial.print(average);
  #endif

  int brightness = map(volume, average * VALLEY, average * PEAK, 0, 255);

  brightness = constrain(brightness, 0, 255);
  analogWrite(LED_PIN, brightness);

  #if DEBUG & 1
  Serial.print("  B: ");
  Serial.print(brightness);
  Serial.println();
  #endif
}

/* --------------------------------- MAIN ---------------------------------- */
void setup() {
  // pin init
  pinMode(LED_PIN, OUTPUT);
  pinMode(MIC_PIN, INPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  #if DEBUG
  Serial.begin(9600);
  #endif

  digitalWrite(LED_PIN, HIGH);
  unsigned long int volume;
  unsigned long int innerAvg;
  continuousAvg = 0;
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
  digitalWrite(LED_PIN, LOW);
}

void loop() {
	// Calculates innerAvg for RUNNING_ITERS. Replaces oldest averageWindow[]
	// with innerAvg. Also lights LEDs with each new volume reading.
	unsigned long int volume;
	unsigned long int innerAvg = 0;
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
        #if DEBUG & 2
		Serial.println("Complete window refresh");
        #endif
	}
}

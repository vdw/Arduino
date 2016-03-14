/*
  Led Bar Graph with Sensor Calibration

  created 2016
  by Dimitris Krestos (vdw)
 
  https://github.com/vdw/Arduino
*/

// These constants won't change:
const int sensorPin = A0;              // pin that the sensor is attached to
const int ledPin    = 9;               // pin that the LED is attached to

// variables:
int sensorValue     = 0;               // the sensor value
int sensorMin       = 1023;            // minimum sensor value
int sensorMax       = 0;               // maximum sensor value

int timer           = 100;             // The higher the number, the slower the timing.
int pinCount        = 6;               // the number of pins (i.e. the length of the array)
int ledPins[] = {  2, 3, 4, 5, 6, 7 }; // an array of pin numbers to which LEDs are attached

void setup() {

  // turn on LED to signal the start of the calibration period:
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);

  // calibrate during the first five seconds
  while (millis() < 5000) {
    sensorValue = analogRead(sensorPin);

    // record the maximum sensor value
    if (sensorValue > sensorMax) {
      sensorMax = sensorValue;
    }

    // record the minimum sensor value
    if (sensorValue < sensorMin) {
      sensorMin = sensorValue;
    }
  }

  // signal the end of the calibration period
  digitalWrite(13, LOW);
  
  // the array elements are numbered from 0 to (pinCount - 1).
  // use a for loop to initialize each pin as an output:
  for (int thisPin = 0; thisPin < pinCount; thisPin++) {
    pinMode(ledPins[thisPin], OUTPUT);
  }
  
  Serial.begin(9600);
}


void loop() {
  // read the sensor:
  sensorValue = analogRead(sensorPin);
  
  Serial.println(sensorValue);
  
  // map the result to a range from 0 to the number of LEDs:
  int ledLevel = map(sensorValue, sensorMin, sensorMax, 0, pinCount);

  // loop over the LED array:
  for (int thisPin = 0; thisPin < pinCount; thisPin++) {
    
    // if the array element's index is less than ledLevel,
    // turn the pin for this element off:
    if (thisPin < ledLevel) {
      digitalWrite(ledPins[thisPin], LOW);
    } else { 
      // turn on all pins higher than the ledLevel:
      digitalWrite(ledPins[thisPin], HIGH);
    }
  }
}

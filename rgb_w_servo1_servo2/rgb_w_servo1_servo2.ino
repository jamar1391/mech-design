#include <Wire.h>
#include <Servo.h>
#include "Adafruit_TCS34725.h"

/* Example code for the Adafruit TCS34725 breakout library */

/* Connect SCL    to analog 5
   Connect SDA    to analog 4
   Connect VDD    to 3.3V DC
   Connect GROUND to common ground */

/* Initialise with default values (int time = 2.4ms, gain = 1x) */
Adafruit_TCS34725 tcs = Adafruit_TCS34725();
Servo myservo;
Servo carriage;

/* Initialise with specific int time and gain values */
// Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);

void setup(void) {
  Serial.begin(9600);

  myservo.attach(9);
  carriage.attach(10);
  myservo.write(178);
  carriage.write(178);
  delay(2000);
  myservo.write(0);
  delay(2000);

  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }
}

void loop(void) {
  uint16_t r, g, b, c, colorTemp, lux;

  carriage.write(45);

  for (int i = 0; i <= 3; i++){
      tcs.getRawData(&r, &g, &b, &c);
      // colorTemp = tcs.calculateColorTemperature(r, g, b);
      colorTemp = tcs.calculateColorTemperature_dn40(r, g, b, c);
      lux = tcs.calculateLux(r, g, b);

      if ((colorTemp < 3500) && (c > 50)) {
        myservo.write(0);
        }
        
      else if ((colorTemp > 4300) && (colorTemp < 5300) && (c > 50)) {
        myservo.write(90);
        }
        
      else if ((colorTemp > 6800) && (colorTemp < 9100) && (c > 50)) {
        myservo.write(178);
        }
        
      delay(50);
    };
  delay(300);
  carriage.write(135);
  delay(500);

}

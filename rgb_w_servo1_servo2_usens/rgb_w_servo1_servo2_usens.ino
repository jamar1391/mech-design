#include <Wire.h>
#include <Servo.h>
#include "Adafruit_TCS34725.h"
#include <IRremote.h>
#include <IRremoteInt.h>

/* Initialise with default values (int time = 2.4ms, gain = 1x) */
Adafruit_TCS34725 tcs = Adafruit_TCS34725();
Servo myservo;
Servo carriage;
int avtime=1000;
int RECV_PIN = 8;          //  The digital pin that the signal pin of the sensor is connected to
IRrecv receiver(RECV_PIN);  //  Create a new receiver object that would decode signals to key codes
decode_results results;  

/* Initialise with specific int time and gain values */
// Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);

void setup(void) {
  Serial.begin(9600);

  receiver.enableIRIn();
  myservo.attach(9);
  carriage.attach(10);
  myservo.write(155);
  carriage.write(135);
  delay(2000);
//  myservo.write(0);
//  delay(2000);
  while (receiver.decode(&results)==0) {}
  
}

void loop(void) {
  uint16_t r, g, b, c, colorTemp, lux;

  carriage.write(138);

  delay(130);
  for (int i = 0; i < 10; i++){
      tcs.getRawData(&r, &g, &b, &c);
      // colorTemp = tcs.calculateColorTemperature(r, g, b);
      colorTemp = tcs.calculateColorTemperature_dn40(r, g, b, c);
      lux = tcs.calculateLux(r, g, b);

      if ((colorTemp < 3500) && (c > 35)) {
        myservo.write(185);
        }
        
      else if ((colorTemp > 4300) && (colorTemp < 6000) && (c > 35)) {
        myservo.write(155);
        }
        
      else if ((colorTemp > 6800) && (colorTemp < 9100) && (c > 35)) {
        myservo.write(120);
        }

//      Serial.print("Color Temp: ");Serial.print(colorTemp,DEC);
//      Serial.print("C: ");Serial.print(c,DEC);
//      Serial.println(" ");
      
//      delay(20);
    }; 
  delay(500);
  carriage.write(110);
  delay(300);

}

#include <Wire.h>
#include <Servo.h>
#include "Adafruit_TCS34725.h"
#include <IRremote.h>
#include <IRremoteInt.h>

/* Initialise with default values (int time = 2.4ms, gain = 1x) */
Adafruit_TCS34725 tcs = Adafruit_TCS34725();
Servo myservo;
Servo carriage;
int dly = 0;        // A variable to store the delay chosen in setup
int RECV_PIN = 8;          //  The digital pin that the signal pin of the sensor is connected to
int funnel = 155;          // The funnel position will be assigned to a variable which can later be used to change its position
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
    while (1) {
    if (receiver.decode(&results)) {
      Serial.println(results.value, HEX);
      if (results.value==0xFF4AB5) {
        Serial.println("Number 8");
        break;
        }
      if (results.value==0xFF52AD) {
        Serial.println("Number 9");
//        dly = 100;
        break;
        }
      if (results.value==0xFF6897) {
        Serial.println("Number 0");
        dly = 100;
        break;
        }
      if (results.value==0xFF30CF) {
        Serial.println("Number 1");
        dly = 200;
        break;
        }
      if (results.value==0xFF18E7) {
        Serial.println("Number 2");
        dly = 300;
        break;
        }
        
//      receiver.resume();
      }
    }
    receiver.resume();

    while (1) {
    if (receiver.decode(&results)) {
      Serial.println(results.value, HEX);
      if (results.value==0xFF02FD) {
        Serial.println("Begin");
        break;
        }
      }
  
}}

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
//        myservo.write(185);
          funnel = 185;
        }
        
      else if ((colorTemp > 4300) && (colorTemp < 6000) && (c > 35)) {
//        myservo.write(155);
          funnel = 155;
        }
        
      else if ((colorTemp > 6800) && (colorTemp < 9100) && (c > 35)) {
//        myservo.write(115);
          funnel = 115;
        }

//      Serial.print("Color Temp: ");Serial.print(colorTemp,DEC);
//      Serial.print("C: ");Serial.print(c,DEC);
//      Serial.println(" ");
      
//      delay(20);
    }; 
  delay(400);
  delay(dly);
  carriage.write(110);
  myservo.write(funnel);
  delay(300);

}

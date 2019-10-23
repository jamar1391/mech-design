#include <IRremote.h>
#include <IRremoteInt.h>

int RECV_PIN = 13;          //  The digital pin that the signal pin of the sensor is connected to
IRrecv receiver(RECV_PIN);  //  Create a new receiver object that would decode signals to key codes
decode_results results;     //  A varuable that would be used by receiver to put the key code into

void setup() {
  Serial.begin(9600);       //  Setup serial port to send key codes to computer
  receiver.enableIRIn();    //  Enable receiver so that it would start processing infrared signals

}


void loop() {

  receiver.decode(&results);
  Serial.println(results.value);

  if (results.value==16712445) {
    Serial.println("Check is good");
    };
    
  receiver.resume();
  delay(500);
}

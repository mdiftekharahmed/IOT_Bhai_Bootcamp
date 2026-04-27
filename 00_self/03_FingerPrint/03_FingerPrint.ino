#include <Adafruit_Fingerprint.h>
#include<SoftwareSerial.h>

SoftwareSerial fingSerial(2,3);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&fingSerial);

void setup(){
  Serial.begin(115200);
  Serial.println("Fingerprint Sensor Test");

  finger.begin(57600);
  if(finger.verifyPassword()){
    Serial.println("Sensor Working");
  }
  else{
    Serial.println("Sensor Not Found!");
    while(1);
  }

}

void loop(){
    

}


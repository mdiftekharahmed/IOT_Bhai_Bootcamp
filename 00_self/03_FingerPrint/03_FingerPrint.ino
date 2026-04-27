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
    //check finger availablity
    if(finger.getImage()!= FINGERPRINT_OK){
      return;
    }

    //convert to characteristics
    finger.image2Tz(1);

    //search against stored templates
    uint8_t p =finger.fingerSearch();
    if(p==FINGERPRINT_OK){
      Serial.print("Found ID #");
      Serial.print(finger.fingerID);
      Serial.print(" with confidence: ");
      Serial.println(finger.confidence);
    }
    else{
      Serial.println("No Match");
    }

    delay(1000);

}



void enrollFingerprint(uint8_t id){
  Serial.print("Enrolling ID #");
  Serial.println(id);
  while(finger.getImage()!=FINGERPRINT_OK);
  finger.image2Tz(1);
  Serial.println("Remove Finger");
  delay(2000);
  while(finger.getImage()!=FINGERPRINT_OK);
  finger.image2Tz(2);
  int ok = finger.createModel();
  if(ok==FINGERPRINT_OK){
    finger.storeModel(id);
    Serial.println("Stored");
  }
  else{
    Serial.println("Failed to create Model");
  }
}





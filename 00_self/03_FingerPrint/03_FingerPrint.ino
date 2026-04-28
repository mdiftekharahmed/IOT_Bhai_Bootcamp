#include <Adafruit_Fingerprint.h>
#include<SoftwareSerial.h>

SoftwareSerial fingSerial(2,3);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&fingSerial);

void setup(){
  Serial.begin(9600);
  Serial.println("Fingerprint Sensor Test");

  finger.begin(57600);
  if(finger.verifyPassword()){
    Serial.println("Sensor Working");
  }
  else{
    Serial.println("Sensor Not Found!");
    while(1);
  }
  Serial.println(finger.getTemplateCount());

}

char val=0;

void loop(){
    if(Serial.available()){
      val =Serial.read();
      if(val=='0'){
        Register(15);
      }
    }
    while(finger.getImage() != FINGERPRINT_OK);
    if(finger.image2Tz(1) != FINGERPRINT_OK) return;
    if(finger.fingerSearch()==FINGERPRINT_OK){
      Serial.print("ID: ");
      Serial.println(finger.fingerID);
    }
    else{
      Serial.println("No Match");
    }
}

uint16_t Register(uint16_t id){
  Serial.println("Place finger...");

  // Wait for first scan
  while (finger.getImage() != FINGERPRINT_OK);

  if (finger.image2Tz(1) != FINGERPRINT_OK) {
    Serial.println("Error processing first scan");
    return 0;
  }

  Serial.println("Remove finger...");
  delay(2000);

  // Wait for second scan
  Serial.println("Place same finger again...");
  while (finger.getImage() != FINGERPRINT_OK);

  if (finger.image2Tz(2) != FINGERPRINT_OK) {
    Serial.println("Error processing second scan");
    return 0;
  }

  // Create model
  if (finger.createModel() != FINGERPRINT_OK) {
    Serial.println("Error creating model");
    return 0;
  }

  // Store model
  if (finger.storeModel(id) != FINGERPRINT_OK) {
    Serial.println("Error storing model");
    return 0;
  }

  Serial.print("Registration success with ID: ");
  Serial.println(id);

  return 1;
}

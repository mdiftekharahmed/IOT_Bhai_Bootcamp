#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include <EEPROM.h>
#include <string.h>
#include <LiquidCrystal.h>
//address in EEPROM for strong slot list;
#define REGISTRY_BASE  (1024 - 16) //Bytes that stores id registry

//Define LED and Lock
#define Rled A5 //Red LED p
#define Gled A4 //Green LED

//Push Buttons
#define btn1 6
#define btn0 7

//DOOR LOCK
#define LOCK_PIN A3


//LCD Display
// previously LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
LiquidCrystal lcd(12, 11, 5, 4, 9, 8);


//BTN State detection
int waitForButton(unsigned long ms){
  unsigned long t = millis()+ ms;
  while(t<millis()){
    if(digitalRead(btn1)==LOW){

      while(digitalRead(btn1)==LOW);
      return 1;
    }
    if(digitalRead(btn0)==LOW){
      while(digitalRead(btn0)==LOW);
      return 0;
    }
  }
  return -1;
}

//DOOR LOCK UNLOCK OPERATIONS
void unlock() { digitalWrite(LOCK_PIN, HIGH);//Serial.println(F("Door Unlocked!"));
 }
void lock()   { digitalWrite(LOCK_PIN, LOW);Serial.println(F("Door Locked!"));}

//Registry: only once to clear the REGISTRY_BASE
void initRegistry(){
  for(int i = 0; i < 16; i++){
    EEPROM.update(REGISTRY_BASE + i, 0x00);  // zero out all 128 bits
  }
  Serial.println(F("Registry initialized."));
}

struct User{
  char roll[16];
  uint8_t role;
  bool active;
};

int changeRole(uint8_t fingerprintID){
  User rec;
  int addr = fingerprintID * sizeof(User);
  EEPROM.get(addr, rec);
  if(rec.role == 1) rec.role = 0;
  else rec.role = 1;
  EEPROM.put(addr, rec);
  return 0;
}

int delUser(uint8_t fingerprintID){
  User rec;
  int addr = fingerprintID * sizeof(User);
  EEPROM.get(addr, rec);
  rec.active = false;
  EEPROM.put(addr, rec);
  markSlot(fingerprintID, false);
  return 0;
}

SoftwareSerial fingSerial(2, 3);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&fingSerial);

String readSerialLine(){
  while(!Serial.available());
  return Serial.readStringUntil('\n');
}


bool slotOccupied(uint8_t id){
  uint8_t byteIndex = id / 8;
  uint8_t bitIndex  = id % 8;
  uint8_t val = EEPROM.read(REGISTRY_BASE + byteIndex);
  return (val >> bitIndex) & 1;
}

void markSlot(uint8_t id, bool value){
  uint8_t byteIndex = id / 8;
  uint8_t bitIndex  = id % 8;
  uint8_t val = EEPROM.read(REGISTRY_BASE + byteIndex);
  if(value) val |= (1 << bitIndex);
  else val &= ~(1 << bitIndex);

  EEPROM.update(REGISTRY_BASE + byteIndex, val);
}

int nextFreeSlot(){
  for(uint8_t i = 1; i < 128; i++){
    if(!slotOccupied(i)) return i;
  }
  return -1;
}
int Register(){
  int id = nextFreeSlot();
  if(id == -1){
    Serial.println(F("Fingerprint Storage Full, Please Delete first!"));
    return -1;
  }
  uint8_t fingerprintID = (uint8_t)id;
  Serial.println(F("========Registratoin========"));
  Serial.println(F("Enter roll: "));
  String roll = readSerialLine();
  roll.trim();
  Serial.println(F("Enter role (0=user, 1=admin): "));
  String roleStr = readSerialLine();
  roleStr.trim();
  uint8_t role = roleStr.toInt();
  User rec;
  strncpy(rec.roll, roll.c_str(), 16);
  rec.role = role;
  rec.active = true;

  Serial.println(F("User Details: "));

  Serial.print(F("roll: "));
  Serial.println(rec.roll);

  Serial.print(F("Role: "));
  Serial.println(rec.role == 1 ? F("Admin") : F("User"));

  Serial.print(F("Active: "));
  Serial.println(rec.active ? F("Yes") : F("No"));

  Serial.println(F("Are these details Correct? Proceed with registration? (Yea=1, No=0): "));

  String confirm = readSerialLine();
  confirm.trim();

  if(confirm != "1"){
    Serial.println(F("Registration Cancelled"));
    return 1;
  }

  else{

    Serial.println(F("====Fingerprint Enrollment===="));
    Serial.println(F("Place your finger to scanner: "));
    unsigned long timeout = millis() + 5000;

    while(finger.getImage() != FINGERPRINT_OK){
      if(millis() > timeout){
        Serial.println(F("Timeout!"));
        return -1;
      }
    }

    if(finger.image2Tz(1) != FINGERPRINT_OK){
      Serial.println(F("Error processing first image"));
    }

    //Duplicate check
    if(finger.fingerSearch() == FINGERPRINT_OK){

      Serial.print(F("Already Registered at ID: "));
      Serial.println(finger.fingerID);
      Serial.println(F("Rewrite data? (Yes=1, No=0)"));
      String cont = readSerialLine();
      cont.trim();
      if(cont == "1"){
        fingerprintID = finger.fingerID;
      }
      else{
        Serial.println(F("Exiting......"));
        return -1;
      }
    }
    Serial.println(F("Remove Finger and wait 2s"));
    timeout = millis() + 2000;
    while(timeout < millis());
    Serial.println(F("Place your finger to scanner again: "));
    timeout = millis() + 10000;
    while(finger.getImage() != FINGERPRINT_NOFINGER){
      if(millis() > timeout){
        Serial.println(F("Timeout"));
        return -1;
      }
    }

    timeout = millis() + 10000;
    while(finger.getImage() != FINGERPRINT_OK){
      if(millis() > timeout){
        Serial.println(F("Timeout!"));
        return -1;
      }
    }

    if(finger.image2Tz(2) != FINGERPRINT_OK){
      Serial.println(F("Error processing second image"));
    }

    if(finger.createModel() != FINGERPRINT_OK){
      Serial.println(F("Scan didn't match!"));
      return -1;
    }

    if(finger.storeModel(fingerprintID) != FINGERPRINT_OK){
      Serial.println(F("Error while storing data..."));
      return -1;
    }

    int addr = fingerprintID * sizeof(User);
    EEPROM.put(addr, rec);
    markSlot(fingerprintID, true);
    Serial.print(F("User ID: "));
    Serial.println(fingerprintID);
    Serial.println(F("Registration Successfull!"));

    return 0;
  }
}

void setup() {

  lcd.begin(16, 2);
  lcd.print("Hello World!");
  lcd.setCursor(0, 1);
  lcd.print("Row 3");

  Serial.begin(9600);
  finger.begin(57600);
  pinMode(Rled, OUTPUT);
  pinMode(Gled, OUTPUT);
  pinMode(LOCK_PIN, OUTPUT);
  pinMode(btn0, INPUT_PULLUP);
  pinMode(btn1, INPUT_PULLUP);

  if(finger.verifyPassword()){
    Serial.println(F("Fingerprint Initialized Successfully!"));
  }

  else{
    Serial.println(F("Error Detecting the Fingerprint Sensor!"));
  }
  Serial.print(F("Total registered fingerprints: "));
  finger.getTemplateCount();
  Serial.println(finger.templateCount);
  digitalWrite(Gled, HIGH);
}

void loop() {
  bool btn_1=0, btn_0=0;
  while(finger.getImage() != FINGERPRINT_OK){}
  if(finger.image2Tz(1) != FINGERPRINT_OK){
    Serial.println(F("Failed to process fingerprint!, Please try later"));
    return;
  }

  if(finger.fingerSearch() != FINGERPRINT_OK){

    Serial.println(F("Fingerprint Not Recognized! Intruder Detected"));
    unsigned long t = millis() + 2000;
    digitalWrite(Rled, HIGH);
    digitalWrite(Gled, LOW);
    while(millis() < t);
    digitalWrite(Rled, LOW);
    digitalWrite(Gled, HIGH);
  }

  else{
    int fingerprintID = finger.fingerID;
    unlock();//======================================door unlock======================
    User usr;
    int addr = fingerprintID * sizeof(User);
    EEPROM.get(addr, usr);
    Serial.println(F("Welcome to Lab!"));
    Serial.println(F("==============="));
    Serial.print(F("Roll: "));
    Serial.println(usr.roll);
    Serial.print(F("Role: "));
    Serial.println(usr.role == 1 ? F("Admin") : F("User"));
    Serial.print(F("Active: "));
    Serial.println(usr.active == 1 ? F("Active") : F("Inactive"));
    Serial.print(F("Fingerprint ID: "));
    Serial.println(fingerprintID);
    Serial.println(F("---------------"));
    Serial.println(F("Please remove your finger from scanner!"));
    Serial.println(F("==============="));
    while(finger.getImage() != FINGERPRINT_NOFINGER);
    lock();//==========================================door lock===========================
    if(usr.role==1){
      Serial.println(F("admin pannel (1, 0)"));
      unsigned long timeout = millis()+5000;
      String val = "";
      int v =waitForButton(5000);
      if(millis()<timeout && v == 1){
        Serial.println(F("Admin Pannel"));
        Serial.println(F("============"));
        Serial.println(F("1. Register/ Update"));
        Serial.println(F("2. Delete User"));
        Serial.println(F("3. Role Change"));
        Serial.println(F("4. Erase Database"));
        Serial.println(F("-----------------"));
        Serial.println(F("Choose one (0 to exit)"));
        Serial.println(F("============"));
        val = readSerialLine();
        val.trim();
        if(val == "1"){
          Register();
        }
        else if(val=="0"){}
        else if(val == "2"){
          Serial.println(F("Enter finger ID to delete: (0 to exit)"));
          String id = readSerialLine();
          val.trim();
          if(id!="0"){uint8_t fingerid = id.toInt();
          delUser(fingerid);
          finger.deleteModel(fingerid);}
          Serial.println(F("User deleted Successfully!"));
        }

        else if(val == "3"){
          Serial.println(F("Enter finger ID to change role: "));
          String id = readSerialLine();
          val.trim();
          if(id!="0"){uint8_t fingerid = id.toInt();
          changeRole(fingerid);}
          Serial.println(F("User role updated Successfully"));
        }

        else if(val == "4"){
          Serial.println(F("Disclaimer: This will erase entire user database, Do you want to Proceed? Yes=1, No=0"));
          String id = readSerialLine();
          val.trim();
          if(id == "1"){

            Serial.println(F("Erasing Database......."));
            initRegistry();
            Serial.println(F("RegistryBase deleted...."));
            if(finger.emptyDatabase() == FINGERPRINT_OK){
              Serial.println(F("Fingerprint Database Deleted...."));
            }
            else{
              Serial.println(F("Error deleting fingerprint Database!"));
            }
            Serial.println(F("Please register an Admin Account! Must select Yes in admin option"));
            Register();
          }
        }

        else{
          Serial.print(F("Invalid Input: "));
          Serial.println(val);
        }
      }
      else{
        Serial.println(F("Timeout!"));
      }
      }
  }
}
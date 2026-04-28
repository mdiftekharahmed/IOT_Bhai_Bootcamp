// #include<Adafruit_Fingerprint.h>
// #include<SoftwareSerial.h>
// #include<EEPROM.h>
// #include<string.h>

// //address in EEPROM for strong slot list;
// #define REGISTRY_BASE  (1024 - 16)

// //Define LED and Lock
// #define Rled 8
// #define Gled 9

// //Registry: only once to clear the REGISTRY_BASE
// void initRegistry(){
//   for(int i = 0; i < 16; i++){
//     EEPROM.update(REGISTRY_BASE + i, 0x00);  // zero out all 128 bits
//   }
//   Serial.println("Registry initialized.");
// }


// struct User{
//   char roll[16];    
//   uint8_t role;
//   bool active;
// };

// int changeRole(uint8_t fingerprintID){
//   User rec;
//   int addr = fingerprintID * sizeof(User);
//   EEPROM.get(addr, rec);
//   if(rec.role==1)rec.role=0;
//   else rec.role=1;
//   EEPROM.put(addr, rec);
//   return 0;
// }

// int delUser(uint8_t fingerprintID){
//   User rec;
//   int addr = fingerprintID * sizeof(User);
//   EEPROM.get(addr, rec);
//   rec.active = false;
//   EEPROM.put(addr, rec);
//   markSlot(fingerprintID, false);
//   return 0;  // was missing
// }

// SoftwareSerial fingSerial(2, 3);
// Adafruit_Fingerprint finger = Adafruit_Fingerprint(&fingSerial);

// String readSerialLine(){
//   while(!Serial.available());
//   return Serial.readStringUntil('\n');
// }


// // Get fingerprint id



// int Register(){

//   int id = nextFreeSlot();
//   if (id == -1){
//     Serial.println("Fingerprint Storage Full, Please Delete first!");
//     return -1;
//   }
//   uint8_t fingerprintID = (uint8_t)id;

//   Serial.println("========Registratoin========");
//   Serial.println("Enter roll: ");
//   String roll = readSerialLine();   // String, capital S
//   roll.trim();

//   Serial.println("Enter role (0=user, 1=admin): ");
//   String roleStr = readSerialLine();  // String, capital S
//   roleStr.trim();
//   uint8_t role = roleStr.toInt();

//   User rec;
//   strncpy(rec.roll, roll.c_str(), 16);  // can't assign array directly, use strncpy
//   rec.role = role;
//   rec.active = true;
//   // int addr = fingerprintID * sizeof(User);
//   Serial.println("User Details: ");
//   Serial.print("roll: ");    Serial.println(rec.roll);
//   Serial.print("Role: ");    Serial.println(rec.role == 1 ? "Admin" : "User");
//   Serial.print("Active: ");  Serial.println(rec.active ? "Yes" : "No");
//   Serial.println("Are these details Correct? Proceed with registration? (Yea=1, No=0): ");
//   String confirm = readSerialLine();
//   confirm.trim();
//   if(confirm!="1"){
//     Serial.println("Registration Cancelled");
//     return 1;
//   }
//   else{
//     Serial.println("====Fingerprint Enrollment====");
//     Serial.println("Place your finger to scanner: ");
//     unsigned long timeout = millis()+5000;
//     //get first scan
//     while(finger.getImage()!=FINGERPRINT_OK){if(millis()>timeout){Serial.println("Timeout!");return -1;}}
//     if(finger.image2Tz(1)!=FINGERPRINT_OK){Serial.println("Error processing first image");}

//     //Duplicate check
//     if(finger.fingerSearch()==FINGERPRINT_OK){
//       Serial.print("Aready Registered at ID: ");
//       Serial.println(finger.fingerID);
//       Serial.println("Rewrite data? (Yes=1, No=0)");
//       String cont = readSerialLine();
//       cont.trim();
//       //continue rewrite data
//       if(cont=="1"){
//         fingerprintID=finger.fingerID;
//         // addr = fingerprintID * sizeof(User);
//       }
//       //cancel registration
//       else{Serial.println("Exiting......");return -1;}

//     }

//     Serial.println("Remove Finger and wait 2s");
//     timeout= millis()+2000;
//     while(timeout<millis());
//     Serial.println("Place your finger to scanner again: ");
//     timeout=millis()+10000;
//     while(finger.getImage()!=FINGERPRINT_NOFINGER){
//       if(millis()>timeout){Serial.println("Timeout"); return -1;}
//     }

//     //get second scan
//     timeout =millis()+10000;
//     while(finger.getImage()!=FINGERPRINT_OK){if(millis()>timeout){Serial.println("Timeout!");return -1;}}
//     if(finger.image2Tz(2)!=FINGERPRINT_OK){Serial.println("Error processing second image");}
    
//     //create model
//     if(finger.createModel()!=FINGERPRINT_OK){Serial.println("Scan didn't match!"); return -1;}

//     //store model
//     if(finger.storeModel(fingerprintID)!=FINGERPRINT_OK){
//       Serial.println("Error while string data...");
//       return -1;
//     }
//     int addr = fingerprintID * sizeof(User);
//     EEPROM.put(addr, rec);
//     markSlot(fingerprintID, true);

//     Serial.print("User ID: ");
//     Serial.println(fingerprintID);
//     Serial.println("Registration Successfull!");
//     return 0;
//   }
// }


//   //checking slot if available
//   bool slotOccupied(uint8_t id){
//     uint8_t byteIndex = id/8;
//     uint8_t bitIndex  = id%8;
//     uint8_t val = EEPROM.read(REGISTRY_BASE + byteIndex);
//     return (val >> bitIndex) & 1;
//   }

//   //markslot occuped
//   void markSlot(uint8_t id, bool value){
//     uint8_t byteIndex = id/8;
//     uint8_t bitIndex  = id%8;
//     uint8_t val = EEPROM.read(REGISTRY_BASE + byteIndex);
//     if(value) val |= (1<<bitIndex);
//     else val &= ~(1<<bitIndex);
//     EEPROM.update(REGISTRY_BASE+byteIndex, val);
//   }

//   //get the next free slot

//   int nextFreeSlot(){
//     for(uint8_t i=1;i<128;i++){
//       if(!slotOccupied(i)) return i;
//     }
//     return -1; //means full
//   }




// void setup() {
//   Serial.begin(9600);
//   finger.begin(57600);

//   //LED, LOCK
//   pinMode(Rled, OUTPUT);
//   pinMode(Gled, OUTPUT);

//   if(finger.verifyPassword()){ Serial.println("Fingerprint Initialized Successfully!"); }
//   else{ Serial.println("Error Detecting the Fingerprint Sensor!"); }

//   Serial.print("Total registered fingerprints: ");
//   finger.getTemplateCount();
//   Serial.println(finger.templateCount);


//   // Register();
  

//   // User rec1;
//   // EEPROM.get(64, rec1);
//   // Serial.print("roll: ");    Serial.println(rec1.roll);
//   // Serial.print("Role: ");    Serial.println(rec1.role == 1 ? "Admin" : "User");
//   // Serial.print("Active: ");  Serial.println(rec1.active ? "Yes" : "No");


//   digitalWrite(Gled, HIGH);

// }

// void loop() {
  
//   while(finger.getImage()!=FINGERPRINT_OK){}
//   if(finger.image2Tz(1)!=FINGERPRINT_OK){
//     Serial.println("Failed to process fingerprint!, Please try later");
//     return;
//   }
//   if(finger.fingerSearch()!=FINGERPRINT_OK){
//     Serial.println("Fingerprint Not Recognized! Intruder Detected");
//     unsigned long t = millis()+2000;
//     digitalWrite(Rled, HIGH);
//     digitalWrite(Gled, LOW);
//     while(millis()<t);
//     digitalWrite(Rled, LOW);
//     digitalWrite(Gled, HIGH);
//   }
//   else{
//     int fingerprintID = finger.fingerID;
//     User usr;
//     int addr = fingerprintID * sizeof(User);
//     EEPROM.get(addr, usr);
//     Serial.println("Welcome to Lab!");
//     Serial.println("===============");
//     Serial.print("ROll: ");
//     Serial.println(usr.roll);
//     Serial.print("Role: ");
//     Serial.println(usr.role==1?"Admin":"User");
//     Serial.print("Active: ");
//     Serial.println(usr.active==1?"Active":"Inactive");
//     Serial.print("Fingerprint ID: ");
//     Serial.println(fingerprintID);
//     Serial.println("---------------");
//     Serial.println("Plese remove your fringer from scanner!");
//     Serial.println("===============");
//     while(finger.getImage() != FINGERPRINT_NOFINGER);
//     unsigned long timout = millis()+5000;
//     Serial.println("Wanna go to admin pannel? (Yes=1, No=0)");
//     String val = readSerialLine();
//     val.trim();
//     if(val=="1"){
//       Serial.println("Admin Pannel");
//       Serial.println("============");
//       Serial.println("0. Register/ Update");
//       Serial.println("1. Delete User");
//       Serial.println("2. Role Change");
//       Serial.println("3. Erase Database");
//       Serial.println("-----------------");
//       Serial.println("Choose one");
//       Serial.println("============");
//       val = readSerialLine();
//       val.trim();
//       if(val=="0"){
//         Register();
//       }
//       else if(val=="1"){
//         Serial.println("Enter finger ID to delete: ");
//         String id = readSerialLine();
//         val.trim();
//         uint8_t fingerid= id.toInt();
//         delUser(fingerid);
//         finger.deleteModel(fingerid);
//       }
//       else if(val=="2"){
//         Serial.println("Enter finger ID to change role: ");
//         String id = readSerialLine();
//         val.trim();
//         uint8_t fingerid= id.toInt();
//         changeRole(fingerid);
//       }
//       else if(val=="3"){
//         Serial.println("Disclaimer: This will erase entire user database, Do you want to Proceed? Yes=1, No=0");
//         Serial.println("Enter finger ID to delete: ");
//         String id = readSerialLine();
//         val.trim();
//         if(id=="1"){
//           Serial.println("Erasing Database.......");
//           initRegistry();
//           Serial.println("RegistryBase deleted....");
//           if(finger.emptyDatabase()==FINGERPRINT_OK){
//             Serial.println("Fingerprint Database Deleted....");
//           }
//           else{
//             Serial.println("Error deleting fingerprint Database!");
//           }
//           Serial.println("Please register an Admin Account! Must select Yes in admin option");
//           Register();
//         }
//       }
//       else{
//         Serial.print("Invalid Input: ");
//         Serial.println(val);
//       }
//     }
//   }


// }
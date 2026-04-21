#include<EEPROM.h>
int cnt_addr=13, flag_addr=102,counter =0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  byte flag=EEPROM.read(flag_addr);

  if(flag!= 0xAA){
    counter=0;
    EEPROM.put(cnt_addr,counter);
    EEPROM.write(flag_addr,0xAA);
  }
  else{
    EEPROM.get(cnt_addr,counter);
  }

  counter++;
  EEPROM.put(cnt_addr,counter);
  
  Serial.print("Boot count: ");
  Serial.println(counter);

}

void loop() {
  // put your main code here, to run repeatedly:
  

}

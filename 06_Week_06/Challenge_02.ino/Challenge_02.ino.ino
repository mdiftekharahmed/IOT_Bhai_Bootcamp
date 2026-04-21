#include<EEPROM.h>
#include<avr/wdt.h>
#include<avr/io.h>

int cnt_addr=18, flag_addr=101, counter=0, wtd_tre=5;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);


  byte mcusrCP= MCUSR;
  MCUSR=0;
  wdt_disable();

  byte flag= EEPROM.read(flag_addr);

 
  if(flag!=0xAA){
    counter = 0;
    EEPROM.put(cnt_addr,counter);
    EEPROM.write(flag_addr, 0xAA);
  }
  else{
    EEPROM.get(cnt_addr, counter);
  }
  

  
    counter++;
    EEPROM.put(cnt_addr,counter);
  
  

  Serial.print("WatchDog Reset count: ");
  Serial.println(counter);

  wdt_enable(WDTO_2S);

}

void loop() {
  wdt_reset();
  if(counter>wtd_tre){
    Serial.println("Entered safe mode!");
    wdt_disable();
  }
  Serial.println("Running infinitely");
  while(1){
  }
}




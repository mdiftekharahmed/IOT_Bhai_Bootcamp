
#define LED 13
#define inp 8
int st=0, stp=0, stT = 0, currT=0, charge = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(inp, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  stp = st;
  st = digitalRead(inp);


  if(st==HIGH && stp==LOW){
    stT = millis();
  }
  if(st==HIGH && stp==HIGH){
    if(millis()-stT==5000){
      if(charge!=5){charge>=5;
      Serial.println("Chargin: Level 5...");
      Serial.println("LASER FIRED");
      digitalWrite(LED, HIGH);}
    }else if(millis()-stT>=4000){
      if(charge!=4){charge=4;
      Serial.println("Chargin: Level 4...");}
    }else if(millis()-stT>=3000){
      if(charge!=3){charge=3;
      Serial.println("Chargin: Level 3...");}
    }else if(millis()-stT>=2000){
      if(charge!=2){charge=2;
      Serial.println("Chargin: Level 2...");}
    }else if(millis()-stT>=1000){
      if(charge!=1){charge=1;
      Serial.println("Chargin: Level 1...");}
    }
  }
  else if(st==LOW && stp==HIGH){
    if(millis()-stT< 5000){
      Serial.println("Charging Cancelled. Power Lost");
      stT = millis();
    }
    digitalWrite(LED, LOW);
    charge=0;
  }
  

  // if(stp != st){
  //   Serial.print("Current time: ");
  //   Serial.println(millis());
  // }


}


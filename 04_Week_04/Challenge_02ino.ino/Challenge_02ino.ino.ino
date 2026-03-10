const int potPin = A2, btn= 8, led=3;

void setup() {
  Serial.begin(9600);
  pinMode(potPin, INPUT);
  pinMode(btn, INPUT);
  pinMode(led, OUTPUT);
}

long time =0;
int prev=0, potVal = 0, btnSt=0, prev_btnSt=0, war=0, prev_war=-1;

bool prev_flag=0, flag=0, ack=0, ledst=0;

void loop() {
  prev_war= war;
  prev_btnSt=btnSt;
  prev=potVal;

  //CHECK BTN STATE
  btnSt=digitalRead(btn);

  //POTENTIOMETER
  potVal = analogRead(potPin);
  
  //PRINT STATUS
  int b = (int)(((float)potVal / 1023.0) * 250);
  if(prev<potVal-20 || prev > potVal+20){
    Serial.print("Status: WARNING | Sensor: ");
    Serial.print(potVal);
    Serial.print(" | PWM: ");
    Serial.println(b);
  }
  

  //Safe Zone 0-511: LED OFF
  if(potVal<512){
    war=0;
    analogWrite(led, 0);
    ack=0;
  }


  //WARNING ZONE 512 - 900: SCALABLE BRIGHTNESSS WITH POTENTIOMETER
  
  if(potVal>511 && potVal<901 ){
      war=1;
      int s = (int)(((float)(potVal-512)/420.0)*250);
      analogWrite(led, s);  
      ack=0;
      // Serial.print("printing: ");
      // Serial.println(s);
  }


  // //CRITICAl ZONE 901-1023: LED BLINK
  if(potVal>900){
    war=2;
  }

  
  if(war==2 && ack!=1){
      if(millis()-time>500){
        time = millis();
        digitalWrite(led, ledst);
        ledst = !ledst;
        
      }
    }
  else if(war==2){
    analogWrite(led, 250);
  }

      //BTN PRESS and LED ON FULL BRIGHTNESS
      if(btnSt==LOW && prev_btnSt==HIGH){
        ack=1;
        digitalWrite(led, HIGH);
        Serial.print("Danger Acknowledged!");
        // Serial.println(war);
      }




  if(prev_war!=war){
    Serial.print("Warning level: ");
    Serial.println(war);
  }

  delay(1);
}








// const int potPin = A2;

// void setup() {
//   Serial.begin(9600);
//   pinMode(potPin, INPUT);

// }

// int potVal = 0, prev_potVal =0;

// void loop() {
//   prev_potVal = potVal;
//   potVal = analogRead(potPin);
//   if(prev_potVal!=potVal){
//     Serial.print("Potentiometer Value: ");
//     Serial.println(potVal);

//   }

//   delay(1);
// }

const int potPin = A2, btn= 8, led=3;

void setup() {
  Serial.begin(9600);
  pinMode(potPin, INPUT);
  pinMode(btn, INPUT);
  pinMode(led, OUTPUT);
}


int prev=0, potVal = 0, btnSt=0, prev_btnSt=0;

bool prev_flag=0, flag=0;

void loop() {

  //CHECK BTN STATE
  prev_btnSt=btnSt;
  btnSt=digitalRead(btn);
  if(prev_btnSt==HIGH && btnSt==LOW){
    flag= !flag;
  }

  //POTENTIOMETER
  prev=potVal;
  potVal = analogRead(potPin);
  
  if(flag && (prev<potVal-20 || prev > potVal+20)){
    // Serial.print("Potentiometer Value: ");
    // Serial.println(potVal);

    int b = (int)(((float)potVal/ 1023.0) * 250);
    analogWrite(led, b);
    Serial.print("Brightness: ");
    Serial.println(b);
    
  }

  
  if(prev_flag!=flag && flag==0){
    Serial.println("SYSTEM OFF");
    analogWrite(led, 0);
  }
  prev_flag=flag;


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


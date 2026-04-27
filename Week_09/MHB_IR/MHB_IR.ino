#define lirPin 5
#define rirPin 2
#define ledPin 13

void setup() {
  // put your setup code here, to run once:
  pinMode(lirPin, INPUT);
  pinMode(rirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

int lstate=1, lprev_state=1, rstate=1, rprev_state=1;

void loop() {
  // put your main code here, to run repeatedly:
  lprev_state=lstate;
  lstate = digitalRead(lirPin);
  rprev_state=rstate;
  rstate= digitalRead(rirPin);

  if(lstate!=lprev_state)
  {  if(lstate==LOW){
      Serial.println("Object Detected on LEFT!");
      digitalWrite(ledPin, HIGH);
    }
    else{
      Serial.println("Road Clear");
      digitalWrite(ledPin, LOW);
    }
  }

  if(rstate!=rprev_state)
  {  if(rstate==LOW){
      Serial.println("Object Detected on RIGHT!");
      digitalWrite(ledPin, HIGH);
    }
    else{
      Serial.println("Road Clear");
      digitalWrite(ledPin, LOW);
    }
  }
}






// int irPin = A0;

// void setup() {
//   Serial.begin(9600);
// }

// void loop() {
//   int value = analogRead(irPin);
//   Serial.println(value);
//   delay(100);
// }

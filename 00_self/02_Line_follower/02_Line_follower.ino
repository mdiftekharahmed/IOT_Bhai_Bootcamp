//IR sensors
#define lirPin 5
#define rirPin 2
// Motor A
int ena = 10;
int in1 = 7;
int in2 = 8;
// Motor B
int enb = 6;
int in3 = 3;
int in4 = 4;

#define ledPin 13

const int n=5;//number of times the states to be inputted
int speed_l=0, speed_r=0;
int lstate=0, lprev_state=0, rstate=0, rprev_state=0;
int lstates[n], rstates[n];

void change_dir(int pwm, int val){
  analogWrite(pwm,val);
  return;
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ena, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enb, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(lirPin, INPUT);
  pinMode(rirPin, INPUT);

  //Enable PWM
  digitalWrite(ena, LOW);
  digitalWrite(enb, LOW);

  //turn on MOTOR
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

}

  int t=0;

void loop() {

  lprev_state=lstate;
  rprev_state=rstate;
  
  for(int i=0;i<n;i++){
    lstates[i]= digitalRead(lirPin);
    rstates[i]= digitalRead(rirPin);
  }
  for(int i=0;i<n;i++){
    lstate+=lstates[i];
    rstate+=rstates[i];  
  }
  lstate/=n;
  rstate/=n;

  if(lstate!=lprev_state){
    if(lstate==LOW){
      Serial.print(t);
      Serial.print(" : ");
      Serial.println("On Left line!");
    }
    else{Serial.println("Lost left Line");}
    t++;
  }
  

  if(rstate!=rprev_state){
    if(rstate==LOW){
      Serial.print(t);
      Serial.print(" : ");
      Serial.println("On right Line");
    }
    else{Serial.println("Lost right Line");}
    t++;
  }




}

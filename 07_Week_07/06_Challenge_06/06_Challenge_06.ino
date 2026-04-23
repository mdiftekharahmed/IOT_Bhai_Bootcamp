#include<EEPROM.h>

#define ECHO_PIN 2
#define TRIG_PIN 3
#define LED_R 12
#define LED_G 10
#define BUZZ 9
#define BTN 8

int Mem_Addr= 9;
float default_dist = 11;

long duration;
float distance_cm;
int alarm=0,btn_st=0, prev_btn_st=0;
const int n=5;
float arr[n];

int flag=0;



void sortArray(float arr[], int n){
  for(int i=0;i<n-1;i++){
    for(int j=i+1;j<n;j++){
      if(arr[i] > arr[j]){
        float temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
      }
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(BUZZ, OUTPUT);
  pinMode(BTN, INPUT);

  byte f= EEPROM.read(Mem_Addr);
  if(f!=0xAA){
    flag_addr, 0xAA
  }
}

void loop() {

  

  //========SENSOR DATA===========
  for(int i=0;i<n;i++){
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    duration = pulseIn(ECHO_PIN, HIGH,30000);
    distance_cm = duration * .0343 /2;
    arr[i]=distance_cm;

    delay(50);
  }
  
  sortArray(arr, n);
  float sum=0;
  for(int i=1;i<n-1;i++){
    sum+=arr[i];
  }
  Serial.print("Distance: ");
  Serial.print(sum/(n-2));
  Serial.println(" cm");


  if(abs(distance_cm - default_dist)> 5){
    Serial.print("Object Detected!! Turning on ALARM!")
    

  }



  //==========BUTTON =============
  prev_btn_st= btn_st;
  btn_st = digitalRead(BTN);

  if(prev_btn_st!=btn_st){
    Serial.print("Button st: ");
    Serial.println( btn_st);
  }
  if(btn_st==1){
    digitalWrite(LED_G, HIGH);
  }
  else{
    digitalWrite(LED_G, LOW);
  }



}

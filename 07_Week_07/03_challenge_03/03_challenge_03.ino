#define ECHO_PIN 2
#define TRIG_PIN 3
#define LED_R 12
#define LED_G 10
#define LED_B 11

long duration=0;
float distance_cm=0 ;
unsigned long scan =0, led=0, ledg=0,  intv=50;
int led_val=0, led_flag=1;
bool st=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  digitalWrite(LED_R, LOW);n
  digitalWrite(LED_B, LOW);
  digitalWrite(LED_G, LOW);
  scan = millis();
  led = millis();
  ledg=millis();
}

void loop() {
  //make the trig to low;
  
  if(millis()-scan>=100){
    scan=millis();

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  //send 10 microsecond pulse to trig
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH,30000); //30ms timeout cz pulseIn takes more than 1s if no echo
  distance_cm = duration * .0343 / 2;

  Serial.print("Distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");
  }

  if(led_val>245)led_flag=0;
  else if(led_val<=5)led_flag=1;
  
  if(millis()-ledg>10)
  {
    ledg=millis(); 
    if(led_flag)led_val+=1;
    else led_val-=1;
  }

  if(distance_cm>20){
    digitalWrite(LED_R, LOW);
    analogWrite(LED_G, led_val);
    

  }
  else if(distance_cm<=20){
    digitalWrite(LED_G, LOW);
    if(millis()-led >= intv){
      led =millis();
      st =!st;
      digitalWrite(LED_R, st);
    }
  }
  // put your main code here, to run repeatedly:

}

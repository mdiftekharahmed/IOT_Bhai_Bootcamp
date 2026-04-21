#define TRIG_PIN 3
#define ECHO_PIN 2
#define LED_G 10
#define LED_B 11
#define LED_R 12

long duration;
float distance_cm;
int freq;

void setup(){
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  digitalWrite(LED_R, LOW);
  digitalWrite(LED_G, LOW);
  digitalWrite(LED_B, LOW);
}
void loop(){
  //make sure TRIG is low;
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  //send 10 microsecond pulse to trig
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  //read ECHO pulse duration
  duration = pulseIn(ECHO_PIN, HIGH);

  //calculate distance in centemeters
  distance_cm = duration * 0.0343 /2;

  //print result
  // Serial.print("Distance: ");
  // Serial.print(distance_cm);
  // Serial.println(" cm");

  if(distance_cm <10){
    Serial.print("Danger Zone: ");
    Serial.print(distance_cm);
    Serial.println(" cm");
    digitalWrite(LED_R, HIGH);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_B, LOW);

  }
  else if(distance_cm>25){
    Serial.print("SafeZone: ");
    Serial.print(distance_cm);
    Serial.println(" cm");
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_G, HIGH);
    digitalWrite(LED_B, LOW);
  }
  else{
    Serial.print("Warning Zone: ");
    Serial.print(distance_cm);
    Serial.println(" cm");
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_B, HIGH);
  }

  delay(500);
}





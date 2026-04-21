#define TRIG_PIN 3
#define ECHO_PIN 2

long duration;
float distance_cm;

void setup(){
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
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
  Serial.print("Distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  delay(500);
}



void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

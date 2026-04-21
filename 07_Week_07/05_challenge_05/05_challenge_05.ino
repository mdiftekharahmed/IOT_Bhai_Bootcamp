#define ECHO_PIN 2
#define TRIG_PIN 3
#define LED_R 12
#define LED_G 10
#define LED_B 11
#define BUZZ 9

long duration=0;
float distance[2]={0.0,0.0};
float distance_cm=0;
long t;
int flag=0;
const int n=5;
float arr[n];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(BUZZ, OUTPUT);
  digitalWrite(LED_R, LOW);
  t=millis();
}

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



void loop() {

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

  distance_cm = sum/(n-2);

  Serial.print("Distance_NOW: ");
  Serial.print(distance_cm);
  Serial.println(" cm");


  if(!flag){
    distance[0]=distance_cm;
    flag=1;
  }
  else if(flag){
    distance[1]=distance_cm;
    flag=0;
  }
    


  float  vel = (max(distance[0], distance[1]) - min(distance[0],distance[1]))/.25;
  long intv =500,led;
  bool st=0;

  
  if((int)vel ==0 || vel > 0)
  {
    Serial.print("Velocity: ");
    Serial.print(vel);
    Serial.println(" cm/s");
  }
  else{
    Serial.print("Velocity: ");
    Serial.print(vel);
    Serial.println(" cm/s | System down!");
  }

  if(vel>15){
    Serial.println("WARNING: Ready for IMPACT!");
    digitalWrite(LED_R, HIGH);
    digitalWrite(BUZZ,HIGH);
    digitalWrite(LED_G, LOW);
  }
  else if(vel<=15){
    Serial.println("System Moving!");
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_G, HIGH);
    digitalWrite(BUZZ,LOW);

  }
  else{
    digitalWrite(BUZZ,LOW);
    digitalWrite(LED_R,LOW);
    digitalWrite(LED_G, LOW);
  }

  t=millis();
}

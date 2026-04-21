#define ECHO_PIN 2
#define TRIG_PIN 3

const int n=5;


long duration;
float distance_cm;
float arr[n];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);

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
  // put your main code here, to run repeatedly:
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


}
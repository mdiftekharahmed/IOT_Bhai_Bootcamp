#include<Servo.h>
#include<NewPing.h>

// ==========Ultrasonic===========
  #define echoPin A5
  #define trigPin A4
  #define maxDistance 200

  int readPing();
  int measureDistance();

// ============Servo Motor========
  #define servoPin 12

  void servoControl();
  void servoCenter();

// ============MOTORS==============
  #define motorLeft 6
  #define motorRight 11

  #define motor1pin1 2
  #define motor1pin2 3
  #define motor2pin1 5
  #define motor2pin2 4

  void stopMotor();
  void moveForward();
  void moveBackward();
  void turnLeft();
  void turnRight();
  void goForward();
  void goForTime(int time);



// Objects
  Servo myServo;
  NewPing sonar(trigPin, echoPin, maxDistance);

//Global Variables
  unsigned long t;
  bool go =true;
  int defAngle= 90;
  const int safeDistance= 20;
  int distance = 250;
  int direction = 0; //right -> +ve, left=-ve
  int pwmVal = 250;
  int moveFor = 20;
  int turnTime = 50;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myServo.attach(servoPin);
  myServo.write(defAngle);
  delay(200);

  // pinMode(trigPin, OUTPUT);
  // pinMode(echoPin, INPUT);
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1,  OUTPUT);
  pinMode(motor2pin2, OUTPUT);

  //(Optional)
  pinMode(motorLeft,  OUTPUT); 
  pinMode(motorRight, OUTPUT);
  //(Optional)

  distance = measureDistance();
  if(distance>safeDistance){
    go = true;
    Serial.println("System ready and running!");
  }
  else{
    go = false;
    Serial.println("Obstacle Detected!, move the machine at safe place before you start!");
  }

}

void loop() {

  servoControl(defAngle);
  int ldistance=250, rdistance=250;
  //if less more than 30 go ahed
  goForward();
  // moveForward();
  // else
  if(!go){
    if(distance<safeDistance){
      // look left and measure
      servoControl(0);
      ldistance= measureDistance();
      servoCenter();
      // look right and measure
      servoControl(180);
      rdistance= measureDistance();
      servoCenter();

      // if right dist > left dist
        if(rdistance> ldistance){
          // turn right
          turnRight();
          direction=1;
        }
        else{// else 
          turnLeft();
          direction=-1;
          // turn left
        }
        goForTime(50); //go forward for 50ms;
        // turn the oposite side
        if(direction >0)turnLeft();
        else if(direction < 0 )turnRight();

        goForTime(moveFor);

        if(direction >0){
          //look left and 
          servoControl(0);
          distance = measureDistance();
          servoCenter();
          if(distance> safeDistance)turnLeft();
        }
        else if(direction < 0 ){
          servoControl(180);
          distance = measureDistance();
          servoCenter();
          if(distance> safeDistance)turnRight();
        }
        goForTime(moveFor);
        if(direction >0)turnRight();
        else if(direction < 0 )turnLeft();
    }
  }
  
  
  
  
  direction= 0;
  go = true;
    // delay(1000);
  
}


// Function definition
void goForward(){
  while(go){
    moveForward();
    // servoControl(defAngle);
    // measure forward distance
    distance = measureDistance();
      Serial.print("Distance: ");
      Serial.println(distance);

    if(distance < safeDistance){
      go= false;
      stopMotor();
      Serial.println("Obstacle Detected!");
    }
    else {go = true;Serial.println("Going!");}
  }
}
void goForTime(int time){
    // move for 50ms
  moveForward();
  // goForward();
  unsigned long st = millis();
  while(millis()-st<time);
  stopMotor();
}

int readPing() {
  delay(30);
  int cm = sonar.ping_cm();
  if (cm == 0)cm = 250;
  return cm;
}

void servoControl(int angle){
  Serial.print("Servo at deg: ");
  Serial.println(angle);
  myServo.write(angle);
  unsigned long t = millis();
  while(millis()-t<400);
}

void stopMotor(){
  analogWrite(motorLeft, 0);
  analogWrite(motorRight, 0);
  Serial.println("Motor stopped!");
}

void moveForward(){
  analogWrite(motorLeft, pwmVal);
  analogWrite(motorRight, pwmVal);
  Serial.println("inside moveforward");

  digitalWrite(motor1pin1,  HIGH);
  digitalWrite(motor1pin2, LOW);

  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
  // delay(100);
}

void moveBackward(){
  analogWrite(motorLeft, pwmVal);
  analogWrite(motorRight, pwmVal);

  digitalWrite(motor1pin1,  LOW);
  digitalWrite(motor1pin2, HIGH);

  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);
}

void turnLeft(){
  analogWrite(motorLeft, pwmVal);
  analogWrite(motorRight, pwmVal);

  digitalWrite(motor1pin1,  HIGH);
  digitalWrite(motor1pin2, LOW);

  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);
  // unsigned long time = millis();
  // while(millis()-time < turnTime);
  // stopMotor();
  delay(150);
}
void turnRight(){
  
  analogWrite(motorLeft, pwmVal);
  analogWrite(motorRight, pwmVal);

  digitalWrite(motor1pin1,  LOW);
  digitalWrite(motor1pin2, HIGH);

  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);

  // unsigned long time = millis();
  // while(millis()-time < turnTime);

  // stopMotor();
  delay(150);
}

int measureDistance(){
  int arr[5]={0,0,0,0,0};
  for(int i=0;i<5;i++){
    arr[i]=readPing();
  }

  // Bubble Sort
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4 - i; j++) {
      if (arr[j] > arr[j + 1]) {
        int temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }

  return (int)((arr[1]+arr[2]+arr[3])/3);
}

void servoCenter(){
  servoControl(defAngle);
}

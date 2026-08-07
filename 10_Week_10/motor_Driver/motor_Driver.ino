#define motorLeft 9
#define motorRight 10

int motor1pin1 = 2;
int motor1pin2 = 3;

int motor2pin1 = 5;
int  motor2pin2 = 4;


void stopMotor();
void moveForward();
void moveBackward();
void turnLeft();
void turnRight();



void setup() {
  // put your setup code here, to run once:
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1,  OUTPUT);
  pinMode(motor2pin2, OUTPUT);

  //(Optional)
  pinMode(9,  OUTPUT); 
  pinMode(10, OUTPUT);
  //(Optional)
}

void loop() {
  // put your main code here, to run repeatedly:

  //Controlling speed (0  = off and 255 = max speed):     
  //(Optional)
  // stopMotor();
  moveForward();

  // delay(3000);

  // stopMotor();
  delay(1000);

  // turnLeft();

  delay(1000);

  // turnRight();
  // delay(1000);

  moveBackward();
  delay(3000);
}



void stopMotor(){
  analogWrite(motorLeft, 0);
  analogWrite(motorRight, 0);
  Serial.println("Motor stopped!");
}

void moveForward(){
  analogWrite(motorLeft, 100);
  analogWrite(motorRight, 100);

  digitalWrite(motor1pin1,  HIGH);
  digitalWrite(motor1pin2, LOW);

  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
}

void moveBackward(){
  analogWrite(motorLeft, 100);
  analogWrite(motorRight, 100);

  digitalWrite(motor1pin1,  LOW);
  digitalWrite(motor1pin2, HIGH);

  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);
}

void turnLeft(){
  analogWrite(motorLeft, 100);
  analogWrite(motorRight, 100);

  digitalWrite(motor1pin1,  HIGH);
  digitalWrite(motor1pin2, LOW);

  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);
}
void turnRight(){
  
  analogWrite(motorLeft, 100);
  analogWrite(motorRight, 100);

  digitalWrite(motor1pin1,  LOW);
  digitalWrite(motor1pin2, HIGH);

  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
}



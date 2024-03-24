//Right motor
int enableRightMotor=10;
int rightMotorPin1=9;
int rightMotorPin2=8;

//Left motor
int enableLeftMotor=11;
int leftMotorPin1=6;
int leftMotorPin2=7;
// Define pins for ultrasonic sensor
const int trigPin =2;
const int echoPin = 3;

// Define distance threshold
const int distanceThreshold = 50; // in centimeters


void setup() {
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);

  // Ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Initialize Serial Monitor
  Serial.begin(9600);


}

void loop() {
  
  int distance = getDistance();
  Serial.print("Distance: ");
  Serial.println(distance);

  if(distance<=10){
    rotateMotor(0,0);
    if(distance<=10){
      obstacleAvoidance();
    }
    if(distance<=5){
      rotateMotor(-90,-90);
    }
  }else{
    moveForward();
  }
  
}

void rotateMotor(int rightMotorSpeed, int leftMotorSpeed)
{
  
  if (rightMotorSpeed < 0)
  {
    digitalWrite(rightMotorPin1,LOW);
    digitalWrite(rightMotorPin2,HIGH);    
  }
  else if (rightMotorSpeed > 0)
  {
    digitalWrite(rightMotorPin1,HIGH);
    digitalWrite(rightMotorPin2,LOW);      
  }
  else
  {
    digitalWrite(rightMotorPin1,LOW);
    digitalWrite(rightMotorPin2,LOW);      
  }

  if (leftMotorSpeed < 0)
  {
    digitalWrite(leftMotorPin1,LOW);
    digitalWrite(leftMotorPin2,HIGH);    
  }
  else if (leftMotorSpeed > 0)
  {
    digitalWrite(leftMotorPin1,HIGH);
    digitalWrite(leftMotorPin2,LOW);      
  }
  else 
  {
    digitalWrite(leftMotorPin1,LOW);
    digitalWrite(leftMotorPin2,LOW);      
  }
  analogWrite(enableRightMotor, abs(rightMotorSpeed));
  analogWrite(enableLeftMotor, abs(leftMotorSpeed));    
}

int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  return pulseIn(echoPin, HIGH) / 58; // Divide by 58 to convert microseconds to centimeters
}
void moveForward(){
  rotateMotor(75,75);
}
void obstacleAvoidance(){

  rotateMotor(45,0);

}

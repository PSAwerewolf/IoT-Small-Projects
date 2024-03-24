#define enA 10 // Enable1 L298 Pin enA
#define in1 9  // Motor1  L298 Pin in1
#define in2 8  // Motor1  L298 Pin in1
#define in3 7  // Motor2  L298 Pin in1
#define in4 6  // Motor2  L298 Pin in1
#define enB 5  // Enable2 L298 Pin enB
#define echo A2    // Echo pin
#define trigger A3 // Trigger pin
#define servo A5

#define MOTOR_SPEED 180

//Right motor
int enableRightMotor=6;
int rightMotorPin1=7;
int rightMotorPin2=8;

//Left motor
int enableLeftMotor=5;
int leftMotorPin1=9;
int leftMotorPin2=10;
int Set = 15;
int distance_F;

void setup() {
  Serial.begin(9600);
  pinMode(echo, INPUT);    // declare ultrasonic sensor Echo pin as input
  pinMode(trigger, OUTPUT); // declare ultrasonic sensor Trigger pin as Output
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enB, OUTPUT);
  

  distance_F = Ultrasonic_read();
  delay(500);
}

void loop() {
  distance_F = Ultrasonic_read();
  Serial.print("D F="); Serial.println(distance_F);

  if (distance_F > Set) {
    forward();
  } else {
    obstacleAvoidance(distance_F);
  }

  delay(10);
}



long Ultrasonic_read() {
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  long time = pulseIn(echo, HIGH);
  return time / 29 / 2;
}

void obstacleAvoidance(int distance) {
  stop();
  Serial.print("Object Detected at Distance: ");
  Serial.println(distance);
  delay(1000); // Print the message for 1 second, adjust as needed
  // Add your specific obstacle avoidance logic here
  // For example, you can turn the robot left or right based on the obstacle position.
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

void forward()
{
  rotateMotor(180,180);
}

void stop()
{
  rotateMotor(0,0);
}


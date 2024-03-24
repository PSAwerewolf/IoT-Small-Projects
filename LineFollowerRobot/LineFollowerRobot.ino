#define Joystick_vrY A1
#define Joystick_vrX A2
#define MOTOR_SPEED 50


//Enable Two Motors
int enableRightMotor=10;
int enableLeftMotor=5;

//Right Motor Input
int rightMotorPin1=9;
int rightMotorPin2=8;

//Left Motor Input
int leftMotorPin1=6;
int leftMotorPin2=7;

void setup()
{
  //The problem with TT gear motors is that, at very low pwm value it does not even rotate.
  //If we increase the PWM value then it rotates faster and our robot is not controlled in that speed and goes out of line.
  //For that we need to increase the frequency of analogWrite.
  //Below line is important to change the frequency of PWM signal on pin D5 and D6
  //Because of this, motor runs in controlled manner (lower speed) at high PWM value.
  //This sets frequecny as 7812.5 hz.
  //TCCR0B = TCCR0B & B11111000 | B00000010 ;
  
  // put your setup code here, to run once:
  pinMode(enableRightMotor, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);
  
  pinMode(enableLeftMotor, OUTPUT);
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);

  pinMode(Joystick_vrX, INPUT);
  pinMode(Joystick_vrY, INPUT);
  rotateMotor(0,0);   

  Serial.begin(9600);
}


void loop()
{

  int XValue = analogRead(Joystick_vrX);
  int YValue = analogRead(Joystick_vrY);


Serial.println("X Value:");
Serial.println(XValue);
Serial.println("Y Value:");
Serial.println(YValue);

  
  //If none of the sensors detects black line, then go straight
  //UP
  if ( XValue==0 && YValue>0 )
  {
    digitalWrite(13,OUTPUT);
    rotateMotor(MOTOR_SPEED, MOTOR_SPEED);
  }
  //Right
  else if(XValue==1023 && YValue<1023){
    rotateMotor(0,45);
  }
  //Left
  else if(XValue<1023 && YValue==1023)
  {
    rotateMotor(45,0);
  }
  //Down
  else if(XValue==1023 && YValue==514){
    rotateMotor(-45,-45);
  }
  else{
    rotateMotor(0,0);
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

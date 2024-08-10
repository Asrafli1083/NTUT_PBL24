#define carSpeed 150
#define carSpeed2 150
#include <Servo.h>  //servo library
Servo myservo;      // create servo object to control servo

// Initialization
int IN1 = 4; //set L298n PIN
int IN2 = 5;
int IN3 = 6;
int IN4 = 7;
int ENA = 8;
int ENB = 9;
int rightDistance = 0, leftDistance = 0;
//Ultrasonic sensor variables
int Echo = A4;  
int Trig = A5; 

int keep_turning_time = 0;

int Distance_test() {
  digitalWrite(Trig, LOW);   
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);  
  delayMicroseconds(20);
  digitalWrite(Trig, LOW);   
  float Fdistance = pulseIn(Echo, HIGH);  
  Fdistance= Fdistance / 58;       
  return (int)Fdistance;
}

void setup() {
myservo.attach(3);  // attach servo on pin 3 to servo object
pinMode(IN1, OUTPUT); // Arduino control a car using output voltage
pinMode(IN2, OUTPUT);
pinMode(IN3, OUTPUT);
pinMode(IN4, OUTPUT);
pinMode(ENA, OUTPUT);
pinMode(ENB, OUTPUT);
pinMode(Trig, OUTPUT); // Sets the trigPin as an Output
pinMode(Echo, INPUT); // Sets the echoPin as an Input
Serial.begin(9600); // Starts the serial communication
}

void loop() {
  // myservo.write(60);  //setservo position to right side
  // delay(200); 
  // rightDistance = Distance_test();

  // myservo.write(120);  //setservo position to left side
  // delay(200); 
  // leftDistance = Distance_test();


  // if((rightDistance > 70)&&(leftDistance > 70)){
  //   stop();
  // }else if((rightDistance >= 20) && (leftDistance >= 20)) {     
  //   forward();
  // }else if((rightDistance <= 10) && (leftDistance <= 10)) {
  //     back();
  //     delay(100);
  // }else if(rightDistance - 3 > leftDistance) {
  //     left();
  //     delay(100);
  // }else if(rightDistance + 3 < leftDistance) {
  //     right();
  //     delay(100);
  // }else{
  //   stop();
  // }
    
  // forward();
  // delay(4000);
  // stop();
  // delay(500);
  // right();
  // delay(500);
  // stop();

    // Clears the trigPin
  digitalWrite(Trig, LOW);
  delayMicroseconds(400);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  double duration = pulseIn(Echo, HIGH, 35000);
  // Calculating the distance
  int distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  if ((distance >= 15 || distance == 0) && keep_turning_time <= 0) {
    // Serial.print(distance);
    // Serial.println("cm");
    forward();
  }else{
    if (!(distance >= 15 || distance == 0)) keep_turning_time = 13;
    if (keep_turning_time) --keep_turning_time;
    right();
    delay(50);
    stop();
    delay(100);
  }
}

void forward(){ 
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("Forward");
}

void back() {
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("Back");
}
void left() {
  analogWrite(ENA, carSpeed2);
  analogWrite(ENB, carSpeed2);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH); 
  Serial.println("Left");
}
void right() {
  analogWrite(ENA, carSpeed2);
  analogWrite(ENB, carSpeed2);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("Right");
}
void stop() {
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW); 
  Serial.println("Stop!");
}
#include <Servo.h> 

Servo myServo;

int servoPin = 7;
int minAngle = 30;
int maxAngle = 150;
int currentAngle;

int speed = 20;

#define trigPin 10
#define echoPin 11
#define buzzerPin 12

long duration;
int distance;

int buzzerKatsayisi;

void setup(){
  pinMode(buzzerPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  currentAngle = 90;
  myServo.write(90);
  myServo.attach(servoPin);
  buzzerKatsayisi = 5;
}

void loop() { 

  for (int angle = minAngle; angle <= maxAngle; angle++) {
    myServo.write(angle); 
    delay(speed);
    currentAngle = angle;
    distance = range();

    Serial.print(currentAngle);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");
    buzzerSesi(distance);
  }

  for (int angle = maxAngle; angle >= minAngle; angle--) {
    myServo.write(angle);
    delay(speed);
    currentAngle = angle;
    distance = range();

    Serial.print(currentAngle);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");
    buzzerSesi(distance);
  }
  
}
void buzzerSesi(int mesafe){
  if(mesafe > 40){
    digitalWrite(buzzerPin, LOW);
  }
  else if(mesafe <= 40 && mesafe > 30){
    digitalWrite(buzzerPin, HIGH);
    delay(mesafe * (buzzerKatsayisi + 4));
    digitalWrite(buzzerPin, LOW);
    delay(mesafe * (buzzerKatsayisi + 4));
  }
  else if(mesafe <= 30 && mesafe > 20){
    digitalWrite(buzzerPin, HIGH);
    delay(mesafe * (buzzerKatsayisi + 3));
    digitalWrite(buzzerPin, LOW);
    delay(mesafe * (buzzerKatsayisi + 3));
  }
  else if(mesafe <= 20 && mesafe > 10){
    digitalWrite(buzzerPin, HIGH);
    delay(mesafe * (buzzerKatsayisi + 2));
    digitalWrite(buzzerPin, LOW);
    delay(mesafe * (buzzerKatsayisi + 2));
  }
  else if(mesafe <= 10 && mesafe > 0){
    digitalWrite(buzzerPin, HIGH);
    delay(mesafe * (buzzerKatsayisi + 1));
    digitalWrite(buzzerPin, LOW);
    delay(mesafe * (buzzerKatsayisi + 1));
  }
  else{
    digitalWrite(buzzerPin, LOW);
  }
}


int range(){
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  duration = pulseIn(echoPin, HIGH);
  
  distance = duration * 0.0344 / 2;
  delayMicroseconds(5);
  
  
  return distance;
}

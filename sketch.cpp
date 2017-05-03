#include <Servo.h>

Servo myServo;
int const servoPin = 9;
int angle = 90;
int speed = 4;

void setup() {
  myServo.attach( servoPin );
  myServo.write( angle );
  delay(15);
  
  Serial.begin(9600);
  Serial.println("a");
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  if(Serial.available()>0) {
    char receivedChar = Serial.read();
    if( receivedChar == 'r' ) {
      angle = angle + speed;
      angle = min(angle, 179);
    } else if( receivedChar == 'l' ) {
      angle = angle - speed;
      angle = max(angle, 0);
    }
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }

  myServo.write( angle );
  delay(15);
}

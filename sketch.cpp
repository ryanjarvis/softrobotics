#include <Servo.h>

Servo the_servo;
int const servoPin = 9;

int angle = 90;

char command_verb = 'a';
char command_amount[4];
int ca_index = 0;

void reset_command() {
  memset(command_amount, 0, sizeof(command_amount));
  ca_index = 0;
  command_verb = 'a';
}

void add_to_command(char input) {
  if(isDigit(input)) {
    command_amount[ca_index] = input;
    ca_index++;
  } else if (isAlpha(input)) {
    command_verb = input;
  }

  if(ca_index >= sizeof(command_amount)) {
    ca_index = sizeof(command_amount) - 1;
  }
}

void run_command() {
  if(command_amount[0] == '\0') {
    reset_command();
    return;
  }
  
  int amount = atoi(command_amount);
  
  switch(command_verb) {
    case 'a':
      angle = amount;
      break;
    case 'r':
      angle = angle + amount;
      break;
    case 'l':
      angle = angle - amount;
      break;
  }
  
  constrain(angle, 0, 179);
  the_servo.write(angle);
  delay(15);

  reset_command();
}

void setup() {
  the_servo.attach( servoPin );
  the_servo.write( angle );
  delay(15);

  reset_command();

  Serial.begin(9600);
  Serial.println("a");
}

void loop() {
  if(Serial.available()>0) {
    char incoming = Serial.read();
    if(incoming == '\n') {
      run_command();
    } else {
      add_to_command(incoming);
    }
  }
}

#include <Servo.h>
const int StepPin = 5;
const int DirPin = 6;
const int UpperSwitch  = 7;
const int IR_Sensor1 = 10;
Servo name_servo;
int servo_position = 0;

void setup() {
  name_servo.attach (9);
  name_servo.write(110);
  pinMode(StepPin, OUTPUT);
  pinMode(DirPin, OUTPUT);
  pinMode(UpperSwitch , INPUT);
  pinMode(IR_Sensor1 , INPUT);


  while ( digitalRead( UpperSwitch) == HIGH ) {
    digitalWrite(DirPin, LOW); // Gantry Up
    Homing (1);
  }
}

void loop() {
  int Sensor1  =  digitalRead( IR_Sensor1);

  // Conveyor moves till sensor reads high , sensor is high so it stops

  if ( Sensor1 == LOW ) // IR low : object detected
  {{
      GantryDown ();
    }
    delay (500);
    name_servo.write(155);  //servo closes
    delay ( 500) ;

    digitalWrite ( DirPin , LOW ) ; // Gantry Up
    motorStep2 (1) ;

    // Conveyor moves with the lower part
    delay (3000) ;

    { digitalWrite ( DirPin , HIGH ) ; // Gantry Down
      motorStep3 (1) ;
    }
    delay (500);
    name_servo.write(110); //servo opens
    delay (500);

    while ( digitalRead( UpperSwitch) == HIGH ) {
      digitalWrite(DirPin, LOW); // Gantry Up
      Homing (1);
      }
    delay (3000) ;
  }
}

// Conveyor moves normally

void motorStep( int Steps) {
for (int n = 0; n < 2; n++){
  for (int x = 0; x < 24000; x++) {
    digitalWrite(StepPin, HIGH);
    delayMicroseconds(35);
    digitalWrite(StepPin, LOW);
    delayMicroseconds(35);
  }}
}

void motorStep2( int Steps) {

  for (int x = 0; x < 17000; x++) { // 2000 as when gantry is going down to release , it can't stop by the limit , it must be calibrated by steps
    digitalWrite(StepPin, HIGH);
    delayMicroseconds(35);
    digitalWrite(StepPin, LOW);
    delayMicroseconds(35);
  }
}
void motorStep3( int Steps) {

  for (int x = 0; x < 22000; x++) {
    digitalWrite(StepPin, HIGH);
    delayMicroseconds(35);
    digitalWrite(StepPin, LOW);
    delayMicroseconds(35);
  }
}


void Homing ( int Stepss) {
  for (int i = 0; i < Stepss; i++) {
    digitalWrite(StepPin, HIGH);
    delayMicroseconds(30);
    digitalWrite(StepPin, LOW);
    delayMicroseconds(30);
  }
}
void GantryDown (void) {
  { digitalWrite ( DirPin , HIGH ) ; // Gantry Down
    motorStep (1) ;
  }
}

void GantryUp (void) {
  { digitalWrite(DirPin, LOW); // Gantry Up
    motorStep (1) ;
  }
}

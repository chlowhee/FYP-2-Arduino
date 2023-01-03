#include "MeMCore.h"

MeDCMotor motorLeft(M1);
MeDCMotor motorRight(M2);

uint8_t MOTORSPEED = 200;
uint16_t MOTORSPEEDTURN = 300;

void setup() {
  Serial.begin(115200);
  Serial.println("K");
}

void loop() {
  char piCmd = 'z';
  while (Serial.available()) {
    piCmd = Serial.read();

    switch(piCmd) {
      case 'A':
//        motorMove(1);
        joystickMovement(1);
//        Serial.println("fwd");
        Serial.println("K");
        break;

      case 'B':
//        motorMove(2);
        joystickMovement(2);
//        Serial.println("bwd");
        Serial.println("K");
        break;

      case 'C':
//        motorMove(3);
        joystickMovement(3);
//        Serial.println("R90");
        Serial.println("K");
        break;

      case 'D':
//        motorMove(4);
        joystickMovement(4);
//        Serial.println("L90");
        Serial.println("K");
        break;

      case 'E':
        motorMove(5);
//        Serial.println("R45");
        Serial.println("K");
        break;

      case 'F':
        motorMove(6);
//        Serial.println("L45");
        Serial.println("K");
        break;

       case 'G':
//        motorMove(7);
        dance();
        break;
        
      case 'b':
        Serial.println("Jas a pi");
        break;

      default:
        break;
    }
  }
}

void motorMove(int dir) {
  switch(dir) {
    case 1: //forward
      motorLeft.run(-MOTORSPEED);
      motorRight.run(MOTORSPEED+10);
      delay(350);
      break;

    case 2: //backward
      motorLeft.run(MOTORSPEED);
      motorRight.run(-MOTORSPEED);
      delay(350);
      break;

    case 3: //right 90
      motorLeft.run(-MOTORSPEEDTURN-50);
      motorRight.run(-MOTORSPEEDTURN);
      delay(400);
      break;

    case 4: //left 90
      motorLeft.run(MOTORSPEEDTURN);
      motorRight.run(MOTORSPEEDTURN);
      delay(400);
      break;

    case 5: //R45
      motorLeft.run(-MOTORSPEEDTURN-50);
      motorRight.run(-MOTORSPEEDTURN);
      delay(200);
      break;

    case 6: //L45
      motorLeft.run(MOTORSPEEDTURN);
      motorRight.run(MOTORSPEEDTURN);
      delay(200);
      break;

     case 7: //R360
      motorLeft.run(-MOTORSPEEDTURN-50);
      motorRight.run(-MOTORSPEEDTURN);
      delay(1600);
      break;

     case 8: //L360
      motorLeft.run(MOTORSPEEDTURN);
      motorRight.run(MOTORSPEEDTURN);
      delay(1600);
      break;
      
    default:
      break;
  }
  motorStop();
}

void joystickMovement(int dir) {
  switch(dir) {
    case 1: 
      motorLeft.run(-MOTORSPEED);
      motorRight.run(MOTORSPEED+10);
      delay(100);
      break;
     case 2:
      motorLeft.run(MOTORSPEED);
      motorRight.run(-MOTORSPEED);
      delay(100);
      break;
     case 3: //right 
      motorLeft.run(-MOTORSPEEDTURN-50);
      motorRight.run(-MOTORSPEEDTURN);
      delay(100);
      break;

    case 4: //left 
      motorLeft.run(MOTORSPEEDTURN);
      motorRight.run(MOTORSPEEDTURN);
      delay(100);
      break;
     default:
        break;
  }
  motorStop();
}

void motorStop() {
  motorLeft.stop();
  motorRight.stop();
}

void dance() {
  motorMove(5);
  motorMove(6);
  motorMove(5);
  motorMove(6);
  motorMove(7);
  motorMove(4);
  motorMove(3);
  motorMove(8);
  motorMove(3);
  motorMove(4);
  for(int i = 0; i<4; i++) {
    motorMove(3);
  }
  motorMove(8);
  motorMove(4);
  motorMove(3);
  //adjust view
}

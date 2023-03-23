#include "MeMCore.h"
#include <time.h>

MeDCMotor motorLeft(M1);
MeDCMotor motorRight(M2);
MeRGBLed onboardled(0,30);
MeLineFollower lineFinderFront(PORT_1);
MeLineFollower lineFinderBack(PORT_2);

const int BUTTONPIN = 7;
const int LEDPIN = 13;

uint8_t MOTORSPEED = 200;
uint16_t MOTORSPEEDTURN = 300;

void setup() {
  Serial.begin(115200);
  onboardled.setpin(LEDPIN);
  pinMode(BUTTONPIN, INPUT);
  onboardled.setColor(0,0,0);
  onboardled.show();
  Serial.println("K");
}

void loop() {
  char piCmd = 'z';
  if (Serial.available()>0) {
    piCmd = Serial.read();

    switch(piCmd) {
      case 'A':
        if(!frontEdgeDetected()) {
          joystickMovement(1);
        }
//        Serial.println("fwd");
        Serial.println("K");
        break;

      case 'B':
        if(!backEdgeDetected()) {
          joystickMovement(2);
        }
//        Serial.println("bwd");
        Serial.println("K");
        break;

      case 'C':
        joystickMovement(3);
//        Serial.println("R90");
        Serial.println("K");
        break;

      case 'D':
        joystickMovement(4);
//        Serial.println("L90");
        Serial.println("K");
        break;

      case 'E':
//      Right when face detected
        motorMove(9);
        Serial.println("K");
        break;

      case 'F':
//      Left when face detected
        motorMove(10);
        Serial.println("K");
        break;

       case 'I':
//       Right when NO face detected
        joystickMovement(3);
        delay(1000);
        Serial.println("K");
        break;

       case 'G':
        fidget();
        Serial.println("N");
        break;

       case 'H':
        dance();
        Serial.println("N");
        break;

       case 'L':
        game();
        delay(2000);
        Serial.println("K");
        break;

       case 'U':
         freeMotivationMove(1);
         Serial.println("N");
        break;

       case 'V':
         freeMotivationMove(2);
         Serial.println("N");
        break;
        
      default:
        break;
    }
  }
}

void motorMove(int dir) {
  switch(dir) {
    case 1: //forward
      if(!frontEdgeDetected()) {
        motorLeft.run(-MOTORSPEED);
        motorRight.run(MOTORSPEED+10);
        delay(150);
      }
      break;

    case 2: //backward
      if(!backEdgeDetected()) {
        motorLeft.run(MOTORSPEED);
        motorRight.run(-MOTORSPEED);
        delay(150);
      }
      break;

    case 3: //right 90
      motorLeft.run(-MOTORSPEEDTURN-50);
      motorRight.run(-MOTORSPEEDTURN);
      delay(390);
      break;

    case 4: //left 90
      motorLeft.run(MOTORSPEEDTURN);
      motorRight.run(MOTORSPEEDTURN);
      delay(390);
      break;

    case 5: //R45
      motorLeft.run(-MOTORSPEEDTURN-50);
      motorRight.run(-MOTORSPEEDTURN);
      delay(250);
      break;

    case 6: //L45
      motorLeft.run(MOTORSPEEDTURN);
      motorRight.run(MOTORSPEEDTURN);
      delay(250);
      break;

     case 7: //R360
      motorLeft.run(-MOTORSPEEDTURN-50);
      motorRight.run(-MOTORSPEEDTURN);
      delay(1400);
      break;

     case 8: //L360
      motorLeft.run(MOTORSPEEDTURN);
      motorRight.run(MOTORSPEEDTURN);
      delay(1150);
      break;

     case 9:  //tiny R for face tracking
      motorLeft.run(-MOTORSPEEDTURN-50);
      motorRight.run(-MOTORSPEEDTURN);
      delay(50);
      break;

     case 10: //tiny L for face tracking
      motorLeft.run(MOTORSPEEDTURN);
      motorRight.run(MOTORSPEEDTURN);
      delay(50);
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
      delay(90);
      break;
     case 2:
      motorLeft.run(MOTORSPEED);
      motorRight.run(-MOTORSPEED);
      delay(90);
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

void fidget() {
  delay(200);
  motorMove(6);
  delay(1000);
  motorMove(3);
  delay(1000);
  motorMove(6);
}

void dance() {
  motorMove(7);
  delay(400);
  motorMove(1);
  delay(400);
  motorMove(5);
  delay(300);
  motorMove(6);
  delay(400);
  motorMove(2);
  delay(400);
  motorMove(6);
  delay(300);
  motorMove(5);
}

bool frontEdgeDetected() {
  int frontSensor = lineFinderFront.readSensors();
  return(frontSensor != 3);
}

bool backEdgeDetected() {
  int backSensor = lineFinderBack.readSensors();
  return(backSensor != 3);
}

void game() {
  long int t;
  bool x = true;

  Serial.println("s");
  //Game start
  onboardled.setColor(255,0,0); //red
  onboardled.show();
  //wait a random time from 1-7sec
  int num = rand() % 7000 + 1000;  
  delay(num);
  
  onboardled.setColor(0,255,255); //blue
  onboardled.show();
  
  //Timer start
  t = millis();

  while (x == true) {
    if (analogRead(7) < 100) {
      Serial.println("p");
      t = millis() - t;
      onboardled.setColor(0,0,0);
      onboardled.show();
      x = false;
      delay(2000);
      Serial.println(t); //send result to android
    } else {
      //Button not pressed for 7s
      if ((millis() - t) > 7000) {
        onboardled.setColor(0,0,0);
        onboardled.show(); 
        x = false;
        Serial.println("f");
      }
    }
  }
}

void freeMotivationMove(int goodOrBad) {
  switch(goodOrBad) {
    case 1: //good
      motorMove(2);
      delay(1000);
      motorMove(5);
      delay(1500);
      motorMove(6);
      delay(1000);
      motorMove(1);
      delay(1500);
      motorMove(1);
      break;
      
     case 2:  //bad
      delay(200);
      motorMove(1);
      delay(500);
      motorMove(1);
      delay(500);
      motorMove(1);
      delay(1500);
      motorMove(5);
      delay(1000);
      motorMove(6);
      delay(400);
      motorMove(5);
      delay(400);
      motorMove(6);
      delay(400);
      motorMove(5);
      delay(500);
      motorMove(2);
      delay(1000);
      motorMove(6);
      break;

     default: break;
  }
}

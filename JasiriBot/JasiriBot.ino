#include "MeMCore.h"

MeDCMotor motorLeft(M1);
MeDCMotor motorRight(M2);

uint8_t MOTORSPEED = 100;

void setup() {
  Serial.begin(115200);

}

void loop() {
  char piCmd;
  while (Serial.available()) {
    piCmd = Serial.read();

    switch(piCmd) {
      case 'a':
        motorForward();
        delay(1000);
        motorStop();
        Serial.println("Moving");
        break;
        
      case 'b':
        Serial.println("Jas a pi");
        break;

      default:
        break;
    }
  }

}

void motorForward() {
  motorLeft.run(-MOTORSPEED);
  motorRight.run(MOTORSPEED);
}

void motorStop() {
  motorLeft.stop();
  motorRight.stop();
}

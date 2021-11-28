#include "main.h"


using namespace pros;

const double ticksPerDeg = 900/360;
//200*4.125*pi/60 * sqrt(2), = 60
const double robotSpeed = 43.196 * sqrt(2);
const double rotationSpeed = 200;

extern Controller control;
extern Motor FrontLeft;
extern Motor FrontRight;
extern Motor BackLeft;
extern Motor BackRight;
extern Motor LeftIntake;
extern Motor RightIntake;

//Ports
const int FLPort = 3;
const int FRPort = 6;
const int BLPort = 4;
const int BRPort = 5;

const int BCPort = 7;
const int FCPort = 8;

const int LIPort = 10;
const int RIPort = 11;
const int LRPort = 2;
const int RRPort = 3;
const int IMUPort = 1;

Controller control (E_CONTROLLER_MASTER);
Motor FrontLeft(FLPort, true);
Motor FrontRight(FRPort, false);
Motor BackLeft(BLPort, true);
Motor BackRight(BRPort, false);
Motor LeftIntake(LIPort, false);
Motor RightIntake(RIPort, true);
Motor BackRoller(LRPort, true);
Motor MainRoller(RRPort, true);
Motor BackClamp(BCPort,true);
Motor FrontClamp(FCPort,true);
Motor Conveyor(LIPort,true);
Imu inertial(IMUPort);

ADIEncoder yWheel('C', 'D', true);
ADIEncoder xWheel('A', 'B', false);


//Calibrate the sensors
void calibrateSensors(){
  xWheel.reset();
  yWheel.reset();
  inertial.reset();

  int timeInit = millis();

  inertial.reset();
  while(inertial.is_calibrating()){
    lcd::print(1, "Calibrating");
    delay(10);
  }
  delay(2000);
  lcd::print(1, "Calibration took %f", millis() - timeInit);
}

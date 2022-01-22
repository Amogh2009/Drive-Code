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
const int FRPort = 5;
const int BLPort = 14;
const int BRPort = 16;
const int MLPort = 10;
const int MRPort = 7;

const int BCPort = 7;
const int FCPort = 12;
const int L1Port = 15;
const int L2Port = 10;

const int LIPort = 11;
const int RIPort = 12;
const int LRPort = 2;
const int RRPort = 3;
const int IMUPort = 1;

Controller control (E_CONTROLLER_MASTER);
Motor FrontLeft(FLPort, true);
Motor FrontRight(FRPort, false);
Motor BackLeft(BLPort, true);
Motor BackRight(BRPort, false);
Motor MidLeft(MLPort, true);
Motor MidRight(MRPort, false);
/*
Motor FrontLeft(FLPort, false);
Motor FrontRight(FRPort, true);
Motor BackLeft(BLPort, false);
Motor BackRight(BRPort, true);
Motor MidLeft(MLPort, false);
Motor MidRight (MRPort, true);
*/
Motor LeftIntake(LIPort, false);
Motor RightIntake(RIPort, true);
Motor BackRoller(LRPort, true);
Motor MainRoller(RRPort, true);
Motor BackClamp(BCPort,true);
Motor FrontClamp(FCPort,false);
Motor Conveyor(LIPort,true);
Motor Lift1(L1Port, true);
Motor Lift2(L2Port, false);
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

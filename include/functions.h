#include "main.h"
//#include "motorSetup.h"

//okapi::Controller master;


//Useful Constants
const double wheelCircumfrence = 4 * M_PI;

const double FLWeight = 1;
const double FRWeight = 1;
const double BLWeight = 1;
const double BRWeight = 1;
const double MLWeight = 1;
const double MRWeight = 1;

//For debugging things
void printOnScreen(){
	//lcd::print(1, "Velocity FL: %f", FrontLeft.get_actual_velocity());
	//lcd::print(2, "Target Velocity FL: %f", drive.wheelTL);
  lcd::print(0, "Inertial Reading: %f", inertial.get_rotation());
  lcd::print(1, "Y Wheel Reading: %f", ((double) yWheel.get_value()));
  lcd::print(2, "X Wheel Reading: %f", ((double) xWheel.get_value()));
}

int selected = 0;
std::string autons[2] = {"Disabled", "Enabled"};
int size = 2;//*(&autons + 1) - autons;


void autonSelector(){
  control.clear();
  pros::delay(200);
  while(true){
    control.clear();
    pros::delay(100);
    control.print(2, 1, autons[selected].c_str());
    pros::delay(100);
     if(control.get_digital(DIGITAL_RIGHT)){
       selected = (selected + 1 + size) % size;
     }else if(control.get_digital(DIGITAL_LEFT)){
       selected = (selected - 1 + size) % size;
     }else if(control.get_digital(DIGITAL_Y)){
       pros::delay(200);
       if(control.get_digital(DIGITAL_Y)){
         control.print(2, 1, "Selected %d", selected);
         goto slctEnd;
       }
     }
   }
   slctEnd:
   control.rumble("..");
}

void motorTest() {
  while (true) {
  Controller master (CONTROLLER_MASTER);

  if (master.get_digital(DIGITAL_L1)) {
    FrontLeft.move(100);
  }
  if (master.get_digital(DIGITAL_L2)) {
    BackLeft.move(100);
  }
  if (master.get_digital(DIGITAL_R1)) {
    FrontRight.move(100);
  }
  if (master.get_digital(DIGITAL_R2)) {
    BackRight.move(100);
    }
  }
}

void driverControl(double l, double r){
  //Calculates speed of wheels for driver control

	FrontLeft.move_velocity(l * FLWeight);
	FrontRight.move_velocity(r * FRWeight);
	BackLeft.move_velocity(l * BLWeight);
	BackRight.move_velocity(r * BRWeight);
  MidLeft.move_velocity(l * MLWeight);
  MidRight.move_velocity(r * MRWeight);
}


void stopDrive(bool hold = false){
  //Shortcut to stop the drive quickly
  if(hold){
    FrontLeft.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    FrontRight.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    BackLeft.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    BackRight.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  }
  FrontLeft.move_velocity(0);
	FrontRight.move_velocity(0);
	BackLeft.move_velocity(0);
	BackRight.move_velocity(0);
  delay(100);
  FrontLeft.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  FrontRight.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  BackLeft.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
  BackRight.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}

#include "main.h"
#include  "autonomous.h"

void leftBtn(){

}
void centerBtn(){

}
void rightBtn(){

}
void initialize() {
	pros::lcd::initialize();

	pros::lcd::register_btn0_cb(leftBtn);
	pros::lcd::register_btn1_cb(centerBtn);
	pros::lcd::register_btn2_cb(rightBtn);

	autonomous();
	//autonSelector();
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
	skills();
	FrontLeft.move_relative((1) * FLWeight, 100);
	FrontRight.move_relative((1) * FRWeight, 100);
	BackLeft.move_relative((1) * BLWeight, 100);
	BackRight.move_relative((1) * BRWeight, 100);
	pros::delay(2000);
}
using namespace pros;
void opcontrol() {
  Controller master (CONTROLLER_MASTER);

  while (true) {
		//drivetrain
		double power = master.get_analog(ANALOG_LEFT_Y);
		double turn = master.get_analog(ANALOG_RIGHT_X);
		driverControl(100*(power-turn), 100*(power+turn));
		//back clamp
		if (master.get_digital(DIGITAL_R2)){
			BackClamp.move(100);
		}
		else if (master.get_digital(DIGITAL_R1)){
			BackClamp.move(-100);
		}else{
			BackClamp.move(0);
		}
		//front clamp
		if (master.get_digital(DIGITAL_L2)){
			BackClamp.move(100);
		}
		else if (master.get_digital(DIGITAL_L1)){
			BackClamp.move(-100);
		}else{
			BackClamp.move(0);
		}
		//ring intake? commenting out for now
		/*
		if (master.get_digital(DIGITAL_L1)){
			Conveyor.move(100);
		}else{
			Conveyor.move(0);
		}
		*/

		pros::delay(2);
  }
}

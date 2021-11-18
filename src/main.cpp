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


	//autonSelector();
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
	
}
using namespace pros;
void opcontrol() {
  Controller master (CONTROLLER_MASTER);

  while (true) {
		double power = master.get_analog(ANALOG_LEFT_Y);
		double turn = master.get_analog(ANALOG_RIGHT_X);
		driverControl(100*(power-turn), 100*(power+turn));
    pros::delay(2);
		if (master.get_digital(DIGITAL_R2)){
			Clamp.move(100);
		}
		else if (master.get_digital(DIGITAL_R1)){
			Clamp.move(-100);
		}else{
			Clamp.move(0);
		}

		}
  }

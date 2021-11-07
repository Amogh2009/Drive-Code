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
	skills();
}
using namespace pros;
void opcontrol() {
  Controller master (CONTROLLER_MASTER);

  while (true) {
		double power = master.get_analog(ANALOG_LEFT_Y);
		double turn = master.get_analog(ANALOG_LEFT_X);
		driverControl(100*(power-turn), 100*(power+turn));
    pros::delay(2);

  }
}

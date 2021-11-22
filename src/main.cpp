
#include "main.h"
#include  "autonomous.h"
#include "motorSetup.h"
#include "functions.h"
#include <math.h>

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

	autonSelector();
}

void disabled() {}

void competition_initialize() {}

const int MOVE_SPEED = 60;  // 60 RPM
const float WHEEL_RADIUS = 2.0;  // 2 inches
float calculateRotations(float distance) {
	return 6 * distance / (WHEEL_RADIUS * M_PI);
}

// Move the robot forward distance in feet
void moveForward(float distance) {
	float rotations = calculateRotations(distance);
	FrontLeft.move_relative(rotations, 60);
	FrontRight.move_relative(rotations, 60);
	BackLeft.move_relative(rotations, 60);
	BackRight.move_relative(rotations, 60);
}

// Move the robot backward distance in feet
void moveBackward(float distance) {
	float rotations = calculateRotations(distance);
	FrontLeft.move_relative(-rotations, 60);
	FrontRight.move_relative(-rotations, 60);
	BackLeft.move_relative(-rotations, 60);
	BackRight.move_relative(-rotations, 60);
}


void autonomous() {
	if(selected) {
		FrontLeft.move_relative((1) * FLWeight, 100);
		FrontRight.move_relative((1) * FRWeight, 100);
		BackLeft.move_relative((1) * BLWeight, 100);
		BackRight.move_relative((1) * BRWeight, 100);
		pros::delay(2000);
		moveForward(6.0);
		// do we need to add delay
		// pros::delay(10000);
		// clamp down
		BackClamp.move(100);
		moveBackward(5.5);
	}
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
		} else {
			BackClamp.move(0);
		}
		//front clamp
		if (master.get_digital(DIGITAL_L2)){
			FrontClamp.move(100);
		}
		else if (master.get_digital(DIGITAL_L1)){
			FrontClamp.move(-100);
		} else {
			FrontClamp.move(0);
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

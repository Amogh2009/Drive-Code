
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

const int MOVE_SPEED = 120;  // 120 RPM
const float WHEEL_RADIUS = 2.0;  // 2 inches
float calculateRotations(float distance) {
	//converts distance from feet to inches
	return 12 * distance / (2 * WHEEL_RADIUS * M_PI);
}

// Move the robot forward distance in feet
void moveForward(float distance) {
	float rotations = calculateRotations(distance);
	float degrees = 360 * rotations;
	FrontLeft.move_relative(degrees, MOVE_SPEED);
	FrontRight.move_relative(degrees, MOVE_SPEED);
	BackLeft.move_relative(degrees, MOVE_SPEED);
	BackRight.move_relative(degrees, MOVE_SPEED);
}

// Move the robot backward distance in feet
void moveBackward(float distance) {
	float rotations = calculateRotations(distance);
	float degrees = 360 * rotations;
	FrontLeft.move_relative(-degrees, MOVE_SPEED);
	FrontRight.move_relative(-degrees, MOVE_SPEED);
	BackLeft.move_relative(-degrees, MOVE_SPEED);
	BackRight.move_relative(-degrees, MOVE_SPEED);
}


void autonomous() {
	if(selected) {
		/*
		FrontLeft.move_relative((1) * FLWeight, 100);
		FrontRight.move_relative((1) * FRWeight, 100);
		BackLeft.move_relative((1) * BLWeight, 100);
		BackRight.move_relative((1) * BRWeight, 100);
		pros::delay(2000);
		*/
		moveBackward(9.5);
		//delay of 1.5 seconds
		pros::delay(1500);
		// clamp down
		BackClamp.move(100);
		//delay of 1 second
		pros::delay(1000);
		moveForward(9.0);
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
		if (master.get_digital(DIGITAL_DOWN)){
			Lift1.move(100);
			Lift2.move(100);
		}
		else if (master.get_digital(DIGITAL_UP)){
			Lift1.move(-100);
			Lift2.move(-100);
		} else {
			Lift1.move(0);
			Lift2.move(0);
		}
		//ring intake
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

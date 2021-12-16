
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

//is this even accurate?
void turnLeft45Degrees(){
    FrontLeft.move(100);
    FrontRight.move(200);
    BackLeft.move(100);
    BackRight.move(200);
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
void move(float distance) {
	float rotations = calculateRotations(distance);
	float degrees = 360 * rotations;
	FrontLeft.move_relative(degrees, MOVE_SPEED);
	FrontRight.move_relative(degrees, MOVE_SPEED);
	BackLeft.move_relative(degrees, MOVE_SPEED);
	BackRight.move_relative(degrees, MOVE_SPEED);
}

//still rough, needs adjustment. Not sure if the theory behind it is entirely correct either.
void turn(float deg, float dist) {
	//the dist from one opposite wheel to another in feet. Needs measurement.
	const float inscribedDiameter = 1;

	float circumference = M_PI * inscribedDiameter; //circumference of the circle that describe's the wheels' path
	float arc_length = circumference * deg / 360; //calculates the length of the arc that represents the angle
	float rotations = calculateRotations(arc_length); //calculate how many rotations to travel that distance
	float degrees = 360 * rotations; //calculates the degrees needed to travel that length
	float acc = calculateRotations(dist) * 360; //calculates the degrees needed to go [dist] far
	FrontLeft.move_relative(acc + degrees, MOVE_SPEED);
	FrontRight.move_relative(acc - degrees, MOVE_SPEED);
	BackLeft.move_relative(acc + degrees, MOVE_SPEED);
	BackRight.move_relative(acc - degrees, MOVE_SPEED);
}

//like the turn function, this is untested, and has a 0% chance of working without adjustment.
void autonmid(bool isLeft) {
	move(7);
	pros::delay(1100);
	turn(70 * (isLeft ? 1 : -1), 80);
	pros::delay(700);
	BackClamp.move(100);
	pros::delay(100);
	turn(-70 * (isLeft ? 1 : -1), 80);
	pros::delay(700);
	move(-5);
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
		move(12.5);
		//delay of 1.5 seconds
		pros::delay(1500);
		// clamp down
		BackClamp.move(100);
		//delay of 1 second
		pros::delay(1000);
		move(-12.0);
	}
}

using namespace pros;
void opcontrol() {
  Controller master (CONTROLLER_MASTER);

  while (true) {
		//drivetrain
    /*
    int power = master.get_analog(ANALOG_LEFT_Y);
    int turn = master.get_analog(ANALOG_RIGHT_X);
    */
    double power = master.get_analog(ANALOG_LEFT_Y);
		double turn = master.get_analog(ANALOG_LEFT_X);
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
			Lift1.move(200);
			Lift2.move(200);
		}
		else if (master.get_digital(DIGITAL_UP)){
			Lift1.move(-200);
			Lift2.move(-200);
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

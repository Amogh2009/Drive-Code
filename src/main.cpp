
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
void turnLeft90Degrees(){
    FrontLeft.move(-200);
    FrontRight.move(200);
    BackLeft.move(-200);
    BackRight.move(200);
    pros::delay(3000);
}

void initialize() {
	pros::lcd::initialize();

	pros::lcd::register_btn0_cb(leftBtn);
	pros::lcd::register_btn1_cb(centerBtn);
	pros::lcd::register_btn2_cb(rightBtn);

  autonSelector();
	//autonSelector();
}

void disabled() {}

void competition_initialize() {}

const int MOVE_SPEED = 200;  // 200 RPM
const float WHEEL_RADIUS = 2.0;  // 2 inches

float calculateRotations(float distance) {
	//converts distance from feet to inches
	return 12 * distance / (2 * WHEEL_RADIUS * M_PI);
}

// Move the robot forward distance in feet
void move(float distance) {
  float multiplier = 0.75;
	float rotations = calculateRotations(distance);
	float degrees = 360 * rotations;
	FrontLeft.move_relative(degrees, multiplier*MOVE_SPEED);
	FrontRight.move_relative(degrees, multiplier*MOVE_SPEED);
  MidLeft.move_relative(degrees, multiplier*MOVE_SPEED);
  MidRight.move_relative(degrees, multiplier*MOVE_SPEED);
	BackLeft.move_relative(degrees, multiplier*MOVE_SPEED);
	BackRight.move_relative(degrees, multiplier*MOVE_SPEED);
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
/*void autonmid(bool isLeft) {
	move(7);
	pros::delay(1100);
	turn(70 * (isLeft ? 1 : -1), 80);
	pros::delay(700);
	BackClamp.move(100);
	pros::delay(100);
	turn(-70 * (isLeft ? 1 : -1), 80);
	pros::delay(700);
	move(-5);
}*/

void autonomous() {
	if(selected == 1) {
		/*
		FrontLeft.move_relative((1) * FLWeight, 100);
		FrontRight.move_relative((1) * FRWeight, 100);
		BackLeft.move_relative((1) * BLWeight, 100);
		BackRight.move_relative((1) * BRWeight, 100);
		pros::delay(2000);
		*/
    Lift1.move(-200);
    pros::delay(10);
    move(6.8);
    Lift1.move(0);
		//delay of 1.5 seconds
		pros::delay(1500);
		// clamp down
		FrontClamp.move(50);
		//delay of 1 second
		pros::delay(1000);
		move(-6.3);
	}else if(selected == 2){
    FrontClamp.move(50);
    pros::delay(1000);
    Lift1.move(-200);
    pros::delay(100);
    Lift1.move(0);
    move(-4);
    turnLeft90Degrees();
    move(14.5);
  }
}

void print_temperature(void* param) {
	double temp = (FrontRight.get_temperature()
	+ BackLeft.get_temperature()
	+ BackRight.get_temperature()
	+ MidLeft.get_temperature()
	+ MidRight.get_temperature()
	+ FrontClamp.get_temperature()
	+ Lift1.get_temperature()) / 7.0;
	// (FrontLeft.get_temperature());

	control.print(1, 1, "%.2f", temp);
}

double lastpress;
double multiplier = 200;

using namespace pros;
void opcontrol() {
  Controller master (CONTROLLER_MASTER);
	//Task my_task(my_task_fn);
  while (true) {
		//drivetrain
		print_temperature(nullptr);
    double power = master.get_analog(ANALOG_LEFT_Y);
		double turn = master.get_analog(ANALOG_RIGHT_X);
    driverControl(multiplier*(power+turn), multiplier*(power-turn));

    if(control.get_digital(E_CONTROLLER_DIGITAL_X) && millis()-lastpress>=1000){
        if (multiplier == 200){
          multiplier = 0.5;
          FrontLeft.set_brake_mode(MOTOR_BRAKE_HOLD);
          FrontRight.set_brake_mode(MOTOR_BRAKE_HOLD);
          BackRight.set_brake_mode(MOTOR_BRAKE_HOLD);
          BackLeft.set_brake_mode(MOTOR_BRAKE_HOLD);
          MidRight.set_brake_mode(MOTOR_BRAKE_HOLD);
          MidLeft.set_brake_mode(MOTOR_BRAKE_HOLD);
          //std::string climbstring = "Climb";
          control.print(3, 1, "Climb");
          lastpress = millis();
        }else{
          multiplier = 200;
          FrontLeft.set_brake_mode(MOTOR_BRAKE_COAST);
          FrontRight.set_brake_mode(MOTOR_BRAKE_COAST);
          BackLeft.set_brake_mode(MOTOR_BRAKE_COAST);
          BackRight.set_brake_mode(MOTOR_BRAKE_COAST);
          MidLeft.set_brake_mode(MOTOR_BRAKE_COAST);
          MidRight.set_brake_mode(MOTOR_BRAKE_COAST);
          //std::string climbstring = "No Climb";
          control.print(3, 1, "No Climb");
          lastpress = millis();
        }
    }
    /*
    //back clamp
		if (master.get_digital(DIGITAL_R2)){
			BackClamp.move(100);
		}
		else if (master.get_digital(DIGITAL_R1)){
			BackClamp.move(-100);
		} else {
			BackClamp.move(0);
		}
    */
		//front clamp
		if (master.get_digital(DIGITAL_R2)){
			FrontClamp.move(100);
		}
		else if (master.get_digital(DIGITAL_R1)){
			FrontClamp.move(-100);
		} else {
			FrontClamp.move(0);
		}
		if (master.get_digital(DIGITAL_L2)){
			Lift1.move(200);
		}
		else if (master.get_digital(DIGITAL_L1)){
			Lift1.move(-200);
		} else {
			Lift1.move(0);
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

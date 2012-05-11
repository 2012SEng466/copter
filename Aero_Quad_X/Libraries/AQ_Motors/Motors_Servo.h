/*
  Motors_Servo.h
  AeroQuad motor control using the Arduino Servo library.

  Author: Garrett Owen
 */


#ifndef _AEROQUAD_MOTORS_SERVO_H_
#define _AEROQUAD_MOTORS_SERVO_H_

#include "Arduino.h"
#include "Motors.h"
#include <Servo.h>

Servo motor1;
Servo motor2;
Servo motor3;
Servo motor4;

void initializeMotors(NB_Motors numbers) {
	numberOfMotors = numbers;

	motor1.attach(3);
	motor2.attach(5);
	motor3.attach(6);
	motor4.attach(10);

	commandAllMotors(1000);  // Initialise motors to 1000us (stopped)
}

void writeMotors() {
	motor1.writeMicroseconds(motorCommand[MOTOR1]);
	motor2.writeMicroseconds(motorCommand[MOTOR2]);
	motor3.writeMicroseconds(motorCommand[MOTOR3]);
	motor4.writeMicroseconds(motorCommand[MOTOR4]);
}

void commandAllMotors(int command) {
	motor1.writeMicroseconds(command);
	motor2.writeMicroseconds(command);
	motor3.writeMicroseconds(command);
	motor4.writeMicroseconds(command);
}


#endif

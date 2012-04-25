/*
  AeroQuad v3.0.1 - February 2012
  www.AeroQuad.com
  Copyright (c) 2012 Ted Carancho.  All rights reserved.
  An Open Source Arduino based multicopter.

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program. If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef _AEROQUAD_MOTORS_SERVO_H_
#define _AEROQUAD_MOTORS_SERVO_H_

#include "Arduino.h"
#include "Motors.h"
#include <Servo.h>

#define PWM_FREQUENCY 300   // in Hz
#define PWM_PRESCALER 8
#define PWM_COUNTER_PERIOD (F_CPU/PWM_PRESCALER/PWM_FREQUENCY)

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

	commandAllMotors(1000);                                     // Initialise motors to 1000us (stopped)
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

#ifndef copter_control_H_
#define copter_control_H_

#include "Arduino.h"
#include "radio.h"
#include "Servo.h"

/* Motor Vars */
#define MOTOR_MAX_SPEED	2000
#define MOTOR_MIN_SPEED	700
/* Motor Pins */
#define MOTOR0			3
#define MOTOR1			5
#define MOTOR2			6
#define MOTOR3			10

#ifdef __cplusplus
extern "C" {
#endif
void loop();
void setup();
#ifdef __cplusplus
} // extern "C"
#endif

//Do not add code below this line
#endif /* copter_control_H_ */

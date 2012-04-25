// Do not remove the include below
#include "copter_control.h"

int mSpeeds[4];
volatile int radio_flag = 0;

Servo motor0;
Servo motor1;
Servo motor2;
Servo motor3;

void radio_irq() {
	radio_flag = 1;
}

void motor_stop_all() {
	motor0.writeMicroseconds(MOTOR_MIN_SPEED);
	motor1.writeMicroseconds(MOTOR_MIN_SPEED);
	motor2.writeMicroseconds(MOTOR_MIN_SPEED);
	motor3.writeMicroseconds(MOTOR_MIN_SPEED);

	for (int i=0; i<4; i++)
		mSpeeds[i] = MOTOR_MIN_SPEED;
}

void motor_arm() {
	motor0.attach(MOTOR0);
	motor1.attach(MOTOR1);
	motor2.attach(MOTOR2);
	motor3.attach(MOTOR3);

	motor_stop_all();

	delay(200);
}

void motor_write_speeds() {
	motor0.writeMicroseconds(mSpeeds[0]);
	motor1.writeMicroseconds(mSpeeds[1]);
	motor2.writeMicroseconds(mSpeeds[2]);
	motor3.writeMicroseconds(mSpeeds[3]);
}

void motor_set_all(int setSpeed) {
	for (int i=0; i<4; i++)
		mSpeeds[i] = setSpeed;

	motor_write_speeds();
}

/**
 * Requests the remote station to acknowledge that it is still there.
 */
void request_ack() {
	radio_packet packet;

	packet.vars.ack = 0;
	radio_send_nowait(&packet, BASE_ADDR);
}

void setup() {
	// DEBUG
	Serial.begin(9600);

	motor_arm();

	radio_init(COPTER_ADDR, RADIO_CHANNEL, RADIO_PAYLOAD);
	attachInterrupt(0,radio_irq,LOW);

	// DEBUG
	Serial.println("Listening...");
}

void loop() {
	radio_packet packet;

//	unsigned long currTime = millis();
//	static unsigned long ackRecvd = currTime;
//	static unsigned long ackReq = currTime;
//
//	// Request Ack every second
//	if (currTime - ackReq > 1000)
//		request_ack();
//
//	// If no ack received within 2 seconds stop motors
//	if (currTime - ackRecvd > 2000) {
//		motor_stop_all();
//		Serial.println("no ack recvd");
//	}

	// Check if data received
	if (!radio_check_recv(&packet)) {
		delay(100);
		return;
	}

//	// Check if Ack received
//	if (packet.vars.ack == 1) {
//		ackRecvd = millis();
//		return;
//	}

	switch (packet.vars.motor) {
	case 'a':
		motor_set_all(packet.vars.speed);
		break;

	case 'c': // clockwise
		mSpeeds[0] = packet.vars.speed;
		mSpeeds[2] = packet.vars.speed;
		motor_write_speeds();
		break;
	case 'v': // counter clockwise
		mSpeeds[1] = packet.vars.speed;
		mSpeeds[3] = packet.vars.speed;
		motor_write_speeds();
		break;

	case '0':
		mSpeeds[0] = packet.vars.speed;
		motor_write_speeds();
		break;
	case '1':
		mSpeeds[1] = packet.vars.speed;
		motor_write_speeds();
		break;
	case '2':
		mSpeeds[2] = packet.vars.speed;
		motor_write_speeds();
		break;
	case '3':
		mSpeeds[3] = packet.vars.speed;
		motor_write_speeds();
		break;
	}

	// DEBUG print packet details
	Serial.print("speed: ");
	Serial.print(packet.vars.speed);
	Serial.print(" motor: ");
	Serial.println(packet.vars.motor);

	delay(100);

//	// DEBUG - interrupt should have been set
//	// Note, interrupts should be disabled when flag is checked.
//	if (radio_flag == 1)
//		radio_flag = 0;
//	else
//		Serial.println("Warning: Radio Flag was not set.");
//
//	// DEBUG print packet details
//	Serial.print("speed: ");
//	Serial.print(packet.vars.speed);
//	Serial.print(" motor: ");
//	Serial.print(packet.vars.motor);
//	Serial.print(" ack: ");
//	Serial.println(packet.vars.ack);
//
//	packet.vars.ack = 1;
//
//	radio_send_nowait(&packet, BASE_ADDR);
//	// I think it can only send every 10ms... read the spec
//	delay(100); // Quick fix - wait for radio. Later check time since last sent with millis() in send?
}

/*
  Author: Garrett Owen
 */

#ifndef _AEROQUAD_RECEIVER_REMOTE_PC_H_
#define _AEROQUAD_RECEIVER_REMOTE_PC_H_

#include "Arduino.h"
#include "Receiver.h"
#include "Radio.h"
#include "../../AeroQuad/DataStorage.h"

// Array positions for rcValue[] and and recieverCommand[]
// XAXIS 	0	Roll
// YAXIS 	1	Pitch
// ZAXIS 	2	Yaw
// THROTTLE 3	Throttle
// MODE 	4	Rate/Attitude mode selection
// AUX 		5

volatile uint16_t rcValue[6] = {1500,1500,1500,1000,1500,1500}; // interval [1000;2000]
unsigned long lastRecv;


void radioCheck() {
	radio_packet packet;
	int i;

	while (radio_check_recv(&packet)) {
		// Check for PID tuning or radio control
		if (packet.vars.flag == WRITE_PID
				&& packet.vars.pidIndex > -1
				&& packet.vars.pidIndex < 10
				&& motorArmed == OFF) {

			// Set PID Values
			struct PIDdata* pid = &PID[packet.vars.pidIndex];
			pid->P = packet.vars.p;
			pid->I = packet.vars.i;
			pid->D = packet.vars.d;
			pid->lastPosition = 0;
			pid->integratedError = 0;
			zeroIntegralError();

		} else if (packet.vars.flag == READ_PID) {

			// Read and send PID Data
			struct PIDdata* pid = &PID[packet.vars.pidIndex];
			packet.vars.p = pid->P;
			packet.vars.i = pid->I;
			packet.vars.d = pid->D;
			radio_send_nowait(&packet, BASE_ADDR);

		} else if (packet.vars.flag == COMMIT_PID
				&& motorArmed == OFF) {

			writeEEPROM(); // defined in DataStorage.h
			zeroIntegralError();

		} else if (packet.vars.flag == CONTROL_DATA) {
			// Read controller values
			for (i = 0; i < 6; i++) {
				if (packet.vars.receiverCommand[i] < 1000 || packet.vars.receiverCommand[i] > 2000)
					continue;
				rcValue[i] = packet.vars.receiverCommand[i];
			}
		}

		lastRecv = currentTime;
	}

//	Serial.print(currentTime);
//	Serial.print(" - ");
//	Serial.print(lastRecv);
//	Serial.print(" = ");
//	Serial.println(currentTime - lastRecv);

	// If no commands have been received in 2 seconds, slowly land the copter
	if (currentTime - lastRecv > 2000000) {
//		Serial.println("Landing!");
		rcValue[XAXIS] = 1500;
		rcValue[YAXIS] = 1500;
		rcValue[ZAXIS] = 1500;

		if (rcValue[THROTTLE] > 1550)
			rcValue[THROTTLE] -= 40;

		// Turn off after 7 seconds
		if (currentTime- lastRecv > 7000000)
			rcValue[THROTTLE] = 1000;
	}
}

void initializeReceiver(int nbChannel) {
	initializeReceiverParam(nbChannel);
	radio_init(COPTER_ADDR, RADIO_CHANNEL, RADIO_PAYLOAD);
}

int getRawChannelValue(byte channel) {
	return rcValue[channel];
}

void setChannelValue(byte channel,int value) {
	receiverCommand[channel] = value;
}


#endif


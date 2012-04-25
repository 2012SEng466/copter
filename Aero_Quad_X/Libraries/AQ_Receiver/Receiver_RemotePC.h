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

#ifndef _AEROQUAD_RECEIVER_REMOTE_PC_H_
#define _AEROQUAD_RECEIVER_REMOTE_PC_H_

#include "Arduino.h"
#include "Receiver.h"
#include "Radio.h"
#include "../../AeroQuad/DataStorage.h"
//
//#define XAXIS 0
//#define YAXIS 1
//#define ZAXIS 2
//#define THROTTLE 3
//#define MODE 4
//#define AUX 5

volatile uint16_t rcValue[6] = {1500,1500,1500,1000,1500,1500}; // interval [1000;2000]

void readRadioPID(unsigned char PIDid) {
  struct PIDdata* pid = &PID[PIDid];
  pid->P = readFloatSerial();
  pid->I = readFloatSerial();
  pid->D = readFloatSerial();
  pid->lastPosition = 0;
  pid->integratedError = 0;
}

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


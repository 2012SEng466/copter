// Do not remove the include below
#include "Aero_Remote.h"

#define XAXIS 0
#define YAXIS 1
#define ZAXIS 2
#define THROTTLE 3
#define MODE 4
#define AUX 5

#define RATE_XAXIS_PID_IDX          0
#define RATE_YAXIS_PID_IDX          1
#define ZAXIS_PID_IDX               2
#define ATTITUDE_XAXIS_PID_IDX      3
#define ATTITUDE_YAXIS_PID_IDX      4
#define HEADING_HOLD_PID_IDX        5
#define ATTITUDE_GYRO_XAXIS_PID_IDX 6
#define ATTITUDE_GYRO_YAXIS_PID_IDX 7
#define ALTITUDE_HOLD_PID_IDX       8
#define ZDAMPENING_PID_IDX          9

int debug = 0;

// Used to read floating point values from the serial port
float readFloatSerial() {
  #define SERIALFLOATSIZE 15
  byte index = 0;
  byte timeout = 0;
  char data[SERIALFLOATSIZE] = "";

  do {
    if (Serial.available() == 0) {
      delay(10);
      timeout++;
    }
    else {
      data[index] = Serial.read();
      timeout = 0;
      index++;
    }
  } while ((index == 0 || data[index-1] != ';') && (timeout < 10) && (index < sizeof(data)-1));
  data[index] = '\0';

  return atof(data);
}

/**
 * Waits for timeout*10 milliseconds for Serial data to be available.
 * Return 0 if serial data not available or 1 if it is.
 */
int waitSerialAvailable(int timeout) {
	while ( !Serial.available() ) {
		timeout++;
		if (timeout > timeout) {
			return 0;
		}
		delay(10);
	}
	return 1;
}

// Reads an integer given in bytes
unsigned int readIntSerialBytes() {
	union u_tag {
	    byte b[2];
	    unsigned int iVal;
	} value;

	// Wait for input
	if ( !waitSerialAvailable(10) )
		return -1;

	value.b[0] = Serial.read();

	if ( !waitSerialAvailable(10) )
		return -1;

	value.b[1] = Serial.read();

	return value.iVal;
}

void sendControllerData() {
	radio_packet packet;
	int i, command;

	// Get all values
	for(i = 0; i < 6; i++) {
		if ( !waitSerialAvailable(10) )
			return;

		command = Serial.read() - '0';

		// Check if it is out of phase
		if (command < 0 || command > 5)
			return;

		switch (command) {
		case XAXIS:
			packet.vars.receiverCommand[0] = readIntSerialBytes();
			break;
		case YAXIS:
			packet.vars.receiverCommand[1] = readIntSerialBytes();
			break;
		case ZAXIS:
			packet.vars.receiverCommand[2] = readIntSerialBytes();
			break;
		case THROTTLE:
			packet.vars.receiverCommand[3] = readIntSerialBytes();
			break;
		case MODE:
			packet.vars.receiverCommand[4] = readIntSerialBytes();
			break;
		case AUX:
			packet.vars.receiverCommand[5] = readIntSerialBytes();
			break;
		default:
			return;
		}
	}

	// This is not a PID calibration packet
	packet.vars.flag = CONTROL_DATA;

	radio_send_wait(&packet, COPTER_ADDR);

	if (debug == 1) {
		for (i = 0; i < 6; i++) {
			Serial.print(packet.vars.receiverCommand[i]);
			Serial.print(" ");
		}
		Serial.println();
	}
}

void sendPidData() {
	float p, i, d, command;
	uint8_t pidIndex;
	radio_packet packet;

	pidIndex = int(readFloatSerial());
	p = readFloatSerial();
	i = readFloatSerial();
	d = readFloatSerial();

	Serial.print("Index: ");
	Serial.print(pidIndex);
	Serial.print(" P: ");
	Serial.print(p);
	Serial.print(" I: ");
	Serial.print(i);
	Serial.print(" D: ");
	Serial.println(d);

	Serial.println("Set these values? (y/n)");
	while (!Serial.available());
	command = Serial.read();
	if (command == 'n') {
		Serial.println("Calibration canceled.");

	} else if (command == 'y') {
		// Put data into packet and send
		Serial.println("Sending values.");
		packet.vars.pidIndex = pidIndex;
		packet.vars.p = p;
		packet.vars.i = i;
		packet.vars.d = d;
		packet.vars.flag = WRITE_PID;
		radio_send_wait(&packet, COPTER_ADDR);
	}
}

void readPidData(uint8_t pidIndex) {

	radio_packet packet;

	// Request read from index
	packet.vars.pidIndex = pidIndex;
	packet.vars.flag = READ_PID;
	radio_send_wait(&packet, COPTER_ADDR);

	if ( !radio_recv(1000, &packet) ) {
		Serial.println("No response received.");
		return;
	}

	// Print PID Data
	Serial.print("Index: ");
	Serial.print(packet.vars.pidIndex);
	Serial.print(" P: ");
	Serial.print(packet.vars.p);
	Serial.print(" I: ");
	Serial.print(packet.vars.i);
	Serial.print(" D: ");
	Serial.println(packet.vars.d);
}

void commitPid() {
	radio_packet packet;

	Serial.println("Committing PID values to EEPROM.");
	packet.vars.flag = COMMIT_PID;
	radio_send_wait(&packet, COPTER_ADDR);
}

//The setup function is called once at startup of the sketch
void setup() {
	Serial.begin(38400);

	// init radio address, channel, payload size
	radio_init(BASE_ADDR, RADIO_CHANNEL, RADIO_PAYLOAD);

}

// The loop function is called in an endless loop
void loop() {
	int command, i;

	if (!Serial.available()) {
		return;
	}

	// What kind of data is to be sent? Read first character.
	if ((command = Serial.read()) == 'c') { 		// send controller commands
		sendControllerData();
	} else if (command == 'p') { 					// set PID
		sendPidData();
	} else if (command == 'r') { 					// read PID
		if ( !waitSerialAvailable(10) )
			return;
		if (Serial.peek() == 'a') { 				// read all PID values
			Serial.read();
			for (i=0; i< 10; i++) {
				delay(20);
				readPidData(i);
			}
			return;
		} else { 									// read specific PID value
			readPidData( int(readFloatSerial()) );
		}
	} else if (command == 's') { 					// save current PID values to EEPROM
		commitPid();
	} else if (command == '#') {
		debug = !debug;
	}
}

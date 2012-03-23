// Do not remove the include below
#include "copter_remote.h"

void setup() {
	Serial.begin(9600);

	// init radio address, channel, payload size
	radio_init(BASE_ADDR, RADIO_CHANNEL, RADIO_PAYLOAD);

	Serial.println("Beginning ... ");
}

void loop() {
	radio_packet packet;
	int input, number;

	// Wait for input
	if (!Serial.available()) return;

	// Get first byte
	input = Serial.read();

	// emergency stop command is ' key, right next to enter key
	if (input == '\'') {
		packet.vars.speed = MOTOR_MIN_SPEED;
		packet.vars.motor = 'a';
		radio_send_wait(&packet, COPTER_ADDR);
		Serial.println("Sending stop command.");
		return;
	}

	// Convert string or numbers to integer. String terminated with m (for microseconds).
	number = input - '0';
	while ((input = Serial.read()) != 'm') {
		// Only accept characters 0-9
		if (input == -1 || input < '0' || input > '9')
			continue;

		number *= 10;
		number += input - '0';
	}

	// Check for valid motor range
	if (number < 700 || number > 2000) {
		Serial.print("Invalid motor speed: ");
		Serial.println(number);
		return;
	}

	// wait for motor specification
	while ((input = Serial.read()) == -1);
	if (input != 'a' && (input < '0' || input > '3') ) {
		Serial.print("Invalid motor selection: ");
		Serial.println(input);
		return;
	}

	// Send command
	packet.vars.speed = number;
	packet.vars.motor = input;
	radio_send_wait(&packet, COPTER_ADDR);

//	// Receive data before 1000ms
//	if (!radio_recv(1000, &packet)) {
//		Serial.println("Failed to receive response.");
//		delay(1000);
//		return;
//	}
}



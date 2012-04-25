/*
 * radio.cpp
 *
 *  Created on: Mar 20, 2012
 *      Author: garrett
 */

#include "radio.h"

/**
 * Pins:
 * Hardware SPI:
 * MISO -> 12
 * MOSI -> 11
 * SCK -> 13
 * CE -> 8
 * CSN -> 9
 * VCC -> 4
 */

/**
 * Initializes nRF24L01 Radio
 */
void radio_init(char * addr, int channel, int payload) {

	// Reset Radio in case it is in a bad state
	pinMode(4, OUTPUT);
	digitalWrite(4, LOW);
	delay(25);
	digitalWrite(4, HIGH);
	delay(25);

	/*
	 * Setup pins / SPI.
	 */
	Mirf.cePin = 8;
	Mirf.csnPin = 9;

	Mirf.spi = &MirfHardwareSpi;
	Mirf.init();

	/*
	 * Configure reciving address.
	 */
	Mirf.setRADDR((byte *)addr);

	/*
	 * Set the payload length to sizeof(unsigned long) the
	 * return type of millis().
	 *
	 * NB: payload on client and server must be the same.
	 */
	Mirf.payload = payload;

	/*
	 * Write channel and payload config then power up receiver.
	 */

	/*
	 * To change channel:
	 *
	 * Mirf.channel = 10;
	 *
	 * NB: Make sure channel is legal in your area.
	 */
	Mirf.channel = channel;

	Mirf.config();
}

/**
 * Sends a radio_packet to receiver at address addr and waits
 * for send to finish.
 */
void radio_send_wait(radio_packet * packet, char * addr) {

	Mirf.setTADDR((byte *)addr);

	Mirf.send(packet->data);

	while(Mirf.isSending()){
	}

	delay(20);
}

/**
 * Sends a radio_packet to receiver at address addr and returns.
 */
void radio_send_nowait(radio_packet * packet, char * addr) {
	Mirf.setTADDR((byte *)addr);
	Mirf.send(packet->data);
}

/**
 * Waits to receive data over a given timeout period.
 * Data put into packet structure give via pointer.
 */
int radio_recv(unsigned int timeout, radio_packet * packet) {
	unsigned long time = millis();
	while(!Mirf.dataReady()){
		//Serial.println("Waiting");
		if ( ( millis() - time ) > timeout ) {
			return 0;
		}
	}

	Mirf.getData(packet->data);
	return 1;
}

/**
 * Checks if a packet has been received.
 * If a packet has been received, data is added to radio_packet pointer
 * and 1 is returned.
 * Otherwise, 0 is returned.
 */
int radio_check_recv(radio_packet * packet) {
	/*
	 * If a packet has been received.
	 */
	if (!Mirf.isSending() && Mirf.dataReady()) {
		/*
		 * Get load the packet into the buffer.
		 */
		Mirf.getData(packet->data);
		return 1;
	} else {
		/* No data */
		return 0;
	}
}




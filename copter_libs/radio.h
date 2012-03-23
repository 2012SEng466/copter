/*
 * radio.h
 *
 *  Created on: Mar 20, 2012
 *      Author: garrett
 */

#ifndef RADIO_H_
#define RADIO_H_

#include "Arduino.h"
#include "SPI.h"
#include "Mirf/Mirf.h"
#include "Mirf/nRF24L01.h"
#include "Mirf/MirfHardwareSpiDriver.h"

/* Radio definitions */
#define RADIO_CHANNEL	108
#define RADIO_PAYLOAD	sizeof(radio_data)
#define COPTER_ADDR 	"coptr"
#define BASE_ADDR		"basss"

struct radio_data {
	char motor; // motor 0,1,2,3, or a for all
	int speed; // range 700-2000
};

typedef union radio_packet {
	byte data[RADIO_PAYLOAD];
	struct radio_data vars;
} radio_packet;

void radio_init(char * addr, int channel, int payload);
void radio_send_wait(radio_packet * packet, char * addr);
void radio_send_nowait(radio_packet * packet, char * addr);
int radio_recv(unsigned int timeout, radio_packet * packet);
int radio_check_recv(radio_packet * packet);


#endif /* RADIO_H_ */

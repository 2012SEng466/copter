/*
 * radio.h
 *
 *  Created on: Mar 20, 2012
 *      Author: garrett
 */

#ifndef RADIO_H_
#define RADIO_H_

#include <Arduino.h>
#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>

/* Radio definitions */
#define RADIO_CHANNEL	108
#define RADIO_PAYLOAD	sizeof(radio_data)
#define COPTER_ADDR 	"coptr"
#define BASE_ADDR		"basss"

#define READ_PID		0
#define WRITE_PID		1
#define CONTROL_DATA	2
#define COMMIT_PID		3

struct radio_data {
	int receiverCommand[6];
	float p, i, d;
	uint8_t pidIndex;
	uint8_t flag;
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

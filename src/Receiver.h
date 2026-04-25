#ifndef RECEIVER_H
#define RECEIVER_H

#include <Arduino.h>

#define RECEIVER_CHANNEL_1_PIN A0
#define RECEIVER_CHANNEL_2_PIN A1
#define RECEIVER_CHANNEL_3_PIN A2
#define RECEIVER_CHANNEL_4_PIN A3
#define RECEIVER_CHANNEL_5_PIN A4
#define RECEIVER_CHANNEL_6_PIN A5

#define MIN_PULSE_TIME 1100
#define MAX_PULSE_TIME 1900

class Receiver {
public:
	Receiver();
	int readChannel(int channel);
	unsigned long readChannelRaw(int channel);
};

#endif

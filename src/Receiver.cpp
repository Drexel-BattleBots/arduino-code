#include "Receiver.h"

Receiver::Receiver() {
	pinMode(RECEIVER_CHANNEL_1_PIN, INPUT);
	pinMode(RECEIVER_CHANNEL_2_PIN, INPUT);
	pinMode(RECEIVER_CHANNEL_3_PIN, INPUT);
	pinMode(RECEIVER_CHANNEL_4_PIN, INPUT);
	pinMode(RECEIVER_CHANNEL_5_PIN, INPUT);
	pinMode(RECEIVER_CHANNEL_6_PIN, INPUT);
}

int Receiver::readChannel(int channel) {
	unsigned long raw_value = readChannelRaw(channel);
	if (raw_value <= MIN_PULSE_TIME) {
		return 0;
	} else if (raw_value >= MAX_PULSE_TIME) {
		return 255;
	}

	unsigned long range = MAX_PULSE_TIME - MIN_PULSE_TIME;
	return ((raw_value - MIN_PULSE_TIME) * 255) / range;
}

unsigned long Receiver::readChannelRaw(int channel) {
	switch (channel) {
		case 1: return pulseIn(RECEIVER_CHANNEL_1_PIN, HIGH);
		case 2: return pulseIn(RECEIVER_CHANNEL_2_PIN, HIGH);
		case 3: return pulseIn(RECEIVER_CHANNEL_3_PIN, HIGH);
		case 4: return pulseIn(RECEIVER_CHANNEL_4_PIN, HIGH);
		case 5: return pulseIn(RECEIVER_CHANNEL_5_PIN, HIGH);
		case 6: return pulseIn(RECEIVER_CHANNEL_6_PIN, HIGH);
		default: return -1;
	}
}

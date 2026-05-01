#ifndef LOCOMOTION_H
#define LOCOMOTION_H

#include "MotorSystem.h"

#include <Arduino.h>

class Shuffler {
public:
	Shuffler(int controlPin);
	void setThrottle(int value);

private:
	int controlPin;
};

class Locomotion : public MotorSystem {
public:
	Locomotion(int enablePin, int leftControlPin, int rightControlPin);
	void arm() override;
	void disarm() override;
	void enable() override;
	void disable() override;
	bool isArmed() override;
	bool isEnabled() override;

	void setThrottle(int value);
	void setSteering(int value);

private:
	int enablePin;
	Shuffler leftShuffler;
	Shuffler rightShuffler;
	bool enabled;
};

#endif

#ifndef LOCOMOTION_H
#define LOCOMOTION_H

#include "MotorSystem.h"

#include <Arduino.h>

class Locomotion : public MotorSystem {
public:
	Locomotion(int enablePin, int controlPin);
	void arm() override;
	void disarm() override;
	void enable() override;
	void disable() override;
	bool isArmed() override;
	bool isEnabled() override;

	void setThrottle(int value);
	void setSteering(int value);
};

#endif

#ifndef WEAPON_H
#define WEAPON_H

#include "MotorSystem.h"

#include <Arduino.h>

class Weapon : public MotorSystem {
public:
	Weapon(int enablePin, int controlPin);
	void arm() override;
	void disarm() override;
	void enable() override;
	void disable() override;
	bool isArmed() override;
	bool isEnabled() override;

	void setThrottle(unsigned long value);

private:
	int enablePin;
	int controlPin;
};

#endif

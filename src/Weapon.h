#ifndef WEAPON_H
#define WEAPON_H

#include "MotorSystem.h"

#include <Arduino.h>

#define WEAPON_ENABLE_PIN 4
#define WEAPON_CONTROL_PIN 5

class Weapon : public MotorSystem {
public:
	Weapon();
	void arm() override;
	void disarm() override;
	void enable() override;
	void disable() override;
	bool isArmed() override;
	bool isEnabled() override;

	void setThrottle(unsigned long value);
};

#endif

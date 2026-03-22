#ifndef WEAPON_H
#define WEAPON_H

#include "MotorSystem.h"

class Weapon : public MotorSystem {
public:
	void arm() override;
	void disarm() override;
	void enable() override;
	void disable() override;
	bool isArmed() override;
	bool isEnabled() override;

	void setSpeed(int value);
};

#endif

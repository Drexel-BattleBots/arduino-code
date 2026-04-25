#ifndef MOTOR_SYSTEM_H
#define MOTOR_SYSTEM_H

class MotorSystem {
public:
	virtual void arm() = 0;
	virtual void disarm() = 0;
	virtual void enable() = 0;
	virtual void disable() = 0;
	virtual bool isArmed() = 0;
	virtual bool isEnabled() = 0;

protected:
	bool armed = false;
	bool enabled = false;
};

#endif

#include "Weapon.h"

Weapon::Weapon(int enablePin, int controlPin)
	: enablePin(enablePin), controlPin(controlPin) {
	pinMode(this->enablePin, OUTPUT);
	digitalWrite(this->enablePin, LOW);
}

void Weapon::arm() {
	digitalWrite(enablePin, HIGH);
	controlServo.attach(controlPin);
	controlServo.writeMicroseconds(1000); // minimum throttle for ESC arming
}

void Weapon::disarm() {
	controlServo.writeMicroseconds(1500);
	controlServo.detach();
	digitalWrite(enablePin, LOW);
}

bool Weapon::isArmed() {
	return digitalRead(enablePin) == HIGH;
}

void Weapon::enable() {
	enabled = true;
}

void Weapon::disable() {
	enabled = false;
	controlServo.writeMicroseconds(1500);
}

bool Weapon::isEnabled() {
	return enabled;
}

void Weapon::setThrottle(unsigned long value) {
	if (!enabled)
		return;

	controlServo.writeMicroseconds(value);
}

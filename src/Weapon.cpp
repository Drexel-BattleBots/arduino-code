#include "Weapon.h"

Weapon::Weapon(int enablePin, int controlPin) {
	pinMode(enablePin, OUTPUT);
	digitalWrite(enablePin, LOW);

	pinMode(controlPin, OUTPUT);
	digitalWrite(controlPin, LOW);
}

void Weapon::arm() {
	digitalWrite(enablePin, HIGH);
}

void Weapon::disarm() {
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
	digitalWrite(controlPin, LOW); //TODO: REMOVE LATER
}

bool Weapon::isEnabled() {
	return enabled;
}

void Weapon::setThrottle(unsigned long value) {
	if (!enabled)
		return;

	digitalWrite(controlPin, HIGH);
	delayMicroseconds(value);
	digitalWrite(controlPin, LOW);
	delayMicroseconds(20000 - value);
}

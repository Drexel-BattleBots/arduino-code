#include "Locomotion.h"

Locomotion::Locomotion(int enablePin, int controlPin) {
	pinMode(enablePin, OUTPUT);
	digitalWrite(enablePin, LOW);
	pinMode(controlPin, OUTPUT);
	digitalWrite(controlPin, LOW);
}

void Locomotion::arm() {
	digitalWrite(enablePin, HIGH);
}

void Locomotion::disarm() {
	digitalWrite(enablePin, LOW);
}

bool Locomotion::isArmed() {
	return digitalRead(enablePin) == HIGH;
}

void Locomotion::enable() {
	enabled = true;
}

void Locomotion::disable() {
	enabled = false;
}

bool Locomotion::isEnabled() {
	return enabled;
}

void Locomotion::setThrottle(int value) {
	if (!enabled)
		return;

	analogWrite(controlPin, value);
}

void Locomotion::setSteering(int value) {
	if (!enabled)
		return;

}
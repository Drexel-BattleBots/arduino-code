#include "Locomotion.h"

Locomotion::Locomotion() {
	pinMode(LOCOMOTION_ENABLE_PIN, OUTPUT);
	digitalWrite(LOCOMOTION_ENABLE_PIN, LOW);
	pinMode(LOCOMOTION_CONTROL_PIN, OUTPUT);
	digitalWrite(LOCOMOTION_CONTROL_PIN, LOW);
}

void Locomotion::arm() {
	digitalWrite(LOCOMOTION_ENABLE_PIN, HIGH);
}

void Locomotion::disarm() {
	digitalWrite(LOCOMOTION_ENABLE_PIN, LOW);
}

bool Locomotion::isArmed() {
	return digitalRead(LOCOMOTION_ENABLE_PIN) == HIGH;
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

	analogWrite(LOCOMOTION_CONTROL_PIN, value);
}

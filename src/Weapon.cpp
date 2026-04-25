#include "Weapon.h"

Weapon::Weapon() {
	pinMode(WEAPON_ENABLE_PIN, OUTPUT);
	digitalWrite(WEAPON_ENABLE_PIN, LOW);

	pinMode(WEAPON_CONTROL_PIN, OUTPUT);
	digitalWrite(WEAPON_CONTROL_PIN, LOW);
}

void Weapon::arm() {
	digitalWrite(WEAPON_ENABLE_PIN, HIGH);
}

void Weapon::disarm() {
	digitalWrite(WEAPON_ENABLE_PIN, LOW);
}

bool Weapon::isArmed() {
	return digitalRead(WEAPON_ENABLE_PIN) == HIGH;
}

void Weapon::enable() {
	enabled = true;
}

void Weapon::disable() {
	enabled = false;
	digitalWrite(WEAPON_CONTROL_PIN, LOW); //TODO: REMOVE LATER
}

bool Weapon::isEnabled() {
	return enabled;
}

void Weapon::setThrottle(unsigned long value) {
	if (!enabled)
		return;

	digitalWrite(WEAPON_CONTROL_PIN, HIGH);
	delayMicroseconds(value);
	digitalWrite(WEAPON_CONTROL_PIN, LOW);
	delayMicroseconds(20000 - value);
	//analogWrite(WEAPON_CONTROL_PIN, value);
}

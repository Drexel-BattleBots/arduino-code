#include "Locomotion.h"

Shuffler::Shuffler(int controlPin)
	: controlPin(controlPin) {
	pinMode(this->controlPin, OUTPUT);
	digitalWrite(this->controlPin, LOW);
}

void Shuffler::setThrottle(int value) {
	digitalWrite(controlPin, HIGH);
	delayMicroseconds(value);
	digitalWrite(controlPin, LOW);
	delayMicroseconds(20000 - value);
}

Locomotion::Locomotion(int enablePin, int leftControlPin, int rightControlPin)
	: enablePin(enablePin), leftShuffler(leftControlPin), rightShuffler(rightControlPin), enabled(false) {
	pinMode(enablePin, OUTPUT);
	digitalWrite(enablePin, LOW);
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

	int leftValue = constrain(value, 1000, 2000);
	int rightValue = 3000 - leftValue; // mirror around 1500us: 1750 -> 1250
	rightValue = constrain(rightValue, 1000, 2000);

	leftShuffler.setThrottle(leftValue);

	rightShuffler.setThrottle(rightValue);
}

void Locomotion::setSteering(int value) {
	if (!enabled)
		return;
}
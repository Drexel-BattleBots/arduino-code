#include "Locomotion.h"

Shuffler::Shuffler(int throttlePin, int steerPin)
	: throttlePin(throttlePin), steerPin(steerPin) {
	pinMode(this->throttlePin, OUTPUT);
	pinMode(this->steerPin, OUTPUT);
	digitalWrite(this->throttlePin, LOW);
	digitalWrite(this->steerPin, LOW);
}

void Shuffler::setThrottle(int value) {
	digitalWrite(throttlePin, HIGH);
	delayMicroseconds(value);
	digitalWrite(throttlePin, LOW);
	delayMicroseconds(20000 - value);
}

void Shuffler::setSteering(int value) {
	digitalWrite(steerPin, HIGH);
	delayMicroseconds(value);
	digitalWrite(steerPin, LOW);
	delayMicroseconds(20000 - value);
}

Locomotion::Locomotion(int enablePin, Shuffler leftShuffler, Shuffler rightShuffler)
	: enablePin(enablePin), leftShuffler(leftShuffler), rightShuffler(rightShuffler), enabled(false) {
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

void Locomotion::setSteering(int value) { //TODO: YOU MIGHT BE ABLE TO JUST BE GOOD WITH ONE VALUE;
	// NOT BOTH LEFT AND RIGHT SEPARATE
	if (!enabled)
		return;

	int leftValue = constrain(value, 1000, 2000);
	int rightValue = 3000 - leftValue; // mirror around 1500us: 1750 -> 1250
	rightValue = constrain(rightValue, 1000, 2000);

	leftShuffler.setSteering(leftValue);

	rightShuffler.setSteering(rightValue);
}
#include "Locomotion.h"

Shuffler::Shuffler(int throttlePin, int steerPin)
	: throttlePin(throttlePin), steerPin(steerPin) {}

void Shuffler::attach() {
	throttleServo.attach(throttlePin);
	steerServo.attach(steerPin);
	throttleServo.writeMicroseconds(1500); // neutral
	steerServo.writeMicroseconds(1500);
}

void Shuffler::detach() {
	throttleServo.detach();
	steerServo.detach();
}

void Shuffler::setThrottle(int value) {
	if (value == 0) { // Quick fail
		return;
	}

	throttleServo.writeMicroseconds(value);
}

void Shuffler::setSteering(int value) {
	if (value == 0) { // Quick fail
		return;
	}

	steerServo.writeMicroseconds(value);
}

Locomotion::Locomotion(int enablePin, Shuffler &leftShuffler, Shuffler &rightShuffler)
	: enablePin(enablePin), leftShuffler(leftShuffler), rightShuffler(rightShuffler), enabled(false) {
	pinMode(enablePin, OUTPUT);
	digitalWrite(enablePin, LOW);
}

void Locomotion::arm() {
	digitalWrite(enablePin, HIGH);
	leftShuffler.attach();
	rightShuffler.attach();
}

void Locomotion::disarm() {
	leftShuffler.detach();
	rightShuffler.detach();
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
	if (!enabled || value == 0) // Quick fail for both not being enabled OR trying to set 0;
		return;

	int leftValue = constrain(value, 1000, 2000);
	int rightValue = 3000 - leftValue;
	rightValue = constrain(rightValue, 1000, 2000);

	leftShuffler.setThrottle(leftValue);
	rightShuffler.setThrottle(rightValue);
}

void Locomotion::setSteering(int value) {
	if (!enabled || value == 0) // Quick fail for both not being enabled OR trying to set 0;
		return;

	int leftValue = constrain(value, 1000, 2000);
	int rightValue = 3000 - leftValue;
	rightValue = constrain(rightValue, 1000, 2000);

	leftShuffler.setSteering(leftValue);
	rightShuffler.setSteering(rightValue);
}

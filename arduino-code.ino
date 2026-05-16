#include "src/Locomotion.h"
#include "src/Weapon.h"
#include "src/Receiver.h"
#include "src/helpers.h"

/* PIN DEFINITIONS */

#define WEAPON_ARM_PIN 2
#define LOCOMOTION_ARM_PIN 3

#define WEAPON_ENABLE_PIN 4
#define WEAPON_CONTROL_PIN 5
#define LOCOMOTION_ENABLE_PIN 6
#define LEFT_SHUFFLER_THROTTLE_PIN 7
#define LEFT_SHUFFLER_STEER_PIN 9
#define RIGHT_SHUFFLER_THROTTLE_PIN 8
#define RIGHT_SHUFFLER_STEER_PIN 10

/* CHANNEL DEFINITIONS */

#define WEAPON_THROTTLE_CHANNEL 2
#define LOCOMOTION_THROTTLE_CHANNEL 3
#define LOCOMOTION_STEERING_CHANNEL 4
#define LOCOMOTION_TOGGLE_CHANNEL 5
#define WEAPON_TOGGLE_CHANNEL 6

/* PWM SETTINGS */

#define PWM_BOUNDARY 0.8

Shuffler leftShuffler{LEFT_SHUFFLER_THROTTLE_PIN, LEFT_SHUFFLER_STEER_PIN};
Shuffler rightShuffler{RIGHT_SHUFFLER_THROTTLE_PIN, RIGHT_SHUFFLER_STEER_PIN};
Locomotion locomotion{LOCOMOTION_ENABLE_PIN, leftShuffler, rightShuffler};
Weapon weapon{WEAPON_ENABLE_PIN, WEAPON_CONTROL_PIN};
Receiver receiver{};

volatile uint32_t weaponToggleStartTime = 0;
volatile uint32_t weaponTogglePulseWidth = 1500;
volatile uint32_t locomotionToggleStartTime = 0;
volatile uint32_t locomotionTogglePulseWidth = 1500;

unsigned long lastPrintTime = 0;
#define PRINT_INTERVAL_MS 200


void isrWeaponTogglePulse() {
	if (digitalRead(WEAPON_ARM_PIN) == HIGH) {
		weaponToggleStartTime = micros();
	} else {
		weaponTogglePulseWidth = micros() - weaponToggleStartTime;
	}
}

void isrLocomotionTogglePulse() {
	if (digitalRead(LOCOMOTION_ARM_PIN) == HIGH) {
		locomotionToggleStartTime = micros();
	} else {
		locomotionTogglePulseWidth = micros() - locomotionToggleStartTime;
	}
}

void setMovement() {
	if (locomotion.isEnabled()) {
		unsigned long locomotion_throttle = receiver.readChannelRaw(LOCOMOTION_THROTTLE_CHANNEL);

		if (locomotion_throttle == 0) { // FAILSAFE (NO SIGNAL FROM CONTROLLER; GO NEUTRAL)
			locomotion.setThrottle(1500);
			Serial.println("!!!LOCOMOTION THROTTLE FAILSAFE!!!");
			return;
		}
		locomotion_throttle = chokeServoPWM(locomotion_throttle, 1500, PWM_BOUNDARY);
		if (locomotion_throttle > 1450 && locomotion_throttle < 1550) {
    	locomotion_throttle = 1500; // deadzone
		}

		Serial.print("Locomotion Throttle: ");
		Serial.println(locomotion_throttle);

		unsigned long locomotion_steering = receiver.readChannelRaw(LOCOMOTION_STEERING_CHANNEL);

		if (locomotion_steering == 0) {
			locomotion.setThrottle(1500); // FAILSAFE FOR STEERING TOO
			Serial.println("!!!LOCOMOTION STEERING FAILSAFE!!!");
			return;
		}

		locomotion_steering = chokeServoPWM(locomotion_steering, 1500, PWM_BOUNDARY);
		if (locomotion_steering > 1450 && locomotion_steering < 1550) {
			locomotion_steering = 1500; // deadzone
		}

		Serial.print("Locomotion Steering: ");
		Serial.println(locomotion_steering);
		//locomotion.setSteering(locomotion_steering);

		int norm_throttle = 1500 - locomotion_throttle;
		int norm_steering = locomotion_steering - 1500;

		int left = 1500 + (norm_throttle + norm_steering);
		int right = 1500 + (norm_throttle - norm_steering);

		right = 3000 - right;

		left = constrain(left, 1000, 2000);
		right = constrain(right, 1000, 2000);

		leftShuffler.setThrottle(left);
		rightShuffler.setThrottle(right);
	}
}

void setWeapon() {
	if (weapon.isEnabled()) {
		unsigned long weapon_throttle = receiver.readChannelRaw(WEAPON_THROTTLE_CHANNEL);

		if (weapon_throttle == 0) {// FAILSAFE FOR WEAPON
			weapon.setThrottle(1500);
			Serial.println("!!!WEAPON FAILSAFE!!!");
			return;
		}

		if (weapon_throttle > 1450 && weapon_throttle < 1550) {
			weapon_throttle = 1500; // deadzone
		}

		Serial.print("Weapon Throttle: ");
		Serial.println(weapon_throttle);
		weapon.setThrottle(weapon_throttle);
	}
}

void setup() {
	Serial.begin(115200);
	Serial.println("Serial Monitor Initialized");

	if (digitalPinToInterrupt(WEAPON_ARM_PIN) != -1) { // Check if pin is interrupt-capable
		Serial.println("Set up weapon toggle interrupt");
		pinMode(WEAPON_ARM_PIN, INPUT);
		attachInterrupt(digitalPinToInterrupt(WEAPON_ARM_PIN), isrWeaponTogglePulse, CHANGE);
	} else {
		Serial.println("Failed to set up weapon toggle interrupt");
	}

	if (digitalPinToInterrupt(LOCOMOTION_ARM_PIN) != -1) { // Check if pin is interrupt-capable
		Serial.println("Set up locomotion toggle interrupt");
		pinMode(LOCOMOTION_ARM_PIN, INPUT);
		attachInterrupt(digitalPinToInterrupt(LOCOMOTION_ARM_PIN), isrLocomotionTogglePulse, CHANGE);
	} else {
		Serial.println("Failed to set up locomotion toggle interrupt");
	}
}

void loop() {
	bool shouldPrint = (millis() - lastPrintTime >= PRINT_INTERVAL_MS);	if (shouldPrint) lastPrintTime = millis();

	bool armWeapon = (weaponTogglePulseWidth > 1750);
	bool armLocomotion = (locomotionTogglePulseWidth > 1750);

	if (armWeapon && !weapon.isArmed()) {
		weapon.arm();
		weapon.enable();
		Serial.println("Weapon Armed & Enabled");
	} else if (!armWeapon && weapon.isArmed()) {
		weapon.setThrottle(1500); // disable throttle
		weapon.disarm();
		weapon.disable();
		Serial.println("Weapon Disarmed & Disabled");
	}

	if (armLocomotion && !locomotion.isArmed()) {
		locomotion.arm();
		locomotion.enable();
		Serial.println("Locomotion Armed & Enabled");
	} else if (!armLocomotion && locomotion.isArmed()) {
		locomotion.setThrottle(1500); // disable throttle
		locomotion.disarm();
		locomotion.disable();
		Serial.println("Locomotion Disarmed & Disabled");
	}

	if (Serial.available()) {
		// Read incoming data and update control values

		String cmd = Serial.readStringUntil('\n');
		Serial.print("cmd: ");
		Serial.println(cmd);

		if (cmd == "L_ARM") {
			locomotion.arm();
			Serial.println("Locomotion Armed");
		} else if (cmd == "L_DISARM") {
			locomotion.disarm();
			Serial.println("Locomotion Disarmed");
		} else if (cmd == "W_ARM") {
			weapon.arm();
			Serial.println("Weapon Armed");
		} else if (cmd == "W_DISARM") {
			weapon.disarm();
			Serial.println("Weapon Disarmed");
		} else if (cmd == "L_ENABLE") {
			locomotion.enable();
			Serial.println("Locomotion Enabled");
		} else if (cmd == "L_DISABLE") {
			locomotion.disable();
			Serial.println("Locomotion Disabled");
		} else if (cmd == "W_ENABLE") {
			weapon.enable();
			Serial.println("Weapon Enabled");
		} else if (cmd == "W_DISABLE") {
			weapon.disable();
			Serial.println("Weapon Disabled");
		} else {
			Serial.println("Unknown Command");
		}
	}

	setMovement();
	setWeapon();
}

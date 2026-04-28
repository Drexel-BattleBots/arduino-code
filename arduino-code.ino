#include "src/Locomotion.h"
#include "src/Weapon.h"
#include "src/Receiver.h"

#define WEAPON_THROTTLE_CHANNEL 2
#define LOCOMOTION_THROTTLE_CHANNEL 3
#define WEAPON_TOGGLE_CHANNEL 6
#define WEAPON_TOGGLE_PIN 2
#define LOCOMOTION_TOGGLE_CHANNEL 5

Locomotion locomotion{};
Weapon weapon{};
Receiver receiver{};

volatile uint32_t weaponToggleStartTime = 0;
volatile uint32_t weaponTogglePulseWidth = 1500;

void isrWeaponTogglePulse() {
	if (digitalRead(WEAPON_TOGGLE_PIN) == HIGH) {
		weaponToggleStartTime = micros();
	} else {
		weaponTogglePulseWidth = micros() - weaponToggleStartTime;
	}
}

void setup() {
	Serial.begin(9600);
	Serial.println("Serial Monitor Initialized");

	if (digitalPinToInterrupt(WEAPON_TOGGLE_PIN) != -1) { // Check if pin is interrupt-capable
		Serial.println("ALL GOOD");
		pinMode(WEAPON_TOGGLE_PIN, INPUT);
		attachInterrupt(digitalPinToInterrupt(WEAPON_TOGGLE_PIN), isrWeaponTogglePulse, CHANGE);
	} else {
		Serial.println("NOT GOOD");
	}
}

void loop() {
	bool armWeapon = (weaponTogglePulseWidth > 1750);

	if (armWeapon && !weapon.isArmed()) {
		weapon.arm();
		weapon.enable();
		Serial.println("Weapon Armed & Enabled");
	} else if (!armWeapon && weapon.isArmed()) {
		weapon.disarm();
		weapon.disable();
		Serial.println("Weapon Disarmed & Disabled");
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

		if (locomotion.isEnabled()) {
			unsigned long locomotion_throttle = receiver.readChannelRaw(LOCOMOTION_THROTTLE_CHANNEL);
			Serial.print("Locomotion Throttle: ");
			Serial.println(locomotion_throttle);
			locomotion.setThrottle(locomotion_throttle);
		} else {
			//Serial.println("Weapon is disabled, skipping throttle update");
		}

	//locomotion.setThrottle(receiver.readChannel(LOCOMOTION_CONTROL_PIN));
	if (weapon.isEnabled()) {
		unsigned long weapon_throttle = receiver.readChannelRaw(WEAPON_THROTTLE_CHANNEL);
		Serial.print("Weapon Throttle: ");
		Serial.println(weapon_throttle);
		weapon.setThrottle(weapon_throttle);
	} else {
		//Serial.println("Weapon is disabled, skipping throttle update");
	}
}
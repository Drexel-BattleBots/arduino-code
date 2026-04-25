#include "src/Locomotion.h"
#include "src/Weapon.h"
#include "src/Receiver.h"

#define WEAPON_THROTTLE_CHANNEL 3

Locomotion locomotion{};
Weapon weapon{};
Receiver receiver{};

void setup() {
	Serial.begin(9600);
	Serial.println("Serial Monitor Initialized");
}

void loop() {
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
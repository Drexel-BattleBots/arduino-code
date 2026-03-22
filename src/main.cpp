#include <Arduino.h>

const int CH1_PIN = A0;
const int CH2_PIN = A1;
const int CH3_PIN = A2;
const int CH4_PIN = A3;
const int CH5_PIN = A4;
const int CH6_PIN = A5;

const int ESC_PWM1_PIN = 3;
const int ESC_PWM2_PIN = 5;

void setup() {
  Serial.begin(9600);
  Serial.println("CH1\tCH2\tCH3\tCH4\tCH5\tCH6");
}

void loop() {
  int ch1_value = analogRead(CH1_PIN);
  int ch2_value = analogRead(CH2_PIN);
  int ch3_value = analogRead(CH3_PIN);
  int ch4_value = analogRead(CH4_PIN);
  int ch5_value = analogRead(CH5_PIN);
  int ch6_value = analogRead(CH6_PIN);

  Serial.print(ch1_value);
  Serial.print("\t");
  Serial.print(ch2_value);
  Serial.print("\t");
  Serial.print(ch3_value);
  Serial.print("\t");
  Serial.print(ch4_value);
  Serial.print("\t");
  Serial.print(ch5_value);
  Serial.print("\t");
  Serial.println(ch6_value);
}

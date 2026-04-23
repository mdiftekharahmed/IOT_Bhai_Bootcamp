#include <avr/sleep.h>
#include <avr/power.h>

const byte LDR_DO_PIN = 2;   // External interrupt pin INT0
const byte LED_PIN    = 13;

volatile bool wokeUp = false;

// Interrupt Service Routine
void wakeUpISR() {
  wokeUp = true;
}

void goToSleep() {
  // Make sure interrupt flag is clear
  wokeUp = false;

  // Set sleep mode to deepest sleep
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();

  // Attach interrupt on pin 2
  // For Arduino UNO in POWER-DOWN, LOW is the safest wake source
  attachInterrupt(digitalPinToInterrupt(LDR_DO_PIN), wakeUpISR, LOW);

  // Small delay so serial output finishes
  delay(50);

  // Enter sleep
  sleep_cpu();

  // Code continues here after wake-up
  sleep_disable();

  // Important: detach interrupt after wake-up
  detachInterrupt(digitalPinToInterrupt(LDR_DO_PIN));
}

void setup() {
  Serial.begin(9600);

  pinMode(LED_PIN, OUTPUT);
  pinMode(LDR_DO_PIN, INPUT);   // If module output is open collector, use INPUT_PULLUP instead

  digitalWrite(LED_PIN, LOW);

  Serial.println("Arduino UNO Wake on Light Ready...");
  delay(1000);
}

void loop() {

  Serial.println("......");
  // Blink twice before sleeping
  Serial.println("Going to sleep...");
  for (int i = 0; i < 2; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(200);
    digitalWrite(LED_PIN, LOW);
    delay(200);
  }

  delay(500);
  goToSleep();

  // After wake-up
  Serial.println("Woke up due to light change!");

  // Indicate wake-up
  for (int i = 0; i < 5; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(150);
    digitalWrite(LED_PIN, LOW);
    delay(150);
  }

  delay(1000);
}
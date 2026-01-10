#include "esp32-hal-gpio.h"

// =====================
// PARAMETRY
// =====================
uint16_t pwm_frequency = 5000;
const unsigned long debounceTime = 50;

// =====================
// SSR
// =====================
#define PIN_SSR_PLUS     17
#define PIN_SSR_MINUS    16
#define PIN_SSR_PLUS_2   4

// =====================
// ENKODER / PILOT
// =====================
#define encoderPinA   36
#define encoderPinB   39
#define encoderPinAi  35
#define encoderPinBi  34

// =====================
// MOSTEK H
// =====================
#define enablePin     5
#define turnLeftPin   18
#define turnRightPin  19

// =====================
// KRAŃCÓWKI
// =====================
#define krGornaPin 33
#define krDolnaPin 32

// =====================
// PRZYCISKI
// =====================
#define BUTTON_UP_MOMENTARY_PIN    14
#define BUTTON_DOWN_MOMENTARY_PIN  27
#define BUTTON_DOWN_SET_PIN        25
#define BUTTON_UP_SET_PIN          26

bool BUTTON_UP_MOMENTARY_PIN_wcisniety   = false;
bool BUTTON_DOWN_MOMENTARY_PIN_wcisniety = false;
bool BUTTON_DOWN_SET_PIN_wcisniety       = false;
bool BUTTON_UP_SET_PIN_wcisniety         = false;

bool PILOT_UP_PIN_A_MOMENTARY_wcisniety   = false;
bool PILOT_DOWN_PIN_B_MOMENTARY_wcisniety = false;
bool PILOT_DOWN_Ai_SET_PIN_wcisniety      = false;
bool PILOT_UP_Bi_SET_PIN_wcisniety        = false;

// =====================
// INIT
// =====================
void init_wejscia_wyjscia() {

  pinMode(PIN_SSR_PLUS, OUTPUT);
  pinMode(PIN_SSR_MINUS, OUTPUT);
  pinMode(PIN_SSR_PLUS_2, OUTPUT);

  pinMode(enablePin, OUTPUT);
  pinMode(turnLeftPin, OUTPUT);
  pinMode(turnRightPin, OUTPUT);

  ledcAttach(turnLeftPin, pwm_frequency, 8);
  ledcAttach(turnRightPin, pwm_frequency, 8);

  pinMode(krGornaPin, INPUT_PULLUP);
  pinMode(krDolnaPin, INPUT_PULLUP);

  pinMode(BUTTON_UP_SET_PIN, INPUT_PULLUP);
  pinMode(BUTTON_DOWN_SET_PIN, INPUT_PULLUP);
  pinMode(BUTTON_UP_MOMENTARY_PIN, INPUT_PULLUP);
  pinMode(BUTTON_DOWN_MOMENTARY_PIN, INPUT_PULLUP);

  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);
  pinMode(encoderPinAi, INPUT_PULLUP);
  pinMode(encoderPinBi, INPUT_PULLUP);
}
void init_przyciski() {
  pinMode(BUTTON_UP_SET_PIN, INPUT_PULLUP);
  pinMode(BUTTON_DOWN_SET_PIN, INPUT_PULLUP);
  pinMode(BUTTON_UP_MOMENTARY_PIN, INPUT_PULLUP);
  pinMode(BUTTON_DOWN_MOMENTARY_PIN, INPUT_PULLUP);
}

bool wejscieA() {
  static bool lastReading = HIGH;
  static bool stableState = HIGH;
  static unsigned long lastChange = 0;

  bool reading = digitalRead(encoderPinA);

  if (reading != lastReading) {
    lastReading = reading;
    lastChange = millis();
  }

  if (millis() - lastChange > 50) { // debounce 50 ms
    stableState = lastReading;
  }

  return (stableState == LOW); // aktywne = 0V
}

bool wejscieB() {
  static bool lastReading = HIGH;
  static bool stableState = HIGH;
  static unsigned long lastChange = 0;

  bool reading = digitalRead(encoderPinB);

  if (reading != lastReading) {
    lastReading = reading;
    lastChange = millis();
  }

  if (millis() - lastChange > 50) {
    stableState = lastReading;
  }

  return (stableState == LOW);
}

bool wejscieAi() {
  static bool lastReading = HIGH;
  static bool stableState = HIGH;
  static unsigned long lastChange = 0;

  bool reading = digitalRead(encoderPinAi);

  if (reading != lastReading) {
    lastReading = reading;
    lastChange = millis();
  }

  if (millis() - lastChange > 50) {
    stableState = lastReading;
  }

  return (stableState == LOW);
}

bool wejscieBi() {
  static bool lastReading = HIGH;
  static bool stableState = HIGH;
  static unsigned long lastChange = 0;

  bool reading = digitalRead(encoderPinBi);

  if (reading != lastReading) {
    lastReading = reading;
    lastChange = millis();
  }

  if (millis() - lastChange > 50) {
    stableState = lastReading;
  }

  return (stableState == LOW);
}
// =====================
// ODCZYT PRZYCISKÓW
// =====================
void obsluz_przyciski() {
  init_przyciski();
  BUTTON_UP_MOMENTARY_PIN_wcisniety   = (digitalRead(BUTTON_UP_MOMENTARY_PIN) == LOW);
  BUTTON_DOWN_MOMENTARY_PIN_wcisniety = (digitalRead(BUTTON_DOWN_MOMENTARY_PIN) == LOW);
  BUTTON_DOWN_SET_PIN_wcisniety       = (digitalRead(BUTTON_DOWN_SET_PIN) == LOW);
  BUTTON_UP_SET_PIN_wcisniety         = (digitalRead(BUTTON_UP_SET_PIN) == LOW);

  PILOT_UP_PIN_A_MOMENTARY_wcisniety   = wejscieA();
  PILOT_DOWN_PIN_B_MOMENTARY_wcisniety = wejscieB();
  PILOT_DOWN_Ai_SET_PIN_wcisniety      = wejscieAi();
  PILOT_UP_Bi_SET_PIN_wcisniety        = wejscieBi();
}





bool dajStanKrGornej() {
  static bool lastReading = HIGH;
  static bool stableState = HIGH;
  static unsigned long lastChange = 0;

  bool reading = digitalRead(krGornaPin);

  if (reading != lastReading) {
    lastReading = reading;
    lastChange = millis();
  }

  if (millis() - lastChange > debounceTime) {
    stableState = lastReading;
  }

  return (stableState == HIGH) ? false : true;
}

bool dajStanKrDolnej() {
  static bool lastReading = HIGH;
  static bool stableState = HIGH;
  static unsigned long lastChange = 0;

  bool reading = digitalRead(krDolnaPin);

  if (reading != lastReading) {
    lastReading = reading;
    lastChange = millis();
  }

  if (millis() - lastChange > debounceTime) {
    stableState = lastReading;
  }

  return (stableState == HIGH) ? false : true;
}

void monitoruj_krancowki() {
  // Odczyt krańcówek z debouncem
  krGorna = dajStanKrGornej();
  krDolna = dajStanKrDolnej();
}


float pwmValue = 0.0;
const float pwmStep = 0.5;
const float pwmMax = 255.0;

bool wDeadTime = false;

// detekcja zbocza SET
bool setUpPrev = false;
bool setDownPrev = false;

unsigned long obliczSekundyDoKonca() {
  if (!trybSET) return 0;

  unsigned long elapsed = millis() - startCzasJazdy;

  if (jedzie_w_gore) {
    if (elapsed >= czasOtwierania) return 0;
    return (czasOtwierania - elapsed) / 1000;
  }

  if (jedzie_w_dol) {
    if (elapsed >= czasZamykania) return 0;
    return (czasZamykania - elapsed) / 1000;
  }

  return 0;
}

void wlaczSSR() {
  digitalWrite(PIN_SSR_PLUS, HIGH);
  digitalWrite(PIN_SSR_MINUS, LOW);
  digitalWrite(PIN_SSR_PLUS_2, HIGH);
  digitalWrite(enablePin, HIGH);
}

void stopSilnik() {
  jedzie_w_gore = false;
  jedzie_w_dol = false;
  pwmValue = 0;
  // trybSET = false; //Zakomentowano ze względ na 
digitalWrite(enablePin, LOW);
  ledcWrite(turnLeftPin, 0);
  ledcWrite(turnRightPin, 0);

  digitalWrite(PIN_SSR_PLUS, LOW);
  digitalWrite(PIN_SSR_MINUS, LOW);
  digitalWrite(PIN_SSR_PLUS_2, LOW);
}

int pobierzPWM() {
  if (pwmValue < pwmMax) {
    pwmValue += pwmStep;
    if (pwmValue > pwmMax) pwmValue = pwmMax;
  }
  return (int)pwmValue;
}

bool zmianaKierunku(bool chceWGore, bool chceWDol) {
  if (jedzie_w_gore && chceWDol) return true;
  if (jedzie_w_dol && chceWGore) return true;
  return false;
}

void zamykanie_po_czasie() {

  if (!trybSET) {
    autoZamykanieAktywne = false;
    return;
  }

  // warunek: brama stoi na krańcówce dolnej
  // (jeśli to jednak ma być górna – zamień na krGorna)
  if (krDolna && !jedzie_w_gore && !jedzie_w_dol) {

    if (!autoZamykanieAktywne) {
      czasStartAutoZamykania = millis();
      autoZamykanieAktywne = true;
    }

    if (millis() - czasStartAutoZamykania >= czasAutoZamykania) {

      // Start jazdy w dół (jak tryb SET)
      jedzie_w_dol = true;
      jedzie_w_gore = false;
      startCzasJazdy = millis();
      pwmValue = 0;
      trybSET = true;

      autoZamykanieAktywne = false;
    }

  } else {
    // jeśli brama się ruszyła lub zeszła z krańcówki – reset timera
    autoZamykanieAktywne = false;
  }
}

void jazda() {

  bool momentaryUp = BUTTON_UP_MOMENTARY_PIN_wcisniety || PILOT_UP_PIN_A_MOMENTARY_wcisniety;
  bool momentaryDown = BUTTON_DOWN_MOMENTARY_PIN_wcisniety || PILOT_DOWN_PIN_B_MOMENTARY_wcisniety;
  bool setUp = BUTTON_UP_SET_PIN_wcisniety || PILOT_UP_Bi_SET_PIN_wcisniety;
  bool setDown = BUTTON_DOWN_SET_PIN_wcisniety 
            || PILOT_DOWN_Ai_SET_PIN_wcisniety
            || autoSetDown;

  bool chceWGore = momentaryUp || setUp;
  bool chceWDol = momentaryDown || setDown;

  if (chceWGore || chceWDol) autoStop = false;

  

  // =====================
  // ZMIANA KIERUNKU
  // =====================
  if (zmianaKierunku(chceWGore, chceWDol)) {
    stopSilnik();
    wDeadTime = true;
    czasZmianyKierunku = millis();
    return;
  }

  // =====================
  // DEAD TIME
  // =====================
  if (wDeadTime) {
    if (millis() - czasZmianyKierunku < deadTime) return;
    wDeadTime = false;
  }

  if (momentaryUp && !krGorna) {
    
    trybSET = false;
    pwmValue = pwmMax;
    wlaczSSR();
    jedzie_w_gore = true;
    jedzie_w_dol = false;
    ledcWrite(turnLeftPin, pwmMax);
    ledcWrite(turnRightPin, 0);
    return;
  }

  if (momentaryDown && !krDolna) {
    trybSET = false;
    pwmValue = pwmMax;
    wlaczSSR();
    jedzie_w_dol = true;
    jedzie_w_gore = false;
    ledcWrite(turnLeftPin, 0);
    ledcWrite(turnRightPin, pwmMax);
    return;
  }

  // =====================
  // START TRYBU SET (STAN)
  // =====================
  if (!trybSET) {
    if (setUp && !krGorna) {
      trybSET = true;
      jedzie_w_gore = true;
      jedzie_w_dol = false;
      startCzasJazdy = millis();
    }

    else if (setDown && !krDolna) {
      autoSetDown = false;   // <-- DODAJ
      trybSET = true;
      jedzie_w_dol = true;
      jedzie_w_gore = false;
      startCzasJazdy = millis();
    }
  }

  if (trybSET) {
    if ((jedzie_w_gore && (krGorna || millis() - startCzasJazdy > czasOtwierania)) || (jedzie_w_dol && (krDolna || millis() - startCzasJazdy > czasZamykania))) {
      autoStop = true;
      stopSilnik();
      trybSET = false;
      return;
    }


    if ((jedzie_w_dol && (krDolna || millis() - startCzasJazdy > czasZamykania))) {
      autoStop = true;
      stopSilnik();
      trybSET = false;
      return;
    }


    int pwm = pobierzPWM();
    wlaczSSR();

    if (jedzie_w_gore) {
      ledcWrite(turnLeftPin, pwm);
      ledcWrite(turnRightPin, 0);
    }
    if (jedzie_w_dol) {
      ledcWrite(turnLeftPin, 0);
      ledcWrite(turnRightPin, pwm);
    }
    if (!jedzie_w_dol && !jedzie_w_gore) {
      trybSET = false;
      stopSilnik();
    }

    return;
  }
  stopSilnik();
}

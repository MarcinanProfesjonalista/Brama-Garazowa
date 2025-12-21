#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int what_is_displayed = 1; // 1 = status

void init_oled_screen() {

  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  display.clearDisplay();
  display.display();
}


const char* menu_items[] = {
  "Status"  //,  //1
};

String pobierzStanDrzwi(
  bool momentaryUp,
  bool momentaryDown,
  bool trybSET,
  bool jedzieWGore,
  bool jedzieWDol,
  bool awaria,
  bool autoStop
) {
  if (momentaryUp) return "OTWIERANIE";
  if (momentaryDown) return "ZAMYKANIE";

  if (trybSET && jedzieWGore) return "AUTO OTWIERANIE";
  if (trybSET && jedzieWDol)  return "AUTO ZAMYKANIE";

  if (awaria) return "AWARIA";
  if (autoStop) return "AUTO STOI";

  return "STOI";
}

void wyswietl_status_oled(
    bool jedzieWGore,
    bool jedzieWDol,
    bool trybSET,
    bool krGorna,
    bool krDolna,
    bool ssrOn,
    unsigned long czasDoKonca,
    bool momentaryUp,
    bool momentaryDown,
    bool awaria,
    bool autoStop
) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  // -------------------------
  // 1. Nagłówek
  // -------------------------
  display.setCursor(0, 0);
  display.print("STAN DRZWI");

  // Krańcówki w prawym górnym rogu
  display.setCursor(100, 0);
  display.print(krGorna ? "--" : "/\\");
  display.setCursor(100, 10);
  display.print(krDolna ? "__" : "\\/");

  // -------------------------
  // 2. Stan drzwi
  // -------------------------
  display.setCursor(0, 15);
  display.print(pobierzStanDrzwi(
    momentaryUp,
    momentaryDown,
    trybSET,
    jedzieWGore,
    jedzieWDol,
    awaria,
    autoStop
  ));

  // -------------------------
  // 3. SSR
  // -------------------------
  display.setCursor(0, 30);
  display.print("SSR: ");
  display.print(ssrOn ? "ON" : "OFF");

  // -------------------------
  // 4. Czas do końca
  // -------------------------
  display.setCursor(0, 40);
  display.print("SEC TO END: ");
  display.print(czasDoKonca);

  // -------------------------
  // 5. Dolny pasek przycisków
  // -------------------------
  display.setCursor(0, 55);
  display.print("UP:");
  display.print(momentaryUp ? "1 " : "0 ");

  display.print("DOWN:");
  display.print(momentaryDown ? "1 " : "0 ");

  display.print("UP_SET:");
  display.print(BUTTON_UP_SET_PIN_wcisniety ? "1 " : "0 ");

  display.print("DOWN_SET:");
  display.print(BUTTON_DOWN_SET_PIN_wcisniety ? "1" : "0");

  display.display();
}


void obsluga_wyswietlania() {
  bool momentaryUp =
    BUTTON_UP_MOMENTARY_PIN_wcisniety ||
    PILOT_UP_PIN_A_MOMENTARY_wcisniety;

  bool momentaryDown =
    BUTTON_DOWN_MOMENTARY_PIN_wcisniety ||
    PILOT_DOWN_PIN_B_MOMENTARY_wcisniety;

  wyswietl_status_oled(
    jedzie_w_gore,
    jedzie_w_dol,
    trybSET,
    krGorna,
    krDolna,
    (jedzie_w_gore || jedzie_w_dol),   // SSR ON gdy jedzie
    obliczSekundyDoKonca(),        // musisz mieć licznik czasu
    momentaryUp,
    momentaryDown,
    awaria,
    autoStop
  );
}


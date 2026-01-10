#include "esp_task_wdt.h"

#include "zmienne_globalne.h"
#include "wejscia_wyjscia.h"
#include "funkcja_ruchu.h"
#include "ekran_oled.h"

// =====================
// WATCHDOG
// =====================
esp_task_wdt_config_t wdt_config = {
  .timeout_ms = 200,
  .idle_core_mask = 1,   // Core 0
  .trigger_panic = true
};




void setup() {
  Serial.begin(115200);

  init_wejscia_wyjscia();
  init_oled_screen();

  esp_task_wdt_init(&wdt_config);
  esp_task_wdt_add(NULL);
}

void loop() {

  esp_task_wdt_reset();

  // 1. Odczyt wejść
  obsluz_przyciski();
  monitoruj_krancowki();
  zamykanie_po_czasie();

  // 2. Logika ruchu
  jazda();
  

  // 3. UI
  obsluga_wyswietlania();
}

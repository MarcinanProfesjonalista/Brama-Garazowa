<p align="center">
  <img
    src="https://raw.githubusercontent.com/MarcinanProfesjonalista/Brama-Garazowa/main/brama%20garazowa/plyta%201.7.png"
    alt="Płyta sterownika v1.7"
    width="600">
</p>
# 🚪 Automat Bramy Garażowej – System Sterowania

Nowoczesny sterownik do automatyzacji bramy garażowej oparty o mikrokontroler **ESP**, umożliwiający lokalne i bezprzewodowe sterowanie napędem prądu stałego.

---

# ✨ Główne funkcje

- 📶 Komunikacja **Wi-Fi**
- 📡 Komunikacja **Bluetooth**
- ⚡ Komunikacja **ESP-NOW**
- 🎮 Obsługa pilotów bezprzewodowych:
  - 433 MHz
  - 866 MHz
- 🖥️ Wyświetlanie bieżącego stanu urządzenia
- 🔒 Obsługa krańcówek
- ⏱️ Licznik czasu zamykania
- 🖐️ Niezależny tryb ręczny

---

# 📡 Specyfikacja komunikacji

Sterownik obsługuje kilka sposobów komunikacji:

| Technologia | Opis |
|-------------|------|
| Wi-Fi | Sterowanie przez sieć lokalną |
| Bluetooth | Lokalna komunikacja z urządzeniami mobilnymi |
| ESP-NOW | Szybka komunikacja pomiędzy urządzeniami ESP |
| RF 433 MHz | Obsługa pilotów bezprzewodowych |
| RF 866 MHz | Obsługa pilotów bezprzewodowych |

---

# 🕹️ Tryb ręczny

Sterownik posiada cztery przyciski umożliwiające pełną obsługę napędu bez użycia komunikacji radiowej.

> **Sterowanie ręczne ma najwyższy priorytet** i zawsze nadpisuje sterowanie bezprzewodowe.

| Przycisk | Funkcja |
|----------|---------|
| ⬆️ **UP** | Otwieranie bramy |
| ⬇️ **DOWN** | Zamykanie bramy |
| ⏫ **UP_T** | Otwieranie przez 120 sekund |
| ⏬ **BACK_T** | Zamykanie przez 120 sekund |

---

# 🖥️ Informacje wyświetlane na ekranie

Wyświetlacz prezentuje aktualny stan pracy urządzenia.

## Aktualny stan napędu

- 🟢 Stoi
- 🔄 Jedzie
- ⬆️ Otwieranie
- ⬇️ Zamykanie

## Dodatkowe informacje

- Stan krańcówek
- Licznik czasu zamykania
- Aktualny tryb pracy

---

# ⚙️ Parametry zasilania

Sterownik współpracuje z zasilaniem:

| Parametr | Wartość |
|----------|----------|
| Zasilanie sterownika | 24 VDC |
| Zasilacz | 230 VAC → 24 VDC |
| Typ silnika | Silnik prądu stałego (DC) |
| Zakres napięcia silnika | 5–50 VDC |
| Maksymalny prąd udarowy | 30 A |

> **Zalecane jest stosowanie zasilania transformatorowego do zasilania silnika.**

---

# 🔌 Wymagane elementy

Do poprawnej pracy urządzenia wymagane jest zastosowanie:

- Mostka H **BTS7960B**
- Zasilacza **230 VAC → 24 VDC**
- Napędu DC **5–50 V**

---

# 📋 Funkcje systemu

- ✅ Sterowanie lokalne
- ✅ Sterowanie bezprzewodowe
- ✅ Obsługa pilotów RF
- ✅ Obsługa krańcówek
- ✅ Sterowanie czasowe
- ✅ Wyświetlanie stanu urządzenia
- ✅ Licznik czasu zamykania
- ✅ Priorytet sterowania ręcznego

---

# ⚠️ Uwagi

- Sterowanie ręczne działa niezależnie od komunikacji radiowej.
- Wciśnięcie dowolnego przycisku lokalnego natychmiast przejmuje kontrolę nad urządzeniem.
- Do zasilania napędu należy stosować zasilanie transformatorowe.
- Sterownik przeznaczony jest do współpracy z silnikami DC o napięciu od **5 V do 50 V**.

---

# 📄 Licencja

Projekt przeznaczony do własnych zastosowań oraz dalszego rozwoju.

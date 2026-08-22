#include <TFT_eSPI.h>
#include <SPI.h>

#define BOARD_LILYGO_T_QT
// #define BOARD_ESP32_GENERIC

#if defined(BOARD_LILYGO_T_QT)
  const int BTN_LFT = 0;
  const int BTN_RGHT = 47;
#elif defined(BOARD_ESP32_GENERIC)
  const int BTN_LFT = 0;
  const int BTN_RGHT = 4;
#endif

const int DELAY = 700;
const int SECOND_DELAY = 500;
const int CONTACT_BOUNCE_DELAY = 50;

TFT_eSPI tft = TFT_eSPI();

bool checkDoubleClick(int pin) {
  delay(CONTACT_BOUNCE_DELAY);
  while (digitalRead(pin) == LOW);

  unsigned long startTime = millis();

  while (millis() - startTime < DELAY) {
    if (digitalRead(pin) == LOW) {
      return true;
    }
  }
  return false;
}

void setup(void) {
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);

  pinMode(BTN_LFT, INPUT_PULLUP);
  pinMode(BTN_RGHT, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(BTN_LFT) == LOW) {
    if (checkDoubleClick(BTN_LFT)) {
      tft.fillScreen(TFT_BLUE);
    } else {
      tft.fillScreen(TFT_BLACK);
    }
    delay(SECOND_DELAY);
  }

  if (digitalRead(BTN_RGHT) == LOW) {
    if (checkDoubleClick(BTN_RGHT)) {
      tft.fillScreen(TFT_GREEN);
    } else {
      tft.fillScreen(TFT_RED);
    }
    delay(SECOND_DELAY);
  }
}

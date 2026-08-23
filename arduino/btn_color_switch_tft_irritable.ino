#include <TFT_eSPI.h>
#include <SPI.h>

#define BOARD_LILYGO_T_QT
// #define BOARD_ESP32_GENERIC

#if defined(BOARD_LILYGO_T_QT)
  const int BTN_LFT = 0;
  const int BTN_RGHT = 47;
  const int BACKLIGHT_PIN = 10;
#elif defined(BOARD_ESP32_GENERIC)
  const int BTN_LFT = 0;
  const int BTN_RGHT = 4;
#endif

const int DELAY = 700;
const int SECOND_DELAY = 500;
const int CONTACT_BOUNCE_DELAY = 50;

TFT_eSPI tft = TFT_eSPI();

int clickCounter = 0;
bool isSeeded = false;

void handleFifthClick() {
  if (digitalRead(BACKLIGHT_PIN) == HIGH) {
    digitalWrite(BACKLIGHT_PIN, LOW);
  }

  tft.setRotation(2);
  tft.fillScreen(TFT_BLACK);
  uint16_t pastelRed = tft.color565(240, 110, 110);
  tft.setTextColor(pastelRed, TFT_BLACK);

  tft.setTextSize(1);
  tft.setTextDatum(TL_DATUM);

  int randomPhrase = random(3);

  if (randomPhrase == 0) {
    tft.drawString("Stop", 4, 15, 4);
    tft.drawString("bothering", 4, 50, 4);
    tft.drawString("me!", 4, 85, 4);
  }
  else if (randomPhrase == 1) {
    tft.drawString("Leave", 4, 15, 4);
    tft.drawString("me", 4, 50, 4);
    tft.drawString("alone!", 4, 85, 4);
  }
  else if (randomPhrase == 2) {
    tft.drawString("Get off", 4, 15, 4);
    tft.drawString("my", 4, 50, 4);
    tft.drawString("back!", 4, 85, 4);
  }
}

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
  int currentLightState = digitalRead(BACKLIGHT_PIN);
  // Seed the random number generator once using the user's first button press timing
  if (!isSeeded && (digitalRead(BTN_LFT) == LOW || digitalRead(BTN_RGHT) == LOW)) {
    randomSeed(millis());
    isSeeded = true;
  }

  if (digitalRead(BTN_LFT) == LOW) {
    clickCounter++;

    if (clickCounter % 5 == 0) {
      handleFifthClick();
      checkDoubleClick(BTN_LFT);
    } else {
      if (checkDoubleClick(BTN_LFT)) {
        if (currentLightState == LOW) {
          digitalWrite(BACKLIGHT_PIN, HIGH);
        }
        else {
          digitalWrite(BACKLIGHT_PIN, LOW);
        }
      } else {
        tft.fillScreen(TFT_BLACK);
      }
    }
    delay(SECOND_DELAY);
  }

  if (digitalRead(BTN_RGHT) == LOW) {
    clickCounter++;

    if (clickCounter % 5 == 0) {
      handleFifthClick();
      checkDoubleClick(BTN_RGHT);
    } else {
      if (checkDoubleClick(BTN_RGHT)) {
        tft.fillScreen(TFT_GREEN);
      } else {
        tft.fillScreen(TFT_RED);
      }
    }
    delay(SECOND_DELAY);
  }
}

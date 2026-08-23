#include <TFT_eSPI.h>
#include <SPI.h>
#include <OneButton.h>

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

const int CLICK_TICKS = 400;

TFT_eSPI tft = TFT_eSPI();

OneButton buttonLeft(BTN_LFT, true, true);
OneButton buttonRight(BTN_RGHT, true, true);

int clickCounter = 0;

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

void clickLeft() {
  clickCounter++;
  if (clickCounter % 5 == 0) {
    handleFifthClick();
  } else {
    tft.fillScreen(TFT_BLACK);
  }
}

void doubleClickLeft() {
  clickCounter++;
  if (clickCounter % 5 == 0) {
    handleFifthClick();
  } else {
    if (digitalRead(BACKLIGHT_PIN) == LOW) {
      digitalWrite(BACKLIGHT_PIN, HIGH);
    } else {
      digitalWrite(BACKLIGHT_PIN, LOW);
    }
  }
}

void clickRight() {
  clickCounter++;
  if (clickCounter % 5 == 0) {
    handleFifthClick();
  } else {
    tft.fillScreen(TFT_RED);
  }
}

void doubleClickRight() {
  clickCounter++;
  if (clickCounter % 5 == 0) {
    handleFifthClick();
  } else {
    tft.fillScreen(TFT_GREEN);
  }
}

void setup(void) {
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);

  buttonLeft.setClickTicks(CLICK_TICKS);
  buttonRight.setClickTicks(CLICK_TICKS);

  buttonLeft.attachClick(clickLeft);
  buttonLeft.attachDoubleClick(doubleClickLeft);

  buttonRight.attachClick(clickRight);
  buttonRight.attachDoubleClick(doubleClickRight);
}

void loop() {
  buttonLeft.tick();
  buttonRight.tick();
}

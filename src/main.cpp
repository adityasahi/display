#include <SPI.h>
#include "Adafruit_GFX.h"
#include "Adafruit_RA8875.h"
#include <SdFat.h>

#define RA8875_INT 3
#define RA8875_CS 10
#define RA8875_RESET 9

Adafruit_RA8875 tft = Adafruit_RA8875(RA8875_CS, RA8875_RESET);

SdFat sd;

uint16_t tx, ty;
int selectedOption = 0;
int maxOption = 3;
bool inSettings = false;
int brightness = 255;

void setup() {
  Serial.begin(9600);
  Serial.println("RA8875 start");

  /* Initialize the display */
  if (!tft.begin(RA8875_800x480)) {
    Serial.println("RA8875 Not Found!");
    while (1);
  }

  /* Initialize the SD card */
  if (!sd.begin(4)) {
    Serial.println("SD card initialization failed!");
    while (1);
  }

  tft.displayOn(true);
  tft.GPIOX(true);      // Enable TFT - display enable tied to GPIOX
  tft.PWM1config(true, RA8875_PWM_CLK_DIV1024); // PWM output for backlight
  tft.PWM1out(brightness);
  tft.fillScreen(RA8875_BLACK);

  /* Switch to text mode */
  tft.textMode();
  tft.cursorBlink(32);
}

void drawmenu() {
  tft.fillScreen(RA8875_BLACK);
  tft.textMode();
  tft.textSetCursor(10, 10);
  tft.textEnlarge(2);
  tft.textWrite("Menu:");

  tft.textEnlarge(1);
  tft.textSetCursor(10, 40);
  if (selectedOption == 0) {
    tft.textWrite(">");
  } else {
    tft.textWrite(" ");
  }
  tft.textWrite("Game Select");

  tft.textSetCursor(10, 60);
  if (selectedOption == 1) {
    tft.textWrite(">");
  } else {
    tft.textWrite(" ");
  }
  tft.textWrite("Demo");

  tft.textSetCursor(10, 80);
  if (selectedOption == 2) {
    tft.textWrite(">");
  } else {
    tft.textWrite(" ");
  }
  tft.textWrite("Settings");

  tft.textEnlarge(2);
}

void loop() {
  drawmenu();

  while (!Serial.available()); // Wait for user input
  int option = Serial.parseInt(); // Read user input

  if (inSettings) {
    if (option == 1) {
      brightness = min(255, brightness + 25);
      tft.PWM1out(brightness);
    } else if (option == 2) {
      brightness = max(0, brightness - 25);
      tft.PWM1out(brightness);
    } else if (option == 3) {
      inSettings = false;
    } else {
      Serial.println("Invalid option.");
    }
  } else {
    if (option == 1) {
      /* Load and draw bitmap from SD card */
      // tft.bmpDraw("bitmap.bmp", 0, 0);
    } else if (option == 2) {
      Serial.println("Demo selected");
    } else if (option == 3) {
      inSettings = true;
    } else {
      Serial.println("Invalid option.");
    }
  }

  // Update selectedOption based on user input
  if (option > 0 && option <= maxOption) {
    selectedOption = option - 1;
  }

  // Wait for user input to go back or forward in menu
  while (Serial.available()) Serial.read();
  while (!Serial.available()) {
    delay(50);
  }
  int input = Serial.read();
  if (input == 'b' && selectedOption > 0) {
    selectedOption--;
  } else if (input == 'f' && selectedOption < maxOption - 1) {
    selectedOption++;
  }
}
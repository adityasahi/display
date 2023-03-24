#include <SPI.h>
#include "Adafruit_GFX.h"
#include "Adafruit_RA8875.h"

#define RA8875_INT 3
#define RA8875_CS 10
#define RA8875_RESET 9

Adafruit_RA8875 tft = Adafruit_RA8875(RA8875_CS, RA8875_RESET);
uint16_t tx, ty;

int selectedOption = 0;
int maxOption = 4;
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

  tft.displayOn(true);
  tft.GPIOX(true);      // Enable TFT - display enable tied to GPIOX
  tft.PWM1config(true, RA8875_PWM_CLK_DIV1024); // PWM output for backlight
  tft.PWM1out(brightness);
  tft.fillScreen(RA8875_BLACK);
  
  tft.loadBitmap(0, 0, myBitmap, MY_BITMAP_WIDTH, MY_BITMAP_HEIGHT);
  tft.drawBitmap(100, 100, myBitmap, MY_BITMAP_WIDTH, MY_BITMAP_HEIGHT);

  /* Switch to text mode */
  tft.textMode();
  tft.cursorBlink(32);
}

void loop() {
  // Draw the bitmap
  tft.loadBitmap(0, 0, myBitmap, MY_BITMAP_WIDTH, MY_BITMAP_HEIGHT);
  tft.drawBitmap(0, 0, myBitmap, MY_BITMAP_WIDTH, MY_BITMAP_HEIGHT);

  
  Serial.println("Select an option:");
  Serial.println("1. Tetris");
  Serial.println("2. Pong");
  Serial.println("3. Flappy Bird");
  Serial.println("4. Settings");

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
      playTetris();
    } else if (option == 2) {
      playPong();
    } else if (option == 3) {
      playAnimations();
    } else if (option == 4) {
      inSettings = true;
    } else {
      Serial.println("Invalid option.");
    }
  }

  // Update selectedOption based on user input
  if (option > 0 && option <= maxOption) {
    selectedOption = option;
  }

  // Print menu options
  Serial.println();
  Serial.println("Menu:");
  Serial.print(selectedOption == 1 ? ">" : " ");
  Serial.println("Tetris");
  Serial.print(selectedOption == 2 ? ">" : " ");
  Serial.println("Pong");
  Serial.print(selectedOption == 3 ? ">" : " ");
  Serial.println("Flappy Bird");
  Serial.print(selectedOption == 4 ? ">" : " ");
  Serial.println("Settings");

  // Wait for user input to go back or forward in menu
  while (Serial.available()) Serial.read();
  while (!Serial.available()) {
    delay(50);
  }
  int input = Serial.read();
  if (input == 'b' && selectedOption > 1) {
    selectedOption--;
  } else if (input == 'f' && selectedOption < maxOption) {
    selectedOption++;
  }
}

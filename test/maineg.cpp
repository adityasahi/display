#include <SPI.h>
#include "Adafruit_GFX.h"
#include "Adafruit_RA8875.h"
#include <SD.h>
#include <Adafruit_ImageReader.h>


#define RA8875_INT 3
#define RA8875_CS 10
#define RA8875_RESET 9

Adafruit_RA8875 tft = Adafruit_RA8875(RA8875_CS, RA8875_RESET);

uint16_t tx, ty;
int menuIndex = 0; // current menu selection
int maxOption = 3;
bool inSettings = false;
int brightness = 255;
int selectedOption = 0;

void setup() {
  tft.begin(RA8875_800x480); // initialize the display
  tft.displayOn(true); // turn on the display
  tft.GPIOX(true); // enable the backlight
  tft.PWM1config(true, RA8875_PWM_CLK_DIV1024); // set the backlight brightness
  tft.PWM1out(255); // set the backlight brightness to maximum */
  tft.textMode();
  tft.cursorBlink(32);
}


void drawMenu() {
  tft.fillScreen(RA8875_BLACK); // clear the screen
  tft.textMode();
  tft.textSetCursor(200, 100); // set the cursor position
  tft.textColor(RA8875_WHITE,RA8875_BLACK); // set the text color to white
  tft.setTextSize(3); // set the text size to 3
 
  if (menuIndex == 0) {
    tft.textWrite("> Select Game\n"); // highlight selected option
    tft.textWrite("  Demo\n");
    tft.textWrite("  Settings\n");
  }
  else if (menuIndex == 1) {
    tft.textWrite("  Select Game\n");
    tft.textWrite("> Demo\n"); // highlight selected option
    tft.textWrite("  Settings\n");
  }
  else if (menuIndex == 2) {
    tft.textWrite("  Select Game\n");
    tft.textWrite("  Demo\n");
    tft.textWrite("> Settings\n"); // highlight selected option
  }
}


void handleInput() {
  if (digitalRead(0) == LOW) { // button A pressed
    menuIndex--;
    if (menuIndex < 0) {
      menuIndex = 2; // wrap around to end of menu
    }
  }
  else if (digitalRead(1) == LOW) { // button B pressed
    menuIndex++;
    if (menuIndex > 2) {
      menuIndex = 0; // wrap around to beginning of menu
    }
  }
  else if (digitalRead(2) == LOW) { // button C pressed
    // do something based on selected option
    if (menuIndex == 0) {
      // Select Game selected
      tft.fillScreen(RA8875_BLACK); // clear the screen
      tft.textMode();
      tft.textSetCursor(200, 100); // set the cursor position
      tft.textColor(RA8875_WHITE,RA8875_BLACK); // set the text color to white
      tft.setTextSize(3); // set the text size to 3
      tft.textWrite("Select Game"); // display selected option
      delay(1000); // wait for 1 second
      drawMenu(); // redraw menu
    }
    else if (menuIndex == 1) {
      // Demo selected
      tft.fillScreen(RA8875_BLACK); // clear the screen
      tft.textMode();
      tft.textSetCursor(200, 100); // set the cursor position
      tft.textColor(RA8875_WHITE,RA8875_BLACK); // set the text color to white
      tft.setTextSize(3); // set the text size to 3
      tft.textWrite("Demo"); // display selected option
      delay(1000); // wait for 1 second
      drawMenu(); // redraw menu
    }
    else if (menuIndex == 2) {
      // Settings selected
      tft.fillScreen(RA8875_BLACK); // clear the screen
      tft.textMode();
      tft.textSetCursor(200, 100); // set the cursor position
      tft.textColor(RA8875_WHITE,RA8875_BLACK); // set the text color to white
      tft.setTextSize(3); // set the text size to 3
      tft.textWrite("Settings"); // display selected option
      delay(1000); // wait for 1 second
      drawMenu(); // redraw menu
    }
  }
  else if (digitalRead(3) == LOW) { // button D pressed
    // do something else
  }
}


void loop() {
  drawMenu();
  // handleInput();
  delay(1000);
}
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_RA8875.h>

// Initialize the TFT screen
Adafruit_RA8875 tft = Adafruit_RA8875(RA8875_CS, RA8875_RESET);

// Define the menu options
const char* MAIN_MENU_OPTIONS[] = {
  "Select game",
  "Demo",
  "Settings"
};

const char* GAME_MENU_OPTIONS[] = {
  "Pong",
  "Tetris",
  "Flappy Bird"
};

// Keep track of the selected menu option
int selectedOption = 0;

// Keep track of the current menu
const char** currentMenu = MAIN_MENU_OPTIONS;
int currentMenuSize = sizeof(MAIN_MENU_OPTIONS) / sizeof(MAIN_MENU_OPTIONS[0]);

void setup() {
  // Start the SPI bus
  SPI.begin();

  // Initialize the TFT screen
  tft.begin(RA8875_800x480);

  // Set the background color to white
  tft.fillScreen(RA8875_WHITE);

  // Set the text color to black
  tft.setTextColor(RA8875_BLACK);

  // Set the text size to 2x
  tft.setTextSize(2);

  // Draw the main menu on the screen
  drawMenu();
}

void loop() {
  // Read the touch screen coordinates
  TS_Point touchPoint = tft.touchRead();

  // Check if the screen has been touched
  if (touchPoint.z > 0) {
    // Get the menu option that was touched
    int touchedOption = touchPoint.y / 50;

    // Check if the touched option is valid
    if (touchedOption >= 0 && touchedOption < currentMenuSize) {
      // Update the selected option
      selectedOption = touchedOption;

      // Check if the selected option is "Select game"
      if (strcmp(currentMenu[selectedOption], "Select game") == 0) {
        // Switch to the game menu
        currentMenu = GAME_MENU_OPTIONS;
        currentMenuSize = sizeof(GAME_MENU_OPTIONS) / sizeof(GAME_MENU_OPTIONS[0]);

        // Redraw the menu with the new options
        drawMenu();
      }
    }
  }
}

// Draw the current menu on the screen
void drawMenu() {
  // Clear the screen
  tft.fillScreen(RA8875_WHITE);

  // Set the text size to 2x
  tft.setTextSize(2);

  // Write each menu option on the screen
  for (int i = 0; i < currentMenuSize; i++) {
    tft.setCursor(100, 50 + i * 50);
    tft.print(currentMenu[i]);

    // Draw an arrow next to the selected option
    if (i == selectedOption) {
      tft.setCursor(60, 50 + i * 50);
      tft.print(">");
    }
  }
}

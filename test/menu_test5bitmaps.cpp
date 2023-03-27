#include <Adafruit_GFX.h>    // Core graphics library 
#include <SPI.h> 
#include <Wire.h> 
#include <SD.h> 
#include "Adafruit_RA8875.h" 
#include <Adafruit_STMPE610.h> 

#define sd_cs 6                          
#define RA8875_INT 3 
#define RA8875_CS 10 
#define RA8875_RESET 9  

Adafruit_RA8875 tft = Adafruit_RA8875(RA8875_CS, RA8875_RESET); 
Adafruit_STMPE610 ts = Adafruit_STMPE610(STMPE_CS); 

void setup () { 
  Serial.begin(9600); 

  if (!SD.begin(sd_cs)) { 
    Serial.println("initialization failed!"); 
    return; 
  } 

  Serial.println("initialization done."); 
  Serial.println("RA8875 start"); 

  if (!tft.begin(RA8875_800x480)) { 
    Serial.println("RA8875 Not Found!"); 
    while (1); 
  } 

  Serial.println("Found RA8875"); 

  tft.displayOn(true); 
  tft.GPIOX(true);      
  tft.PWM1config(true, RA8875_PWM_CLK_DIV1024); 
  tft.PWM1out(255); 

  Serial.print("("); 
  Serial.print(tft.width()); 
  Serial.print(", "); 
  Serial.print(tft.height()); 
  Serial.println(")"); 

  tft.graphicsMode();                 
  tft.fillScreen(RA8875_BLACK); 
  tft.graphicsMode(); 

  drawMenu(); // Draw the main menu 
} 

void loop() { 
  TS_Point p = ts.getPoint(); 

  if (p.z > ts.pressureThreshhold) { 
    int x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width()); 
    int y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height()); 

    if (x >= 0 && x < tft.width() && y >= 0 && y < tft.height()) { 
      handleTouch(x, y); 
    } 
  } 
} 

void drawMenu() { 
  tft.fillScreen(RA8875_BLACK); 

  tft.textMode(); 
  tft.textEnlarge(2); 

  tft.setCursor(100, 50); 
  tft.print("Select Game"); 

  tft.setCursor(100, 150); 
  tft.print("Settings"); 

  tft.setCursor(100, 250); 
  tft.print("Demo"); 
} 

void drawGameList() { 
  tft.fillScreen(RA8875_BLACK); 

  tft.textMode(); 
  tft.textEnlarge(2); 

  tft.setCursor(100, 50); 
  tft.print("Select a Game"); 

  tft.setCursor(100, 150); 
  tft.print("Pong"); 

  tft.setCursor(100, 200); 
  tft.print("Flappy Bird"); 

  tft.setCursor(100, 250); 
  tft.print("Tetris"); 
} 

void drawSettings() { 
  tft.fillScreen(RA8875_BLACK); 

  tft.textMode(); 
  tft.textEnlarge(2); 

  tft.setCursor(100, 50); 
  tft.print("Settings"); 

  tft.setCursor(100, 150); 
  tft.print("Internal Speaker Volume"); 

  tft.setCursor(100, 200); 
  tft.print("External Speaker Volume"); 

  tft.setCursor(100, 250); 
  tft.print("Back"); 
} 

void drawDemo() { 
  tft.fillScreen(RA8875_BLACK); 

  tft.textMode(); 
  tft.textEnlarge(2); 

  tft.setCursor(100, 50); 
  tft.print("Demo"); 

  tft.setCursor(100, 150); 
  tft.print("Coming Soon"); 

  tft.setCursor(100, 250); 
  tft.print("Back"); 
} 

void handleTouch(int x, int y) { 
  if (y >= 50 && y < 100) { // Select Game 
    drawGameList(); 
  } else if (y >= 150 && y < 200) {
    drawSettings();
  } else if (y >= 250 && y < 300) { // Demo
drawDemo();
}
}

void handleGameListTouch(int x, int y) {
if (y >= 150 && y < 175) { // Pong // Start Pong game } else if (y >= 200 && y < 225) { // Flappy Bird // Start Flappy Bird game } else if (y >= 250 && y < 275) { // Tetris // Start Tetris game } else if (y >= 300 && y < 350) { // Back
drawMenu();
}
}

void handleSettingsTouch(int x, int y) {
if (y >= 150 && y < 175) { // Internal Speaker Volume // Increase or decrease internal speaker volume } else if (y >= 200 && y < 225) { // External Speaker Volume // Increase or decrease external speaker volume } else if (y >= 250 && y < 300) { // Back
drawMenu();
}
}

void handleDemoTouch(int x, int y) {
if (y >= 250 && y < 300) { // Back
drawMenu();
}
}
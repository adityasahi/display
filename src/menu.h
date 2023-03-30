#ifndef MENU_H
#define MENU_H

#include "Arduino.h"

class MenuItem {
  public:
    MenuItem(const char* text, int x, int y, void (*callback)());
    const char* getText();
    int getX();
    int getY();
    void executeCallback();

  private:
    const char* _text;
    int _x;
    int _y;
    void (*_callback)();
};

void gameSelectCallback();
void demoCallback();
void settingsCallback();
void audioCallback();

MenuItem gameSelect("Game Select", 50, 100, gameSelectCallback);
MenuItem demo("Demo", 50, 150, demoCallback);
MenuItem settings("Settings", 50, 200, settingsCallback);
MenuItem audio("Audio", 50, 250, audioCallback);

#endif
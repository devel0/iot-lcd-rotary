---
title: include/lcd-rotary-menu.h


---

# include/lcd-rotary-menu.h








## Classes

|                | Name           |
| -------------- | -------------- |
| struct | **[LCDRotaryMenuOptions](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/struct_l_c_d_rotary_menu_options.md)**  |
| class | **[LCDRotaryMenu](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu.md)** <br>LCD Rotary Menu.  |
















## Source code

```cpp
#ifndef _LCD_ROTARY_MENU_H
#define _LCD_ROTARY_MENU_H

#ifdef ARDUINO

#include <Arduino.h>

#include <LiquidCrystal_I2C.h>

#include <debounced-button.h>
#include <debounced-rotary.h>
#include "lcd-rotary-menuitem.h"

struct LCDRotaryMenuOptions
{
    char subMenuPostChar;

    const char *backString;
};

class LCDRotaryMenu
{
    friend class LCDRotaryMenuItem;

    int cols;
    int rows;

    LiquidCrystal_I2C *lcd;
    DebouncedButton *btn;
    DebouncedRotary *rotary;

    void (*splCb)(LiquidCrystal_I2C &lcd);
    uint32_t splTimeoutMs;

    uint32_t menuBeginTimestamp;
    bool splashDisplayed;

    int rotAPin;
    int rotBPin;
    int rotSWPin;

    LCDRotaryMenuItem *root;
    LCDRotaryMenuItem *selectedItem;
    bool invalidated;

    char **rowsBuf;
    char **rowsBuf2;
    short customLineRow;
    short customLineRow2;

    LCDRotaryMenuItemCB defaultCb = NULL;

    LCDRotaryMenuItem **displayedMenuItems;

    void (*btnCb)() = NULL;
    void (*rotCb)() = NULL;

    bool busyMode = false;

    LCDRotaryMenuItem *editOn = NULL;
    int editOnRow = 0;

protected:
    void displayMenu();
    bool move(int diff);

public:
    LCDRotaryMenu(int addr, int cols, int rows, int rotAPin, int rotBPin, int rotSWPin, bool inverted = false,
                  int btnDebounceMs = 50, int abDebounceUs = 1500);
    ~LCDRotaryMenu();

    void invalidate();

    LCDRotaryMenuOptions options;

    void setSplashCb(void (*splCb)(LiquidCrystal_I2C &lcd), uint32_t timeoutMs);

    void setDefaultCb(LCDRotaryMenuItemCB cb);

    void setButtonCb(void (*cb)());

    void setRotCb(void (*cb)());

    void init();
    void loop();

    LCDRotaryMenuItem &getRoot();

    LCDRotaryMenuItem *getSelected();

    void setSelected(LCDRotaryMenuItem &item);

    void setCustomLine(const char *customLine, short rowIdx);
    void setCustomLine2(const char *customLine2, short rowIdx);
    void unsetCustomLine();

    LiquidCrystal_I2C &getLCD();

    void setBusyLine(const char *busyLine, short rowIdx);
    void unsetBusy();
};

#endif

#endif
```


-------------------------------



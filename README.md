# iot-lcd-rotary

<!-- TOC -->
* [Description](#description)
* [API](#api)
* [Quickstart](#quickstart)
* [Examples](#examples)
  + [lcd rotary menu](#lcd-rotary-menu)
  + [lcd rotary menu with tags](#lcd-rotary-menu-with-tags)
* [Debugging](#debugging)
* [How this project was built](#how-this-project-was-built)
<!-- TOCEND -->

<hr/>

## Description

LCD Rotary Menu for ststm32 platforms with arduino framework.

## API

- [classes](data/api/index_classes.md)
- lcd rotary menu (arduino)
    - [lcd-rotary-menu](data/api/Files/lcd-rotary-menu_8h.md#lcd-rotary-menu.h)
    - [lcd-rotary-menuitem](data/api/Files/lcd-rotary-menuitem_8h.md#lcd-rotary-menuitem.h)
    - [debounced-button](data/api/Files/debounced-button_8h.md#debounced-button.h)
    - [debounced-rotary](data/api/Files/debounced-rotary_8h.md#debounced-rotary.h)

## Quickstart

Install using vscode command palette `PlatformIO: New Terminal` referring to [platformio registry](https://platformio.org/lib/show/12375/iot-lcd-rotary) cli mode doc.

**dependencies**

```
lib_deps = 
	marcoschwartz/LiquidCrystal_I2C@^1.1.4
	devel0/iot-utils@^2.9.0
```

## Examples

### lcd rotary menu

```cpp
#include <lcd-rotary-menu.h>
#include <lcd-rotary-menuitem.h>

#include <sys-debug.h>

// rotary menu example

LCDRotaryMenu *menu;

// check i2c lcd address using i2c scanner
#define LCD_ADDR 0x27
#define LCD_COLS 20
#define LCD_ROWS 4

// PB2
#define ROT_A_PIN 40

// PB1
#define ROT_B_PIN 41

// PA10
#define ROT_SW_PIN 2

#define SPLASH_TIMEOUT_MS 1000

void LCDSplash(LiquidCrystal_I2C &lcd)
{
    lcd.setCursor(0, 0);
    lcd.print("firmware");
    lcd.setCursor(0, 1);
    lcd.print("version");
}

void reboot()
{
    debug("would to reboot...");
}

void setup()
{
    Serial.begin(9600);
    setSystemPrinter(Serial); // for debug and error notice

    auto inverted = false;

    menu = new LCDRotaryMenu(LCD_ADDR, LCD_COLS, LCD_ROWS, ROT_A_PIN, ROT_B_PIN, ROT_SW_PIN,
                             inverted, 200);

    // splash screen ( custom lcd usage ) ; call this before menu init
    menu->setSplashCb(LCDSplash, SPLASH_TIMEOUT_MS);

    menu->init();

    // compose follow menu
    //
    // sample1
    // Mode : TYPE1 | TYPE2
    // VAR A : 05000
    // VAR B :  +030
    // VAR C :   -12.3
    // dev---+
    //       reboot
    //       test

    auto &root = menu->getRoot();

    root.append("sample1");
    {
        auto &multi = root.append("Mode : ", "");
        multi.setMode(LCDRotaryMenuItemModeEnum::MI_MultiSelect);

        auto &typ1 = multi.append("TYPE 1");
        auto &typ2 = multi.append("TYPE 2");

        multi.setSelectedChild(&typ1);
    }

    {
        auto &input = root.append("VAR A : ", "05000");
        input.setMode(LCDRotaryMenuItemModeEnum::MI_NumericInput);
    }
    {
        auto &input = root.append("VAR B :  ", "+030");
        input.setMode(LCDRotaryMenuItemModeEnum::MI_NumericInput);
    }
    {
        auto &input = root.append("VAR C :   ", "-12.3");
        input.setMode(LCDRotaryMenuItemModeEnum::MI_NumericInput);
    }

    auto &dev = root.append("dev");

    dev.append("reboot").onSelect(reboot);
    dev.append("test1");
}

void loop()
{
    menu->loop();
}
```

### lcd rotary menu with tags

[see example03](examples/example03/example03.cpp) and [example04](examples/example04/example04/cpp) with defaultCb.

## Debugging

- [other references/troubleshoot](https://github.com/devel0/knowledge/blob/dece8a75990345c11f6062b782cb9a5d1bccd52a/doc/platformio-troubleshoot.md)

## How this project was built

References:
- [Creating Library](https://docs.platformio.org/en/latest/librarymanager/creating.html?utm_medium=piohome&utm_source=platformio)
- [library.json](https://docs.platformio.org/en/latest/librarymanager/config.html)

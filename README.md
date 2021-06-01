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

LCD Rotary Menu for ststm32 platform, mbed os framework.

## API

- [classes](data/api/index_classes.md)
- lcd rotary menu (arduino)
    - [lcd-rotary-menu](data/api/Files/lcd-rotary-menu_8h.md#lcd-rotary-menu.h)
    - [lcd-rotary-menuitem](data/api/Files/lcd-rotary-menuitem_8h.md#lcd-rotary-menuitem.h)
    - [debounced-button](data/api/Files/debounced-button_8h.md#debounced-button.h)
    - [debounced-rotary](data/api/Files/debounced-rotary_8h.md#debounced-rotary.h)

## Quickstart

Install using vscode command palette `PlatformIO: New Terminal` referring to [platformio registry](https://platformio.org/lib/show/12375/iot-lcd-rotary) cli mode doc.

## Examples

### lcd rotary menu

```cpp
#include <lcd-rotary-menu.h>
#include <lcd-rotary-menuitem.h>

#include <sys-debug.h>

// rotary menu example

LCDRotaryMenu *menu;

// check i2c lcd address using i2c scanner
#define LCD_ADDR 0x3F
#define LCD_COLS 16
#define LCD_ROWS 2

#define ROT_A_PIN 40
#define ROT_B_PIN 41
#define ROT_SW_PIN 45

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

    auto inverted = false; // set to true if want to invert cw/ccw behavior

    menu = new LCDRotaryMenu(LCD_ADDR, LCD_COLS, LCD_ROWS, ROT_A_PIN, ROT_B_PIN, ROT_SW_PIN, inverted);

    // splash screen ( custom lcd usage ) ; call this before menu init
    menu->setSplashCb(LCDSplash, SPLASH_TIMEOUT_MS);

    menu->init();

    // compose follow menu
    //
    // sample1
    // sample2
    // dev---+
    //       reboot
    //       test

    auto &root = menu->getRoot();

    root.append("sample1");
    root.append("sample2");

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

to debug examples/example01.cpp (included through [src/debug-main.cpp](src/debug-main.cpp)) it may needed to select only 1 platform from `platformio.ini` so the launch.json will generate accordingly; todo that comment others platform, ie:

```
[env]
src_filter = +<*> -<.git/> -<.svn/> -<example/> -<examples/> -<test/> -<tests/>

; [platformio]
; default_envs = nucleo_f446re, nucleo_f767zi

[env:nucleo_f767zi]
platform = ststm32
board = nucleo_f767zi
framework = mbed
test_build_project_src = true
debug_build_flags = -O0 -g -ggdb

; [env:nucleo_f446re]
; platform = ststm32
; board = nucleo_f446re
; framework = mbed
; test_build_project_src = true
; debug_build_flags = -O0 -g -ggdb
```

- [other references/troubleshoot](https://github.com/devel0/iot-stm32-ledblink-interrupt-debug#iot-stm32-ledblink-interrupt-debug)

## How this project was built

References:
- [Creating Library](https://docs.platformio.org/en/latest/librarymanager/creating.html?utm_medium=piohome&utm_source=platformio)
- [library.json](https://docs.platformio.org/en/latest/librarymanager/config.html)

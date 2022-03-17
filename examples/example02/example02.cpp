#ifndef UNIT_TEST

#ifdef ARDUINO

#include <lcd-rotary-menu.h>
#include <lcd-rotary-menuitem.h>

#include <sys-debug.h>

// rotary menu example

LCDRotaryMenu *menu;

// check i2c lcd address using i2c scanner
#define LCD_ADDR 0x27
#define LCD_COLS 20
#define LCD_ROWS 4

// PB5
#define ROT_A_PIN 4

// PB3
#define ROT_B_PIN 3

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

    auto inverted = true;

    menu = new LCDRotaryMenu(LCD_ADDR, LCD_COLS, LCD_ROWS, ROT_A_PIN, ROT_B_PIN, ROT_SW_PIN, 
        inverted, 200);

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

    auto &input = root.append("00000");
    input.setMode(LCDRotaryMenuItemModeEnum::MI_NumericInput);

    auto &dev = root.append("dev");

    dev.append("reboot").onSelect(reboot);
    dev.append("test1");
}

void loop()
{
    menu->loop();
}

#endif

#endif
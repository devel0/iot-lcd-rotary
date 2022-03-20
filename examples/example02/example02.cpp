#ifndef UNIT_TEST

#ifdef ARDUINO

#include <lcd-rotary-menu.h>
#include <lcd-rotary-menuitem.h>

#include <sys-debug.h>
#include <string-utils.h>

// rotary menu example

LCDRotaryMenu *menu;

enum MenuTagEnum
{
    Mode_Type,
    Mode_Type1,
    Mode_Type2,
    Mode_Type3,

    Var_A,
    Var_B,
    Var_C,
};

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

bool reboot(LCDRotaryMenuItem& item)
{
    debug("would to reboot...");

    return true;
}

bool multiSelected(LCDRotaryMenuItem &item)
{
    auto handled = false;

    switch (item.getTag())
    {
    case Mode_Type:
    {
        debug("selected mode tag=%d\n", item.getSelectedChild()->getTag());

        handled = true;
    }
    break;
    }

    return handled;
}

bool editEnd(LCDRotaryMenuItem &item)
{
    auto handled = false;

    if (item.getMode() == LCDRotaryMenuItemModeEnum::MI_NumericInput)
    {
        auto str = item.getText().c_str();
        auto val = atof(str);

        debug("var tag=%d changed to %s\n", item.getTag(), tostr(val, 1).c_str());

        handled = true;
    }

    return handled;
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
    // Mode : TYPE1 | TYPE2 | TYPE3
    // VAR A : 05000
    // VAR B :  +030
    // VAR C :   -12.3
    // dev---+
    //       reboot
    //       test

    menu->onMultiSelect(multiSelected);

    menu->onEditEnd(editEnd);

    auto &root = menu->getRoot();

    root.append("sample1");
    {
        auto &multi = root.append("Mode : ", "", MenuTagEnum::Mode_Type);
        multi.setMode(LCDRotaryMenuItemModeEnum::MI_MultiSelect);
        multi.setMultiRollOver(false);

        auto &typ1 = multi.append("TYPE 1", MenuTagEnum::Mode_Type1);
        auto &typ2 = multi.append("TYPE 2", MenuTagEnum::Mode_Type2);
        auto &typ3 = multi.append("TYPE 3", MenuTagEnum::Mode_Type3);

        multi.setSelectedChild(&typ1);
    }

    {
        auto &input = root.append("VAR A : ", "05000", MenuTagEnum::Var_A);
        input.setMode(LCDRotaryMenuItemModeEnum::MI_NumericInput);
    }
    {
        auto &input = root.append("VAR B :  ", "+030", MenuTagEnum::Var_B);
        input.setMode(LCDRotaryMenuItemModeEnum::MI_NumericInput);
    }
    {
        auto &input = root.append("VAR C :   ", "-12.3", MenuTagEnum::Var_C);
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

#endif

#endif
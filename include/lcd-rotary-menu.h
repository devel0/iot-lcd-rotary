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
    /**
     * @brief if not space then the char is appended at end of menu text to inform the user that the selected item is a submenu item
     *
     */
    char subMenuPostChar;

    /**
     * @brief text string for back menu label ( usually .. )
     */
    const char *backString;
};

/**
 * @brief LCD Rotary Menu
 *
 * nfo
 *
 */
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

    LCDRotaryMenuItemCB multiSelectCb = NULL;

    LCDRotaryMenuItemCB editEndCb = NULL;

    LCDRotaryMenuItemCB backPressedCb = NULL;

    /**
     * @brief for purpose of isDisplayed() fn
     */
    LCDRotaryMenuItem **displayedMenuItems;

    void (*btnCb)() = NULL;
    void (*rotCb)() = NULL;

    bool busyMode = false;

    LCDRotaryMenuItem *editOn = NULL;
    int editOnRow = 0;
    uint32_t m_inhibit = 0UL;
    uint32_t inhibit_on = 0UL;

    int lastPressCount = 0;
    int lastRotPos = 0;

    static const uint8_t editChar = 232 + 3;
    static const uint8_t editRowChar = '=';

protected:
    void displayMenu();
    /**
     * @brief move into menu for given diff pos ; return false if at end of menu
     */
    bool move(int diff);

public:
    /**
     * @brief Construct a new LCDRotaryMenu object
     *
     * @param addr i2c lcd address
     * @param cols nr. of lcd columns
     * @param rows nr. of lcd rows
     * @param rotAPin pin of rotary encoder A
     * @param rotBPin pin of rotary encoder B
     * @param rotSWPin pin of rotary encoder switch
     * @param inverted if true cw/ccw generates decrement/increment in position
     * @param btnDebounceMs debounce(ms) for rotary switch
     * @param btnDebounceMs debounce(us) for rotary A, B
     */
    LCDRotaryMenu(int addr, int cols, int rows, int rotAPin, int rotBPin, int rotSWPin, bool inverted = false,
                  int btnDebounceMs = 50, int abDebounceUs = 1500);
    ~LCDRotaryMenu();

    /**
     * @brief force menu redraw, for use within programmatic menu manipulation not tie within callbacks
     */
    void invalidate();

    LCDRotaryMenuOptions options;

    /**
     * @brief Set splash callback before Init
     *
     * @param splCb callback here you can directly used lcd ( clear, setCursor, print )
     * @param timeoutMs time after which menu display
     */
    void setSplashCb(void (*splCb)(LiquidCrystal_I2C &lcd), uint32_t timeoutMs);

    /**
     * @brief set default callback when select menuitem that has no custom callback
     */
    void setDefaultCb(LCDRotaryMenuItemCB cb);

    /**
     * @brief set callback on select this item (multi select mode)
     */
    void onMultiSelect(LCDRotaryMenuItemCB cb);

    /**
     * @brief set callback when edit mode ended
     */
    void onEditEnd(LCDRotaryMenuItemCB cb);

    /**
     * @brief set callback that will be called everytime button switch ; it's called before any specific onSelect callback
     *
     * @param cb
     */
    void setButtonCb(void (*cb)());

    /**
     * @brief set callback when press on .. ( parent ) ; parent menu can be retrived using callbacak argument getParent()
     */
    void setBackPressedCb(LCDRotaryMenuItemCB cb);

    /**
     * @brief set callback that will be called everytime rotary move to different menu item
     */
    void setRotCb(void (*cb)());

    void init();
    void loop();

    LCDRotaryMenuItem &getRoot();

    /**
     * @brief retrieve currently selected menu
     */
    LCDRotaryMenuItem *getSelected();

    void setSelected(LCDRotaryMenuItem &item, bool scrollTo = false, int customScrollRowPos = -1);

    void setCustomLine(const char *customLine, short rowIdx);
    void setCustomLine2(const char *customLine2, short rowIdx);
    void unsetCustomLine();

    void inhibit(uint32_t timeout_ms);

    /**
     * @brief retrieve lcd pointer ( advanced )
     */
    LiquidCrystal_I2C &getLCD();

    void setBusyLine(const char *busyLine, short rowIdx);
    void unsetBusy();
};

#endif

#endif
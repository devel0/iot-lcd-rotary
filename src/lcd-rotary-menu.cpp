#ifdef ARDUINO

#include "lcd-rotary-menu.h"

#include "lcd-rotary-menuitem.h"
#include "sys-debug.h"

#include <vector>

using namespace std;

LCDRotaryMenu::LCDRotaryMenu(int addr, int cols, int rows, int rotAPin, int rotBPin, int rotSWPin, bool inverted,
                             int btnDebounceMs, int abDebounceUs)
{
    this->cols = cols;
    this->rows = rows;
    lcd = new LiquidCrystal_I2C(addr, cols, rows);
    btn = new DebouncedButton(rotSWPin, btnDebounceMs);
    rotary = new DebouncedRotary(rotAPin, rotBPin, abDebounceUs);
    rotary->setInverted(inverted);

    root = new LCDRotaryMenuItem(*this, NULL);
    selectedItem = NULL;
    invalidated = true;
    displayedMenuItems = new LCDRotaryMenuItem *[rows];
    for (int i = 0; i < rows; ++i)
        displayedMenuItems[i] = NULL;

    options.subMenuPostChar = '>';
    options.backString = "..";

    customLineRow = -1;
    customLineRow2 = -1;
    rowsBuf = new char *[rows];
    rowsBuf2 = new char *[rows];
    for (int r = 0; r < rows; ++r)
    {
        rowsBuf[r] = new char[cols];
        rowsBuf2[r] = new char[cols];

        rowsBuf[r][0] = 0;
        rowsBuf2[r][0] = 0;
    }

    lcd->clear();
}

LCDRotaryMenu::~LCDRotaryMenu()
{
    for (int r = 0; r < rows; ++r)
    {
        delete rowsBuf2[r];
        delete rowsBuf[r];
    }
    delete rowsBuf;
    delete rowsBuf2;

    delete displayedMenuItems;
    delete root;

    delete rotary;
    delete btn;
    delete lcd;
}

void LCDRotaryMenu::displayMenu()
{
    if (!invalidated)
        return;

    LCDRotaryMenuItem *parent = (selectedItem == NULL || selectedItem->parent == NULL) ? root : selectedItem->parent;

    vector<LCDRotaryMenuItem *> &menuItems = parent->children;

    auto menuItemsSize = menuItems.size();

    if (menuItemsSize == 0)
        return;

    if (selectedItem == NULL)
        selectedItem = *menuItems.begin();

    int selectedItemIndex = -1;
    for (int i = 0; i < menuItemsSize; ++i)
    {
        if (menuItems[i] == selectedItem)
        {
            selectedItemIndex = i;
            break;
        }
    }
    if (selectedItemIndex == -1)
        error("menuitem idx not found");

    int customLineCount = customLineRow != -1 ? 1 : 0;
    if (customLineRow2 != -1)
        ++customLineCount;

    for (int r = 0; r < rows; ++r)
    {
        displayedMenuItems[r] = NULL;

        if (r == customLineRow || r == customLineRow2)
        {
            int l = strlen(rowsBuf[r]);
            int l2 = strlen(rowsBuf[r]);
            if (l != l2 || strncmp(rowsBuf[r], rowsBuf2[r], l) != 0)
            {
                strncpy(rowsBuf2[r], rowsBuf[r], l + 1);

                for (int j = l; j < cols; ++j)
                    rowsBuf[r][j] = ' ';
                rowsBuf[r][cols] = 0;

                lcd->setCursor(0, r);
                lcd->print(rowsBuf[r]);
            }
        }
        else
        {
            rowsBuf2[r][0] = 0;
            int l2 = 0;

            if (parent->scrollRowPos + r >= menuItemsSize + customLineCount)
            {
                rowsBuf2[r][0] = ' ';
                rowsBuf2[r][1] = 0;
                l2 = 1;
            }
            else
            {

                auto item = menuItems[parent->scrollRowPos + r - (r >= customLineRow ? customLineCount : 0)];
                if (item == selectedItem)
                {
                    rowsBuf2[r][0] = item->isBack ? '<' : '>';
                    rowsBuf2[r][1] = 0;
                }
                else
                {
                    rowsBuf2[r][0] = ' ';
                    rowsBuf2[r][1] = 0;
                }

                displayedMenuItems[r] = item;

                strncat(rowsBuf2[r], item->getText().c_str(), cols - 1);

                l2 = strlen(rowsBuf2[r]);

                if (item->children.size() > 0 && options.subMenuPostChar != ' ')
                {
                    if (l2 >= cols)
                        rowsBuf2[r][cols - 1] = options.subMenuPostChar;
                    else
                    {
                        rowsBuf2[r][l2] = options.subMenuPostChar;
                        rowsBuf[r][l2] = 0;
                        ++l2;
                    };
                }
            }
            lcd->setCursor(0, r);
            lcd->print(rowsBuf2[r][0]);

            int l = strlen(rowsBuf[r]);

            if (l2 > 0 && (l2 == 1 || l != l2 || strncmp(rowsBuf2[r] + 1, rowsBuf[r] + 1, l - 1) != 0))
            {
                strncpy(rowsBuf[r], rowsBuf2[r], l2);

                if (l2 > cols)
                    error("l2");

                for (int i = l2; i < cols; ++i)
                    rowsBuf[r][i] = ' ';
                rowsBuf[r][cols] = 0;
                lcd->setCursor(1, r);
                lcd->print(rowsBuf[r] + 1);
            }
        }
    }

    invalidated = false;
}

bool LCDRotaryMenu::move(int diff)
{
    LCDRotaryMenuItem *parent = (selectedItem == NULL || selectedItem->parent == NULL) ? root : selectedItem->parent;

    vector<LCDRotaryMenuItem *> &menuItems = parent->children;

    auto menuItemsSize = menuItems.size();

    if (menuItemsSize == 0)
        return false;

    if (selectedItem == NULL)
        selectedItem = *menuItems.begin();

    LCDRotaryMenuItem *old = selectedItem;

    int selectedItemIndex = -1;
    for (int i = 0; i < menuItemsSize; ++i)
    {
        if (menuItems[i] == selectedItem)
        {
            selectedItemIndex = i;
            break;
        }
    }
    if (selectedItemIndex == -1)
        error("menuitem idx not found");

    auto newSelectedItemIndex = selectedItemIndex + diff;
    if (newSelectedItemIndex < 0)
        newSelectedItemIndex = 0;
    if (newSelectedItemIndex >= menuItemsSize)
        newSelectedItemIndex = menuItemsSize - 1;

    selectedItem = menuItems[newSelectedItemIndex];
    parent->selectedChild = selectedItem;

    int customLineCnt = customLineRow != -1 ? 1 : 0;
    if (customLineRow2 != -1)
        ++customLineCnt;

    if (newSelectedItemIndex < parent->scrollRowPos)
        parent->scrollRowPos = newSelectedItemIndex;
    else if (newSelectedItemIndex >= parent->scrollRowPos + rows - customLineCnt)
        parent->scrollRowPos = newSelectedItemIndex;

    //debug("new menu idx:%d ( scrollpos:%d )", newSelectedItemIndex, parent->scrollRowPos);

    invalidated = true;

    return selectedItem != old;
}

void LCDRotaryMenu::invalidate()
{
    invalidated = true;
}

void LCDRotaryMenu::setSplashCb(void (*splCb)(LiquidCrystal_I2C &lcd), uint32_t timeoutMs)
{
    this->splCb = splCb;
    this->splTimeoutMs = timeoutMs;
}

void LCDRotaryMenu::setDefaultCb(LCDRotaryMenuItemCB cb)
{
    defaultCb = cb;
}

void LCDRotaryMenu::setButtonCb(void (*cb)())
{
    this->btnCb = cb;
}

void LCDRotaryMenu::setRotCb(void (*cb)())
{
    this->rotCb = cb;
}

int lastPressCount = 0;
int lastRotPos = 0;

void LCDRotaryMenu::init()
{
    lcd->init();

    lcd->backlight();
    lcd->clear();

    if (splCb)
    {
        splCb(*lcd);
        splashDisplayed = true;
    }
    else
        displayMenu();

    menuBeginTimestamp = millis();

    //debug("INIT press cnt = %d", lastPressCount);
}

void LCDRotaryMenu::loop()
{
    if (busyMode)
        return;

    if (splashDisplayed)
    {
        if (millis() - menuBeginTimestamp >= splTimeoutMs)
        {
            splashDisplayed = false;
            lcd->clear();
            displayMenu();
        }
        return;
    }

    bool redrawMenu = invalidated || false;

    if (btn->getPressCount() != lastPressCount)
    {
        lastPressCount = btn->getPressCount();

        if (btnCb != NULL)
            btnCb();

        if (selectedItem != NULL)
        {
            selectedItem->select();

            redrawMenu = true;
        }

        //debug("press cnt = %d", lastPressCount);
    }

    if (rotary->getRotPos() != lastRotPos)
    {
        auto rotPos = rotary->getRotPos();
        auto rotDiff = rotPos - lastRotPos;
        lastRotPos = rotPos;

        move(rotDiff);

        redrawMenu = true;

        //debug("rot pos = %d", lastRotPos);
    }

    if (redrawMenu)
        displayMenu();
}

LCDRotaryMenuItem &LCDRotaryMenu::getRoot() { return *root; }

LCDRotaryMenuItem *LCDRotaryMenu::getSelected() { return selectedItem; }

void LCDRotaryMenu::setSelected(LCDRotaryMenuItem &_selectedItem)
{
    selectedItem = &_selectedItem;
}

void LCDRotaryMenu::setCustomLine(const char *customLine, short rowIdx)
{
    customLineRow = rowIdx;
    if (customLineRow != -1 && customLineRow < rows)
    {
        strncpy(rowsBuf[customLineRow], customLine, cols + 1);
    }
    int l = strlen(customLine);
    for (int i = l; i < cols; ++i)
        rowsBuf[customLineRow][i] = ' ';
    rowsBuf[customLineRow][cols] = 0;
    invalidate();
}

void LCDRotaryMenu::setCustomLine2(const char *customLine2, short rowIdx)
{
    customLineRow2 = rowIdx;
    if (customLineRow2 != -1 && customLineRow < rows)
    {
        strncpy(rowsBuf[customLineRow2], customLine2, cols + 1);
    }
    int l = strlen(customLine2);
    for (int i = l; i < cols; ++i)
        rowsBuf[customLineRow2][i] = ' ';
    rowsBuf[customLineRow2][cols] = 0;
    invalidate();
}

void LCDRotaryMenu::unsetCustomLine()
{
    if (customLineRow != -1 || customLineRow2 != -1)
    {
        customLineRow = -1;
        customLineRow2 = -1;

        invalidate();
    }
}

LiquidCrystal_I2C &LCDRotaryMenu::getLCD()
{
    return *lcd;
}

void LCDRotaryMenu::setBusyLine(const char *busyLine, short rowIdx)
{
    if (!busyMode)
    {
        lcd->clear();
        busyMode = true;
    }
    lcd->setCursor(0, rowIdx);
    lcd->print(busyLine);
}

void LCDRotaryMenu::unsetBusy()
{
    busyMode = false;
    invalidate();
}

#endif

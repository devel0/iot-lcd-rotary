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

    int collapsedMenuItemsCount = 0;
    int selectedItemIndex = -1;
    for (int i = 0; i < menuItemsSize; ++i)
    {
        if (menuItems[i] == selectedItem)
        {
            selectedItemIndex = i;
        }
        if (menuItems[i]->getCollapsed())
            ++collapsedMenuItemsCount;
    }
    if (selectedItemIndex == -1)
        error("menuitem idx not found");

    int customLineCount = customLineRow != -1 ? 1 : 0;
    if (customLineRow2 != -1)
        ++customLineCount;

    editOn = NULL;

    int collapsedPartialCnt = 0;

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
                auto kidx = parent->scrollRowPos + collapsedPartialCnt + r - (r >= customLineRow ? customLineCount : 0);
                auto item = menuItems[kidx];
                if (item->getCollapsed())
                {
                    ++collapsedPartialCnt;
                    --r;
                    continue;
                }
                if (item == selectedItem)
                {
                    rowsBuf2[r][0] = item->isBack ? '<' : '>';
                    rowsBuf2[r][1] = 0;
                    if (selectedItem->isEditing)
                    {
                        editOnRow = r;
                        editOn = selectedItem;
                    }
                }
                else
                {
                    rowsBuf2[r][0] = ' ';
                    rowsBuf2[r][1] = 0;
                }

                displayedMenuItems[r] = item;

                auto &prefix = item->getPrefix();
                auto &txt = item->getText();
                if (prefix.length() > 0)
                {
                    strncat(rowsBuf2[r], prefix.c_str(), cols - 1);
                    strncat(rowsBuf2[r], txt.c_str(), cols - prefix.length() - 1);
                }
                else
                    strncat(rowsBuf2[r], txt.c_str(), cols - 1);

                l2 = strlen(rowsBuf2[r]);

                if (item->getMode() == LCDRotaryMenuItemModeEnum::MI_Normal &&
                    item->children.size() > 0 &&
                    options.subMenuPostChar != ' ')
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

    if (editOn != NULL)
    {
        lcd->cursor_on();
        lcd->setCursor(editOn->editingCol, editOnRow);
    }
    else
        lcd->cursor_off();

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

    if (menuItems[newSelectedItemIndex]->getCollapsed())
    {
        if (diff < 0)
            --newSelectedItemIndex;
        else if (diff > 0)
            ++newSelectedItemIndex;
    }

    if (newSelectedItemIndex < 0)
        newSelectedItemIndex = 0;
    if (newSelectedItemIndex >= menuItemsSize)
        newSelectedItemIndex = menuItemsSize - 1;

    selectedItem = menuItems[newSelectedItemIndex];
    parent->selectedChild = selectedItem;

    int customLineCnt = customLineRow != -1 ? 1 : 0;
    if (customLineRow2 != -1)
        ++customLineCnt;

    auto collapsedCntBeforeNewSelected = 0;
     
    for (int i = parent->scrollRowPos; i < newSelectedItemIndex; ++i)
    {
        auto iscoll = menuItems[i]->getCollapsed();

        if (iscoll)
        {
            if (i < newSelectedItemIndex)
            {
                ++collapsedCntBeforeNewSelected;
            }
        }
    }    

    if (newSelectedItemIndex < parent->scrollRowPos)
        parent->scrollRowPos = newSelectedItemIndex;
    else if (newSelectedItemIndex >= parent->scrollRowPos + rows - customLineCnt + collapsedCntBeforeNewSelected)
        parent->scrollRowPos = newSelectedItemIndex;

    // debug("new menu idx:%d ( scrollpos:%d ) collBefore:%d",
    //       newSelectedItemIndex, parent->scrollRowPos,
    //       collapsedCntBeforeNewSelected);

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

    // debug("INIT press cnt = %d", lastPressCount);
}

void LCDRotaryMenu::setBackPressedCb(LCDRotaryMenuItemCB cb)
{
    backPressedCb = cb;
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
            if (selectedItem->getMode() == LCDRotaryMenuItemModeEnum::MI_Normal)
                selectedItem->select();

            redrawMenu = true;
        }

        if (selectedItem != NULL)
        {
            switch (selectedItem->getMode())
            {

            case LCDRotaryMenuItemModeEnum::MI_MultiSelect:
            {
                editOn = selectedItem;

                editOn->isEditing = !editOn->isEditing;

                invalidated = true;
            }
            break;

            case LCDRotaryMenuItemModeEnum::MI_NumericInput:
            {
                editOn = selectedItem;
                if (editOn->editingCol == editOn->beginEditingCol)
                {
                    if (!editOn->isEditing)
                    {
                        editOn->isEditing = true;
                        editOn->editingCol = editOn->beginEditingCol;
                    }
                    else
                        editOn->isEditing = !editOn->isEditing;
                }
                else
                    editOn->isEditingCol = !editOn->isEditingCol;
            }
            break;
            }
        }

        // debug("press cnt = %d", lastPressCount);
    }

    if (rotary->getRotPos() != lastRotPos)
    {
        auto rotPos = rotary->getRotPos();
        auto rotDiff = rotPos - lastRotPos;
        lastRotPos = rotPos;

        if (editOn != NULL)
        {
            auto &s_val = editOn->getText();
            auto &s_pre = editOn->getPrefix();
            int l_val = s_val.length();
            int l_pre = s_pre.length();

            switch (selectedItem->getMode())
            {
            case LCDRotaryMenuItemModeEnum::MI_MultiSelect:
            {
                auto &childs = selectedItem->children;
                auto &selTxt = selectedItem->getText();
                auto s = childs.size();
                auto selChildIdx = 0;
                for (int i = 0; i < s; ++i)
                {
                    if (childs[i]->getText() == selTxt)
                    {
                        selChildIdx = i;
                        break;
                    }
                }
                if (rotDiff > 0)
                {
                    if (selChildIdx < s - 1)
                        ++selChildIdx;
                    else
                        selChildIdx = 0;
                }
                else if (rotDiff < 0)
                {
                    if (selChildIdx > 0)
                        --selChildIdx;
                    else
                        selChildIdx = s - 1;
                }
                auto selChild = childs[selChildIdx];
                selectedItem->setText(selChild->getText());
                selectedItem->setSelectedChild(selChild);
            }
            break;

            case LCDRotaryMenuItemModeEnum::MI_NumericInput:
            {
                if (editOn->isEditingCol)
                {
                    if (editOn->editingCol - 1 < l_pre + l_val)
                    {
                        const char *cstr = s_val.c_str();
                        char buf[cols + 1];
                        int i = 0;
                        while (cstr[i] != 0 && i < editOn->editingCol - editOn->beginEditingCol)
                        {
                            buf[i] = cstr[i];
                            ++i;
                        }
                        int nr = ((int)cstr[i]) - ((int)'0');
                        if (rotDiff > 0)
                            nr = nr < 9 ? nr + 1 : nr;
                        else
                            nr = nr > 0 ? nr - 1 : nr;
                        buf[i] = ((int)'0') + nr;

                        ++i;
                        while (cstr[i] != 0)
                        {
                            buf[i] = cstr[i];
                            ++i;
                        }
                        buf[i] = 0;
                        editOn->setText(buf);
                    }
                }
                else
                {
                    if (editOn->editingCol == editOn->beginEditingCol && rotDiff < 0)
                    {
                        editOn->isEditing = editOn->isEditingCol = false;
                        if (move(rotDiff) && rotCb != NULL)
                            rotCb();
                    }
                    else if (editOn->editingCol == editOn->beginEditingCol + l_val - 1 && rotDiff > 0)
                    {
                        editOn->isEditing = editOn->isEditingCol = false;
                        if (move(rotDiff) && rotCb != NULL)
                            rotCb();
                    }
                    else if (editOn->editingCol == 0 && l_pre > 0 && rotDiff > 0)
                        editOn->editingCol = l_pre + 1;
                    else
                    {
                        editOn->editingCol += rotDiff;
                        if (editOn->editingCol - 1 >= l_pre + l_val)
                            editOn->editingCol = l_pre + l_val;
                        if (editOn->editingCol < l_pre + 1)
                            editOn->editingCol = 0;
                        else if (editOn->editingCol >= cols - 1)
                            editOn->editingCol = cols - 1;
                    }
                    // if (editOn->editingCol == 0)
                    // {
                    //     editOn->isEditing = false;
                    // }
                }
            }
            break;
            }
            invalidated = true;
        }
        else if (move(rotDiff) && rotCb != NULL)
            rotCb();

        redrawMenu = true;

        // debug("rot pos = %d", lastRotPos);
    }

    if (redrawMenu)
    {
        displayMenu();
        redrawMenu = false;
    }
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

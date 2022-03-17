#ifdef ARDUINO

#include "lcd-rotary-menuitem.h"

#include "lcd-rotary-menu.h"

using namespace std;

void goBack(LCDRotaryMenuItem &item)
{
    item.back();
}

LCDRotaryMenuItem::LCDRotaryMenuItem(LCDRotaryMenu &menu, LCDRotaryMenuItem *parent, int tag, void *custom) : menu(menu)
{
    this->parent = parent;
    this->tag = tag;
    this->customPtr = custom;
    scrollRowPos = 0;
    selectedChild = NULL;

    /*if (!(options & NO_BACK))
    {
        auto backMenuItem = new LCDRotaryMenuItem(menu, this, LCDRotaryMenuItemOptions::NO_BACK);
        backMenuItem->setText("..");
        backMenuItem->onSelect(goBack);
        children.push_back(backMenuItem);
    }*/
}

LCDRotaryMenuItem::~LCDRotaryMenuItem()
{
    int cs = children.size();
    for (int ci = 0; ci < cs; ++ci)
    {
        delete children[ci];
    }
}

void LCDRotaryMenuItem::clear()
{
    int cs = children.size();
    for (int ci = 0; ci < cs; ++ci)
    {
        delete children[ci];
    }
    children.clear();
    selectedChild = NULL;
}

LCDRotaryMenuItem &LCDRotaryMenuItem::append(string menuText, int tag, void *custom)
{
    auto newItem = new LCDRotaryMenuItem(menu, this, tag, custom);
    newItem->setText(menuText);

    if (this != menu.root && mode == LCDRotaryMenuItemModeEnum::MI_Normal && children.size() == 0)
    {
        auto backMenuItem = new LCDRotaryMenuItem(menu, this);
        backMenuItem->setText(menu.options.backString);
        backMenuItem->isBack = true;
        backMenuItem->onSelect(goBack);
        children.push_back(backMenuItem);
    }

    children.push_back(newItem);

    return *newItem;
}

LCDRotaryMenuItem &LCDRotaryMenuItem::appendAfter(LCDRotaryMenuItem &before, string menuText, int tag, void *custom)
{
    auto newItem = new LCDRotaryMenuItem(menu, this, tag, custom);
    newItem->setText(menuText);

    if (this != menu.root && children.size() == 0)
    {
        auto backMenuItem = new LCDRotaryMenuItem(menu, this);
        backMenuItem->setText(menu.options.backString);
        backMenuItem->isBack = true;
        backMenuItem->onSelect(goBack);
        children.push_back(backMenuItem);
    }

    auto it = children.begin();
    auto it_end = children.end();
    while (it != it_end)
    {
        if ((*it) == &before)
        {
            children.insert(it + 1, newItem);
            return *newItem;
        }
        ++it;
    }

    children.push_back(newItem);

    return *newItem;
}

bool LCDRotaryMenuItem::remove(LCDRotaryMenuItem *child)
{
    auto it = children.begin();
    auto it_end = children.end();
    while (it != it_end)
    {
        if ((*it) == child)
        {
            children.erase(it);
            return true;
        }
        ++it;
    }

    return false;
}

LCDRotaryMenuItem *LCDRotaryMenuItem::getParent()
{
    return parent;
}

LCDRotaryMenuItem *LCDRotaryMenuItem::getSelectedChild()
{
    return selectedChild;
}

void LCDRotaryMenuItem::setSelectedChild(LCDRotaryMenuItem *child)
{
    selectedChild = child;
}

vector<LCDRotaryMenuItem *> LCDRotaryMenuItem::getChildren()
{
    return children;
}

void LCDRotaryMenuItem::onSelect(LCDRotaryMenuItemCB cb)
{
    this->selectCb = cb;
}

void LCDRotaryMenuItem::onSelect(void (*cb)())
{
    this->selectCb2 = cb;
}

void LCDRotaryMenuItem::setText(string menuText)
{
    text = menuText;
    menu.invalidate();
}

void LCDRotaryMenuItem::setPrefix(string menuPrefixText)
{
    prefix = menuPrefixText;
    editingCol = 0;
    beginEditingCol = menuPrefixText.length() + 1;
    menu.invalidate();
}

void LCDRotaryMenuItem::select()
{
    if (children.size() > 0)
    {
        if (selectedChild != NULL)
        {
            menu.selectedItem = selectedChild;
        }
        else
        {
            selectedChild = children[0];
            menu.selectedItem = selectedChild;
        }
    }

    if (isBack && menu.backPressedCb != NULL)
        menu.backPressedCb(*this);

    if (selectCb != NULL)
        selectCb(*this);
    else if (selectCb2 != NULL)
        selectCb2();
    else if (menu.defaultCb != NULL)
        menu.defaultCb(*this);

    menu.invalidate();
}

void LCDRotaryMenuItem::back()
{
    menu.selectedItem = parent->parent->selectedChild;
    menu.invalidate();
}

const string &LCDRotaryMenuItem::getText() const
{
    return text;
}

const string &LCDRotaryMenuItem::getPrefix() const
{
    return prefix;
}

int LCDRotaryMenuItem::getTag() const
{
    return tag;
}

void *LCDRotaryMenuItem::getCustom()
{
    return customPtr;
}

bool LCDRotaryMenuItem::isDisplayed() const
{
    for (int i = 0; i < menu.cols; ++i)
        if (menu.displayedMenuItems[i] == this)
            return true;

    return false;
}

void LCDRotaryMenuItem::setMode(LCDRotaryMenuItemModeEnum newMode)
{
    mode = newMode;
}

LCDRotaryMenuItemModeEnum LCDRotaryMenuItem::getMode() const
{
    return mode;
}

void LCDRotaryMenuItem::setScrollRowPos(int scrollRow)
{
    if (this->parent != NULL)
        this->parent->scrollRowPos = scrollRow;
}

void LCDRotaryMenuItem::setCollapsed(bool collapsed)
{
    isCollapsed = collapsed;
}

bool LCDRotaryMenuItem::getCollapsed() const
{
    return isCollapsed;
}

#endif
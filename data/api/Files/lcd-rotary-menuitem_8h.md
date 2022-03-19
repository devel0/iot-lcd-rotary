---
title: include/lcd-rotary-menuitem.h


---

# include/lcd-rotary-menuitem.h







## Namespaces

| Name           |
| -------------- |
| **[std](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Namespaces/namespacestd.md)**  |

## Classes

|                | Name           |
| -------------- | -------------- |
| class | **[LCDRotaryMenuItem](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md)**  |

## Types

|                | Name           |
| -------------- | -------------- |
| enum | **[LCDRotaryMenuItemModeEnum](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Files/lcd-rotary-menuitem_8h.md#enum-lcdrotarymenuitemmodeenum)** { MI_Normal, MI_MultiSelect, MI_NumericInput } |
| typedef void(*)(LCDRotaryMenuItem &) | **[LCDRotaryMenuItemCB](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Files/lcd-rotary-menuitem_8h.md#typedef-lcdrotarymenuitemcb)**  |










## Types Documentation

### enum LCDRotaryMenuItemModeEnum


| Enumerator | Value | Description |
| ---------- | ----- | ----------- |
| MI_Normal |  |   |
| MI_MultiSelect |  |   |
| MI_NumericInput |  |   |































### typedef LCDRotaryMenuItemCB

```cpp
typedef void(* LCDRotaryMenuItemCB) (LCDRotaryMenuItem &);
```


































## Source code

```cpp
#ifndef _LCD_ROTARY_MENUITEM_H
#define _LCD_ROTARY_MENUITEM_H

#ifdef ARDUINO

#include <Arduino.h>

#include <vector>

using namespace std;

class LCDRotaryMenu;
class LCDRotaryMenuItem;

typedef void (*LCDRotaryMenuItemCB)(LCDRotaryMenuItem &);

enum LCDRotaryMenuItemModeEnum
{
    MI_Normal,
    MI_MultiSelect,
    MI_NumericInput
};

class LCDRotaryMenuItem
{
    friend class LCDRotaryMenu;

    LCDRotaryMenu &menu;

    LCDRotaryMenuItem *parent;

    LCDRotaryMenuItem(LCDRotaryMenu &menu, LCDRotaryMenuItem *parent, int tag = -1, void *custom = NULL);

    vector<LCDRotaryMenuItem *> children;

    string text;

    string prefix;

    int scrollRowPos;

    LCDRotaryMenuItem *selectedChild;

    LCDRotaryMenuItemCB selectCb = NULL;

    void (*selectCb2)() = NULL;

    bool isBack = false;

    int tag = -1;

    void *customPtr = NULL;

    LCDRotaryMenuItemModeEnum mode = LCDRotaryMenuItemModeEnum::MI_Normal;

    bool multiRollOver = true;

    bool isEditing = false;

    bool isEditingCol = false;

    int editingCol = 0;
    int beginEditingCol = 0;

    bool isCollapsed = false;

public:
    ~LCDRotaryMenuItem();

    void clear();

    LCDRotaryMenuItem &append(string prefixText, string menuText, int tag = -1, void *custom = NULL);

    LCDRotaryMenuItem &append(string menuText, int tag = -1, void *custom = NULL);

    LCDRotaryMenuItem &appendAfter(LCDRotaryMenuItem &before, string menuText, int tag = -1, void *custom = NULL);

    bool remove(LCDRotaryMenuItem *child);

    LCDRotaryMenuItem *getParent();

    LCDRotaryMenuItem *getSelectedChild();

    void setSelectedChild(LCDRotaryMenuItem *child);

    vector<LCDRotaryMenuItem *> getChildren();

    void setText(string menuText);

    void setPrefix(string menuPrefixText);

    const string &getText() const;

    const string &getPrefix() const;

    void onSelect(LCDRotaryMenuItemCB cb);

    void onSelect(void (*cb)());    

    void select();

    void back();

    int getTag() const;

    void *getCustom();

    bool isDisplayed() const;

    void setMode(LCDRotaryMenuItemModeEnum newMode);

    void setMultiRollOver(bool rollOver);

    LCDRotaryMenuItemModeEnum getMode() const;

    void setScrollRowPos(int scrollRow);

    void setCollapsed(bool collapsed);

    bool getCollapsed() const;
};

#endif

#endif
```


-------------------------------



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
| typedef void(*)(LCDRotaryMenuItem &) | **[LCDRotaryMenuItemCB](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Files/lcd-rotary-menuitem_8h.md#typedef-lcdrotarymenuitemcb)**  |










## Types Documentation

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

class LCDRotaryMenuItem
{
    friend class LCDRotaryMenu;

    LCDRotaryMenu &menu;

    LCDRotaryMenuItem *parent;

    LCDRotaryMenuItem(LCDRotaryMenu &menu, LCDRotaryMenuItem *parent, int tag = -1, void *custom = NULL);

    vector<LCDRotaryMenuItem *> children;

    String text;

    int scrollRowPos;

    LCDRotaryMenuItem *selectedChild;

    LCDRotaryMenuItemCB selectCb = NULL;

    void (*selectCb2)() = NULL;

    bool isBack = false;

    int tag = -1;

    void *customPtr = NULL;

public:
    ~LCDRotaryMenuItem();

    void clear();

    LCDRotaryMenuItem &append(String menuText, int tag = -1, void *custom = NULL);

    LCDRotaryMenuItem *getParent();

    void setText(String menuText);

    void onSelect(LCDRotaryMenuItemCB cb);

    void onSelect(void (*cb)());

    void select();

    void back();

    const String &getText() const;

    int getTag() const;

    void *getCustom();

    bool isDisplayed() const;
};

#endif

#endif
```


-------------------------------



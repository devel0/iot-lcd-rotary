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
| enum | **[LCDRotaryMenuItemModeEnum](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Files/lcd-rotary-menuitem_8h.md#enum-lcdrotarymenuitemmodeenum)** { MI_Normal, MI_MultiSelect, MI_NumericInput, MI_TextInput } |
| typedef bool(*)(LCDRotaryMenuItem &) | **[LCDRotaryMenuItemCB](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Files/lcd-rotary-menuitem_8h.md#typedef-lcdrotarymenuitemcb)**  |





## Defines

|                | Name           |
| -------------- | -------------- |
|  | **[RMI_FLAG_IS_BACK](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Files/lcd-rotary-menuitem_8h.md#define-rmi_flag_is_back)**  |
|  | **[RMI_FLAG_MULTI_ROLLOVER](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Files/lcd-rotary-menuitem_8h.md#define-rmi_flag_multi_rollover)**  |
|  | **[RMI_FLAG_IS_EDITING](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Files/lcd-rotary-menuitem_8h.md#define-rmi_flag_is_editing)**  |
|  | **[RMI_FLAG_IS_EDITING_COL](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Files/lcd-rotary-menuitem_8h.md#define-rmi_flag_is_editing_col)**  |
|  | **[RMI_FLAG_IS_COLLAPSED](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Files/lcd-rotary-menuitem_8h.md#define-rmi_flag_is_collapsed)**  |





## Types Documentation

### enum LCDRotaryMenuItemModeEnum


| Enumerator | Value | Description |
| ---------- | ----- | ----------- |
| MI_Normal |  |   |
| MI_MultiSelect |  |   |
| MI_NumericInput |  |   |
| MI_TextInput |  |   |































### typedef LCDRotaryMenuItemCB

```cpp
typedef bool(* LCDRotaryMenuItemCB) (LCDRotaryMenuItem &);
```
































## Macro Documentation

### define RMI_FLAG_IS_BACK

```cpp
#define RMI_FLAG_IS_BACK (1 << 0)
```





























### define RMI_FLAG_MULTI_ROLLOVER

```cpp
#define RMI_FLAG_MULTI_ROLLOVER (1 << 1)
```





























### define RMI_FLAG_IS_EDITING

```cpp
#define RMI_FLAG_IS_EDITING (1 << 2)
```





























### define RMI_FLAG_IS_EDITING_COL

```cpp
#define RMI_FLAG_IS_EDITING_COL (1 << 3)
```





























### define RMI_FLAG_IS_COLLAPSED

```cpp
#define RMI_FLAG_IS_COLLAPSED (1 << 4)
```































## Source code

```cpp
#ifndef _LCD_ROTARY_MENUITEM_H
#define _LCD_ROTARY_MENUITEM_H

#ifdef ARDUINO

#include <Arduino.h>

#include <vector>

using namespace std;

#define RMI_FLAG_IS_BACK (1 << 0)
#define RMI_FLAG_MULTI_ROLLOVER (1 << 1)
#define RMI_FLAG_IS_EDITING (1 << 2)
#define RMI_FLAG_IS_EDITING_COL (1 << 3)
#define RMI_FLAG_IS_COLLAPSED (1 << 4)

class LCDRotaryMenu;
class LCDRotaryMenuItem;

typedef bool (*LCDRotaryMenuItemCB)(LCDRotaryMenuItem &);

enum LCDRotaryMenuItemModeEnum
{
    MI_Normal,
    MI_MultiSelect,
    MI_NumericInput,
    MI_TextInput
};

class LCDRotaryMenuItem
{
    friend class LCDRotaryMenu;

    LCDRotaryMenu &menu;

    LCDRotaryMenuItem *parent;

    LCDRotaryMenuItem(LCDRotaryMenu &menu, LCDRotaryMenuItem *parent, int tag = -1, void *custom = NULL);

    vector<LCDRotaryMenuItem *> children;

    char *text = NULL;

    char *prefix = NULL;

    int scrollRowPos;

    LCDRotaryMenuItem *selectedChild;

    LCDRotaryMenuItemCB selectCb = NULL;

    int tag = -1;

    void *customPtr = NULL;

    LCDRotaryMenuItemModeEnum mode = LCDRotaryMenuItemModeEnum::MI_Normal;

    int editingCol = 0;
    int beginEditingCol = 0;

    static constexpr const char *DEFAULT_textMaskCharset = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    const char *textMaskCharset = DEFAULT_textMaskCharset;

    uint8_t flags = 0;

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

    vector<LCDRotaryMenuItem *> &getChildren();

    void setText(string menuText);

    void setPrefix(string menuPrefixText);

    const char *getText() const;

    const char *getPrefix() const;

    void onSelect(LCDRotaryMenuItemCB cb);

    void select();

    void back();

    int getTag() const;

    void *getCustom();

    bool isDisplayed() const;

    void setMode(LCDRotaryMenuItemModeEnum newMode);

    void setTextMaskCharset(const char *textMask);

    LCDRotaryMenuItemModeEnum getMode() const;

    void setScrollRowPos(int scrollRow);

    inline int getScrollRowPos() const { return scrollRowPos; }

    // -- flags [get]

    inline bool isBack() const { return (flags & RMI_FLAG_IS_BACK) != 0; }

    inline bool isEditing() const { return (flags & RMI_FLAG_IS_EDITING) != 0; }

    inline bool isEditingCol() const { return (flags & RMI_FLAG_IS_EDITING_COL) != 0; }

    inline bool isCollapsed() const { return (flags & RMI_FLAG_IS_COLLAPSED) != 0; }

    inline bool getMultiRollOver() const { return (flags & RMI_FLAG_MULTI_ROLLOVER) != 0; }

    // -- flags [set]

    void setIsEditing(bool val);

    void setIsEditingCol(bool val);

    void setIsCollapsed(bool collapsed);

    void setMultiRollOver(bool rollOver);
};

#endif

#endif
```


-------------------------------



---
title: LCDRotaryMenu
summary: LCD Rotary Menu.  

---

# LCDRotaryMenu




LCD Rotary Menu.  [More...](#detailed-description)


`#include <lcd-rotary-menu.h>`















## Public Functions

|                | Name           |
| -------------- | -------------- |
|  | **[LCDRotaryMenu](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu.md#function-lcdrotarymenu)**(int addr, int cols, int rows, int rotAPin, int rotBPin, int rotSWPin, bool inverted =false, int btnDebounceMs =50, int abDebounceUs =1500) <br>Construct a new [LCDRotaryMenu](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu.md) object.  |
|  | **[~LCDRotaryMenu](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu.md#function-~lcdrotarymenu)**()  |
| void | **[invalidate](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu.md#function-invalidate)**() <br>force menu redraw, for use within programmatic menu manipulation not tie within callbacks  |
| void | **[setSplashCb](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu.md#function-setsplashcb)**(void(*)(LiquidCrystal_I2C &lcd) splCb, uint32_t timeoutMs) <br>Set splash callback before Init.  |
| void | **[setDefaultCb](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu.md#function-setdefaultcb)**([LCDRotaryMenuItemCB](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Files/lcd-rotary-menuitem_8h.md#typedef-lcdrotarymenuitemcb) cb) <br>set default callback when select menuitem that has no custom callback  |
| void | **[onMultiSelect](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu.md#function-onmultiselect)**([LCDRotaryMenuItemCB](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Files/lcd-rotary-menuitem_8h.md#typedef-lcdrotarymenuitemcb) cb) <br>set callback on select this item (multi select mode)  |
| void | **[onEditEnd](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu.md#function-oneditend)**([LCDRotaryMenuItemCB](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Files/lcd-rotary-menuitem_8h.md#typedef-lcdrotarymenuitemcb) cb) <br>set callback when edit mode ended  |
| void | **[setButtonCb](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu.md#function-setbuttoncb)**(void(*)() cb) <br>set callback that will be called everytime button switch ; it's called before any specific onSelect callback  |
| void | **[setBackPressedCb](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu.md#function-setbackpressedcb)**([LCDRotaryMenuItemCB](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Files/lcd-rotary-menuitem_8h.md#typedef-lcdrotarymenuitemcb) cb) <br>set callback when press on .. ( parent ) ; parent menu can be retrived using callbacak argument getParent()  |
| void | **[setRotCb](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu.md#function-setrotcb)**(void(*)() cb) <br>set callback that will be called everytime rotary move to different menu item  |
| void | **[init](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu.md#function-init)**()  |
| void | **[loop](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu.md#function-loop)**()  |
| [LCDRotaryMenuItem](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md) & | **[getRoot](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu.md#function-getroot)**()  |
| [LCDRotaryMenuItem](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md) * | **[getSelected](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu.md#function-getselected)**() <br>retrieve currently selected menu  |
| void | **[setSelected](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu.md#function-setselected)**([LCDRotaryMenuItem](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md) & item, bool scrollTo =false, int customScrollRowPos =-1)  |
| void | **[setCustomLine](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu.md#function-setcustomline)**(const char * customLine, short rowIdx)  |
| void | **[setCustomLine2](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu.md#function-setcustomline2)**(const char * customLine2, short rowIdx)  |
| void | **[unsetCustomLine](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu.md#function-unsetcustomline)**()  |
| void | **[inhibit](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu.md#function-inhibit)**(uint32_t timeout_ms)  |
| LiquidCrystal_I2C & | **[getLCD](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu.md#function-getlcd)**() <br>retrieve lcd pointer ( advanced )  |
| void | **[setBusyLine](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu.md#function-setbusyline)**(const char * busyLine, short rowIdx)  |
| void | **[unsetBusy](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu.md#function-unsetbusy)**()  |

## Protected Functions

|                | Name           |
| -------------- | -------------- |
| void | **[displayMenu](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu.md#function-displaymenu)**()  |
| bool | **[move](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu.md#function-move)**(int diff) <br>move into menu for given diff pos ; return false if at end of menu  |



## Public Attributes

|                | Name           |
| -------------- | -------------- |
| [LCDRotaryMenuOptions](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/struct_l_c_d_rotary_menu_options.md) | **[options](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu.md#variable-options)**  |


## Friends

|                | Name           |
| -------------- | -------------- |
| class | **[LCDRotaryMenuItem](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu.md#friend-lcdrotarymenuitem)**  |





## Detailed Description

```cpp
class LCDRotaryMenu;
```

LCD Rotary Menu. 


























nfo 











## Public Functions Documentation

### function LCDRotaryMenu

```cpp
LCDRotaryMenu(
    int addr,
    int cols,
    int rows,
    int rotAPin,
    int rotBPin,
    int rotSWPin,
    bool inverted =false,
    int btnDebounceMs =50,
    int abDebounceUs =1500
)
```

Construct a new [LCDRotaryMenu](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu.md) object. 

**Parameters**: 

  * **addr** i2c lcd address 
  * **cols** nr. of lcd columns 
  * **rows** nr. of lcd rows 
  * **rotAPin** pin of rotary encoder A 
  * **rotBPin** pin of rotary encoder B 
  * **rotSWPin** pin of rotary encoder switch 
  * **inverted** if true cw/ccw generates decrement/increment in position 
  * **btnDebounceMs** debounce(ms) for rotary switch 
  * **btnDebounceMs** debounce(us) for rotary A, B 




























### function ~LCDRotaryMenu

```cpp
~LCDRotaryMenu()
```





























### function invalidate

```cpp
void invalidate()
```

force menu redraw, for use within programmatic menu manipulation not tie within callbacks 




























### function setSplashCb

```cpp
void setSplashCb(
    void(*)(LiquidCrystal_I2C &lcd) splCb,
    uint32_t timeoutMs
)
```

Set splash callback before Init. 

**Parameters**: 

  * **splCb** callback here you can directly used lcd ( clear, setCursor, print ) 
  * **timeoutMs** time after which menu display 




























### function setDefaultCb

```cpp
void setDefaultCb(
    LCDRotaryMenuItemCB cb
)
```

set default callback when select menuitem that has no custom callback 




























### function onMultiSelect

```cpp
void onMultiSelect(
    LCDRotaryMenuItemCB cb
)
```

set callback on select this item (multi select mode) 




























### function onEditEnd

```cpp
void onEditEnd(
    LCDRotaryMenuItemCB cb
)
```

set callback when edit mode ended 




























### function setButtonCb

```cpp
void setButtonCb(
    void(*)() cb
)
```

set callback that will be called everytime button switch ; it's called before any specific onSelect callback 

**Parameters**: 

  * **cb** 




























### function setBackPressedCb

```cpp
void setBackPressedCb(
    LCDRotaryMenuItemCB cb
)
```

set callback when press on .. ( parent ) ; parent menu can be retrived using callbacak argument getParent() 




























### function setRotCb

```cpp
void setRotCb(
    void(*)() cb
)
```

set callback that will be called everytime rotary move to different menu item 




























### function init

```cpp
void init()
```





























### function loop

```cpp
void loop()
```





























### function getRoot

```cpp
LCDRotaryMenuItem & getRoot()
```





























### function getSelected

```cpp
LCDRotaryMenuItem * getSelected()
```

retrieve currently selected menu 




























### function setSelected

```cpp
void setSelected(
    LCDRotaryMenuItem & item,
    bool scrollTo =false,
    int customScrollRowPos =-1
)
```





























### function setCustomLine

```cpp
void setCustomLine(
    const char * customLine,
    short rowIdx
)
```





























### function setCustomLine2

```cpp
void setCustomLine2(
    const char * customLine2,
    short rowIdx
)
```





























### function unsetCustomLine

```cpp
void unsetCustomLine()
```





























### function inhibit

```cpp
void inhibit(
    uint32_t timeout_ms
)
```





























### function getLCD

```cpp
LiquidCrystal_I2C & getLCD()
```

retrieve lcd pointer ( advanced ) 




























### function setBusyLine

```cpp
void setBusyLine(
    const char * busyLine,
    short rowIdx
)
```





























### function unsetBusy

```cpp
void unsetBusy()
```






























## Protected Functions Documentation

### function displayMenu

```cpp
void displayMenu()
```





























### function move

```cpp
bool move(
    int diff
)
```

move into menu for given diff pos ; return false if at end of menu 































## Public Attributes Documentation

### variable options

```cpp
LCDRotaryMenuOptions options;
```































## Friends

### friend LCDRotaryMenuItem

```cpp
friend class LCDRotaryMenuItem(
    LCDRotaryMenuItem 
);
```































-------------------------------


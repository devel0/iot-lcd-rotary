---
title: LCDRotaryMenuItem


---

# LCDRotaryMenuItem






`#include <lcd-rotary-menuitem.h>`















## Public Functions

|                | Name           |
| -------------- | -------------- |
|  | **[~LCDRotaryMenuItem](https://github.com/devel0/iot-utils/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md#function-~lcdrotarymenuitem)**()  |
| void | **[clear](https://github.com/devel0/iot-utils/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md#function-clear)**() <br>remove children  |
| [LCDRotaryMenuItem](https://github.com/devel0/iot-utils/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md) & | **[append](https://github.com/devel0/iot-utils/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md#function-append)**(String menuText, int tag =-1, void * custom =NULL) <br>append new child ( deallocation automatic )  |
| [LCDRotaryMenuItem](https://github.com/devel0/iot-utils/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md) * | **[getParent](https://github.com/devel0/iot-utils/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md#function-getparent)**()  |
| void | **[setText](https://github.com/devel0/iot-utils/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md#function-settext)**(String menuText)  |
| void | **[onSelect](https://github.com/devel0/iot-utils/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md#function-onselect)**([LCDRotaryMenuItemCB](https://github.com/devel0/iot-utils/tree/main/data/api/Files/lcd-rotary-menuitem_8h.md#typedef-lcdrotarymenuitemcb) cb) <br>set callback on select this item  |
| void | **[onSelect](https://github.com/devel0/iot-utils/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md#function-onselect)**(void(*)() cb)  |
| void | **[select](https://github.com/devel0/iot-utils/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md#function-select)**() <br>enter this menuitem (if children) selecting last child of it selected or first if never entered before  |
| void | **[back](https://github.com/devel0/iot-utils/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md#function-back)**() <br>exit this menu and go back  |
| const String & | **[getText](https://github.com/devel0/iot-utils/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md#function-gettext)**() const  |
| int | **[getTag](https://github.com/devel0/iot-utils/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md#function-gettag)**() const <br>retrieve user tag associated to this menuitem ( useful when manage with single callback that switch on menuitem tag )  |
| void * | **[getCustom](https://github.com/devel0/iot-utils/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md#function-getcustom)**()  |
| bool | **[isDisplayed](https://github.com/devel0/iot-utils/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md#function-isdisplayed)**() const  |






## Friends

|                | Name           |
| -------------- | -------------- |
| class | **[LCDRotaryMenu](https://github.com/devel0/iot-utils/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md#friend-lcdrotarymenu)**  |















## Public Functions Documentation

### function ~LCDRotaryMenuItem

```cpp
~LCDRotaryMenuItem()
```





























### function clear

```cpp
void clear()
```

remove children 




























### function append

```cpp
LCDRotaryMenuItem & append(
    String menuText,
    int tag =-1,
    void * custom =NULL
)
```

append new child ( deallocation automatic ) 

**Parameters**: 

  * **menuText** text for the item 
  * **tag** optional user tag useful to manage callback with switch type 
  * **custom** void * custom ptr 




























### function getParent

```cpp
LCDRotaryMenuItem * getParent()
```





























### function setText

```cpp
void setText(
    String menuText
)
```





























### function onSelect

```cpp
void onSelect(
    LCDRotaryMenuItemCB cb
)
```

set callback on select this item 




























### function onSelect

```cpp
void onSelect(
    void(*)() cb
)
```





























### function select

```cpp
void select()
```

enter this menuitem (if children) selecting last child of it selected or first if never entered before 




























### function back

```cpp
void back()
```

exit this menu and go back 




























### function getText

```cpp
const String & getText() const
```





























### function getTag

```cpp
int getTag() const
```

retrieve user tag associated to this menuitem ( useful when manage with single callback that switch on menuitem tag ) 







**Return**: int 





















### function getCustom

```cpp
void * getCustom()
```





























### function isDisplayed

```cpp
bool isDisplayed() const
```



































## Friends

### friend LCDRotaryMenu

```cpp
friend class LCDRotaryMenu;
```































-------------------------------


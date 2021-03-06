---
title: LCDRotaryMenuItem


---

# LCDRotaryMenuItem






`#include <lcd-rotary-menuitem.h>`















## Public Functions

|                | Name           |
| -------------- | -------------- |
|  | **[~LCDRotaryMenuItem](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md#function-~lcdrotarymenuitem)**()  |
| void | **[clear](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md#function-clear)**() <br>remove children  |
| [LCDRotaryMenuItem](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md) & | **[append](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md#function-append)**(string prefixText, string menuText, int tag =-1, void * custom =NULL) <br>append new child ( deallocation automatic )  |
| [LCDRotaryMenuItem](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md) & | **[append](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md#function-append)**(string menuText, int tag =-1, void * custom =NULL) <br>append new child ( deallocation automatic )  |
| [LCDRotaryMenuItem](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md) & | **[appendAfter](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md#function-appendafter)**([LCDRotaryMenuItem](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md) & before, string menuText, int tag =-1, void * custom =NULL) <br>append new child ( deallocation automatic )  |
| bool | **[remove](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md#function-remove)**([LCDRotaryMenuItem](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md) * child) <br>remove given child ( MUST delete manually resource for [LCDRotaryMenuItem](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md) ) if true returned  |
| [LCDRotaryMenuItem](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md) * | **[getParent](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md#function-getparent)**() <br>parent of this menu item  |
| [LCDRotaryMenuItem](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md) * | **[getSelectedChild](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md#function-getselectedchild)**() <br>currently selected menu item child  |
| void | **[setSelectedChild](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md#function-setselectedchild)**([LCDRotaryMenuItem](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md) * child) <br>change currently selected menu item child  |
| vector< [LCDRotaryMenuItem](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md) * > & | **[getChildren](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md#function-getchildren)**() <br>retrieve list of children menu items  |
| void | **[setText](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md#function-settext)**(string menuText) <br>change menu item text ( value )  |
| void | **[setPrefix](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md#function-setprefix)**(string menuPrefixText) <br>change menu item prefix ( useful for numeric or multiselect types )  |
| const char * | **[getText](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md#function-gettext)**() const <br>retrieve menu item text ( value )  |
| const char * | **[getPrefix](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md#function-getprefix)**() const <br>retrieve menu item prefix  |
| void | **[onSelect](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md#function-onselect)**([LCDRotaryMenuItemCB](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Files/lcd-rotary-menuitem_8h.md#typedef-lcdrotarymenuitemcb) cb) <br>set callback on select this item  |
| void | **[select](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md#function-select)**() <br>enter this menuitem (if children) selecting last child of it selected or first if never entered before it also apply onSelect callback action  |
| void | **[back](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md#function-back)**() <br>exit this menu and go back  |
| int | **[getTag](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md#function-gettag)**() const <br>retrieve user tag associated to this menuitem ( useful when manage with single callback that switch on menuitem tag )  |
| void * | **[getCustom](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md#function-getcustom)**()  |
| bool | **[isDisplayed](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md#function-isdisplayed)**() const  |
| void | **[setMode](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md#function-setmode)**([LCDRotaryMenuItemModeEnum](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Files/lcd-rotary-menuitem_8h.md#enum-lcdrotarymenuitemmodeenum) newMode)  |
| void | **[setTextMaskCharset](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md#function-settextmaskcharset)**(const char * textMask)  |
| [LCDRotaryMenuItemModeEnum](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Files/lcd-rotary-menuitem_8h.md#enum-lcdrotarymenuitemmodeenum) | **[getMode](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md#function-getmode)**() const  |
| void | **[setScrollRowPos](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md#function-setscrollrowpos)**(int scrollRow) <br>set the given row as the toplevel of the lcd  |
| int | **[getScrollRowPos](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md#function-getscrollrowpos)**() const  |
| bool | **[isBack](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md#function-isback)**() const  |
| bool | **[isEditing](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md#function-isediting)**() const  |
| bool | **[isEditingCol](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md#function-iseditingcol)**() const  |
| bool | **[isCollapsed](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md#function-iscollapsed)**() const  |
| bool | **[getMultiRollOver](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md#function-getmultirollover)**() const  |
| void | **[setIsEditing](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md#function-setisediting)**(bool val)  |
| void | **[setIsEditingCol](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md#function-setiseditingcol)**(bool val)  |
| void | **[setIsCollapsed](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md#function-setiscollapsed)**(bool collapsed)  |
| void | **[setMultiRollOver](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md#function-setmultirollover)**(bool rollOver) <br>if true, for multiselect menuitem type, when rotary reach end or begin of the list restarts from other side  |






## Friends

|                | Name           |
| -------------- | -------------- |
| class | **[LCDRotaryMenu](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md#friend-lcdrotarymenu)**  |















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
    string prefixText,
    string menuText,
    int tag =-1,
    void * custom =NULL
)
```

append new child ( deallocation automatic ) 

**Parameters**: 

  * **prefixText** prefix text for the item 
  * **menuText** text for the item 
  * **tag** optional user tag useful to manage callback with switch type 
  * **custom** void * custom ptr 




























### function append

```cpp
LCDRotaryMenuItem & append(
    string menuText,
    int tag =-1,
    void * custom =NULL
)
```

append new child ( deallocation automatic ) 

**Parameters**: 

  * **menuText** text for the item 
  * **tag** optional user tag useful to manage callback with switch type 
  * **custom** void * custom ptr 




























### function appendAfter

```cpp
LCDRotaryMenuItem & appendAfter(
    LCDRotaryMenuItem & before,
    string menuText,
    int tag =-1,
    void * custom =NULL
)
```

append new child ( deallocation automatic ) 

**Parameters**: 

  * **menuText** text for the item 
  * **tag** optional user tag useful to manage callback with switch type 
  * **custom** void * custom ptr 




























### function remove

```cpp
bool remove(
    LCDRotaryMenuItem * child
)
```

remove given child ( MUST delete manually resource for [LCDRotaryMenuItem](https://github.com/devel0/iot-lcd-rotary/tree/main/data/api/Classes/class_l_c_d_rotary_menu_item.md) ) if true returned 







**Return**: false if not found 





















### function getParent

```cpp
LCDRotaryMenuItem * getParent()
```

parent of this menu item 




























### function getSelectedChild

```cpp
LCDRotaryMenuItem * getSelectedChild()
```

currently selected menu item child 




























### function setSelectedChild

```cpp
void setSelectedChild(
    LCDRotaryMenuItem * child
)
```

change currently selected menu item child 




























### function getChildren

```cpp
vector< LCDRotaryMenuItem * > & getChildren()
```

retrieve list of children menu items 




























### function setText

```cpp
void setText(
    string menuText
)
```

change menu item text ( value ) 




























### function setPrefix

```cpp
void setPrefix(
    string menuPrefixText
)
```

change menu item prefix ( useful for numeric or multiselect types ) 




























### function getText

```cpp
const char * getText() const
```

retrieve menu item text ( value ) 




























### function getPrefix

```cpp
const char * getPrefix() const
```

retrieve menu item prefix 




























### function onSelect

```cpp
void onSelect(
    LCDRotaryMenuItemCB cb
)
```

set callback on select this item 




























### function select

```cpp
void select()
```

enter this menuitem (if children) selecting last child of it selected or first if never entered before it also apply onSelect callback action 




























### function back

```cpp
void back()
```

exit this menu and go back 




























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





























### function setMode

```cpp
void setMode(
    LCDRotaryMenuItemModeEnum newMode
)
```





























### function setTextMaskCharset

```cpp
void setTextMaskCharset(
    const char * textMask
)
```





























### function getMode

```cpp
LCDRotaryMenuItemModeEnum getMode() const
```





























### function setScrollRowPos

```cpp
void setScrollRowPos(
    int scrollRow
)
```

set the given row as the toplevel of the lcd 




























### function getScrollRowPos

```cpp
inline int getScrollRowPos() const
```





























### function isBack

```cpp
inline bool isBack() const
```





























### function isEditing

```cpp
inline bool isEditing() const
```





























### function isEditingCol

```cpp
inline bool isEditingCol() const
```





























### function isCollapsed

```cpp
inline bool isCollapsed() const
```





























### function getMultiRollOver

```cpp
inline bool getMultiRollOver() const
```





























### function setIsEditing

```cpp
void setIsEditing(
    bool val
)
```





























### function setIsEditingCol

```cpp
void setIsEditingCol(
    bool val
)
```





























### function setIsCollapsed

```cpp
void setIsCollapsed(
    bool collapsed
)
```





























### function setMultiRollOver

```cpp
void setMultiRollOver(
    bool rollOver
)
```

if true, for multiselect menuitem type, when rotary reach end or begin of the list restarts from other side 


































## Friends

### friend LCDRotaryMenu

```cpp
friend class LCDRotaryMenu(
    LCDRotaryMenu 
);
```































-------------------------------


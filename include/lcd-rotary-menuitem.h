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
    MI_NumericInput,
    MI_TextInput
};

class LCDRotaryMenuItem
{
    friend class LCDRotaryMenu;

    /**
     * @brief reference to menu manager
     */
    LCDRotaryMenu &menu;

    /**
     * @brief null if this menu is the root
     */
    LCDRotaryMenuItem *parent;

    LCDRotaryMenuItem(LCDRotaryMenu &menu, LCDRotaryMenuItem *parent, int tag = -1, void *custom = NULL);

    vector<LCDRotaryMenuItem *> children;

    /**
     * @brief text or value
     */
    string text;

    /**
     * @brief prefix ( useful for numeric or multiselect prompt )
     */
    string prefix;

    /**
     * @brief children scroll row
     */
    int scrollRowPos;

    /**
     * @brief currently selected child
     */
    LCDRotaryMenuItem *selectedChild;

    /**
     * @brief callback when select this menuitem
     */
    LCDRotaryMenuItemCB selectCb = NULL;

    /**
     * @brief callback when select this menuitem ( argument less )
     */
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

    const char *textMaskCharset = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

public:
    ~LCDRotaryMenuItem();

    /**
     * @brief remove children
     */
    void clear();

    /**
     * @brief append new child ( deallocation automatic )
     *
     * @param prefixText prefix text for the item
     * @param menuText text for the item
     * @param tag optional user tag useful to manage callback with switch type
     * @param custom void * custom ptr
     */
    LCDRotaryMenuItem &append(string prefixText, string menuText, int tag = -1, void *custom = NULL);

    /**
     * @brief append new child ( deallocation automatic )
     *     
     * @param menuText text for the item
     * @param tag optional user tag useful to manage callback with switch type
     * @param custom void * custom ptr
     */
    LCDRotaryMenuItem &append(string menuText, int tag = -1, void *custom = NULL);

    /**
     * @brief append new child ( deallocation automatic )
     *
     * @param menuText text for the item
     * @param tag optional user tag useful to manage callback with switch type
     * @param custom void * custom ptr
     */
    LCDRotaryMenuItem &appendAfter(LCDRotaryMenuItem &before, string menuText, int tag = -1, void *custom = NULL);

    /**
     * @brief remove given child ( MUST delete manually resource for LCDRotaryMenuItem ) if true returned
     *
     * @return false if not found
     */
    bool remove(LCDRotaryMenuItem *child);

    /**
     * @brief parent of this menu item
     */
    LCDRotaryMenuItem *getParent();

    /**
     * @brief currently selected menu item child
     */
    LCDRotaryMenuItem *getSelectedChild();

    /**
     * @brief change currently selected menu item child
     */
    void setSelectedChild(LCDRotaryMenuItem *child);

    /**
     * @brief retrieve list of children menu items
     */
    vector<LCDRotaryMenuItem *> getChildren();

    /**
     * @brief change menu item text ( value )
     */
    void setText(string menuText);

    /**
     * @brief change menu item prefix ( useful for numeric or multiselect types )
     */
    void setPrefix(string menuPrefixText);

    /**
     * @brief retrieve menu item text ( value )
     */
    const string &getText() const;

    /**
     * @brief retrieve menu item prefix
     */
    const string &getPrefix() const;

    /**
     * @brief set callback on select this item
     */
    void onSelect(LCDRotaryMenuItemCB cb);

    void onSelect(void (*cb)());    

    /**
     * @brief enter this menuitem (if children) selecting last child of it selected or first if never entered before
     * it also apply onSelect callback action
     */
    void select();

    /**
     * @brief exit this menu and go back
     */
    void back();

    /**
     * @brief retrieve user tag associated to this menuitem ( useful when manage with single callback that switch on menuitem tag )
     *
     * @return int
     */
    int getTag() const;

    void *getCustom();

    bool isDisplayed() const;

    void setMode(LCDRotaryMenuItemModeEnum newMode);

    void setTextMaskCharset(const char *textMask);

    /**
     * @brief if true, for multiselect menuitem type, when rotary reach end or begin of the list restarts from other side
     */
    void setMultiRollOver(bool rollOver);

    LCDRotaryMenuItemModeEnum getMode() const;

    /**
     * @brief set the given row as the toplevel of the lcd
     */
    void setScrollRowPos(int scrollRow);

    /**
     * @brief collapsed this menu item
     */
    void setCollapsed(bool collapsed);

    /**
     * @brief retrieve collapsed value of this menu item
     */
    bool getCollapsed() const;
};

#endif

#endif
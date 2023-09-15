#ifndef _LCD_ROTARY_MENUITEM_H
#define _LCD_ROTARY_MENUITEM_H

#ifdef ARDUINO

#include <Arduino.h>

#include <string>
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
    char *text = NULL;

    /**
     * @brief prefix ( useful for numeric or multiselect prompt )
     */
    char *prefix = NULL;

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
    vector<LCDRotaryMenuItem *> &getChildren();

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
    const char *getText() const;

    /**
     * @brief retrieve menu item prefix
     */
    const char *getPrefix() const;

    /**
     * @brief set callback on select this item
     */
    void onSelect(LCDRotaryMenuItemCB cb);

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

    LCDRotaryMenuItemModeEnum getMode() const;

    /**
     * @brief set the given row as the toplevel of the lcd
     */
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

    /**
     * @brief if true, for multiselect menuitem type, when rotary reach end or begin of the list restarts from other side
     */
    void setMultiRollOver(bool rollOver);
};

#endif

#endif
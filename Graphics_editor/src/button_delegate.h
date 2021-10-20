#ifndef BUTTON_DELEGATE
#define BUTTON_DELEGATE

class Button_delegate {
  public:
    virtual void click_reaction() = 0;
};

#include "view_manager.h"
enum class Mouse_click_state;
#endif
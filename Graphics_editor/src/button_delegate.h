#ifndef BUTTON_DELEGATE
#define BUTTON_DELEGATE

class Button_delegate {
  public:
    virtual void click_reaction(const double mouse_x, const double mouse_y)  = 0;
    virtual void motion_reaction(const double mouse_x, const double mouse_y) = 0;
};

#include "view_manager.h"
enum class Mouse_click_state;
#endif
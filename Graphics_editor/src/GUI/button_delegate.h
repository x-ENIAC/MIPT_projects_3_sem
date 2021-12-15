#include "../Utils/point.h"

#ifndef BUTTON_DELEGATE
#define BUTTON_DELEGATE

class Button_delegate {
  public:
	virtual void click_reaction(const double mouse_x, const double mouse_y)  = 0;
	virtual void motion_reaction(const double mouse_x, const double mouse_y) = 0;
	virtual void reactive_reaction(Point old_mouse, Point now_mouse) = 0;
};

#include "../Editor/view_manager.h"
enum class Mouse_click_state;

#include "animation_manager.h"
class Animation_manager;

// extern Animation_manager* anim_manager;

#endif
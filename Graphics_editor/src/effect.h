#include "GUI/view.h"

#ifndef EFFECT_H
#define EFFECT_H

class Effect : public View_object {
  public:

  	Effect() : View_object() {}

	virtual void apply() {
		printf("effect apply\n");
	}
};

#endif
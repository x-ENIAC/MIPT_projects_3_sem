
#ifndef WIDGET_TYPES_H
#define WIDGET_TYPES_H

enum class Widget_types {
	VIEW_OBJECT    = 0,
	VIEW_MANAGER   = 1,
	PALETTE		   = 2,
	CANVAS_MANAGER = 3,
	CANVAS 		   = 4,
	BUTTON_MANAGER = 5,
	BUTTON 		   = 6,
	TEXT		   = 7,
	TABS 		   = 8,
};

const size_t COUNT_OF_TYPES = 9;

#endif
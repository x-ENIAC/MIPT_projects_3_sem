
#ifndef WIDGET_TYPES_H
#define WIDGET_TYPES_H

enum class Widget_types {
	VIEW_OBJECT    			= 0,
	VIEW_MANAGER   			= 1,
	PALETTE		   			= 2,
	CANVAS_MANAGER_MANAGER  = 3,
	CANVAS_MANAGER 			= 4,
	CANVAS 		   			= 5,
	BUTTON_MANAGER 			= 6,
	BUTTON 		   			= 7,
	TEXT		   			= 8,
	TABS 		   			= 9,
	CHART					= 10,
	INTERPOLATION_CANVAS	= 11,
	INTERPOLATION_POINT		= 12
};

const size_t COUNT_OF_TYPES = 13;

#endif
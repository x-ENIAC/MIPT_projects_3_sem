#include "my_plagin.h"

void make_negative(Canvas* canvas) {
	printf("begin make negative %p\n", canvas);

	if(!canvas || !canvas->rect)
		return;

	//printf("beginnnnnnnnnnnnnnnnnnnnnnnn\n");
	int width  = canvas->rect->get_width();
	int height = canvas->rect->get_height();

	//printf("width %d, height %d\n", width, height);
	printf("point (10, 10) was (%lg, %lg, %lg) -> ", canvas->cells_color[10][10].get_color().red,
													 canvas->cells_color[10][10].get_color().green,
													 canvas->cells_color[10][10].get_color().blue);

	for(int i = 0; i <= width; ++i) {
		for(int j = 0; j <= height; ++j) {
			Colour now = canvas->cells_color[i][j].get_color();
			now *= -1;
			now += {255, 255, 255, 255};
			now.alpha = 255;

			canvas->cells_color[i][j].set_color(now);
		}
	}


	printf("(%lg, %lg, %lg)\n", canvas->cells_color[10][10].get_color().red,
								canvas->cells_color[10][10].get_color().green,
								canvas->cells_color[10][10].get_color().blue);
}
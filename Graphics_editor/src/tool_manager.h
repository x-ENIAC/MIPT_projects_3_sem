#ifndef TOOL_MANAGER_H
#define TOOL_MANAGER_H

class Tool_manager : public View_object {
  public:
  	
  	Tool** tools;
  	size_t count_of_tools;

  	Tool* active_tool;

	Tool_manager(const Point par_center, const double par_width, const double par_height,
		 const Colour par_color, const Widget_types par_widget_types = Widget_types::VIEW_OBJECT,
		 const char par_path_to_picture[] = NON_PATH_TO_PUCTURE) :
	  View_object(par_center, par_width, par_height, par_color, par_widget_types, par_path_to_picture) {

	  	tools = new Tool*[MAX_COUNT_OF_VIEW_OBJECTS];
	  	for(int i = 0; i < MAX_COUNT_OF_VIEW_OBJECTS; ++i)
	  		tools[i] = new Tool;
	  	count_of_tools = 0;

	  	active_tool = new Tool;
	}

	void draw(SDL_Renderer** render, SDL_Texture** texture, SDL_Surface** screen) override {
		rect->draw(*render);

		Point center = rect->get_left_up_corner();
		center += Point(50, 50);

		for(size_t i = 0; i < count_of_tools; ++i) {
			tools[i]->draw(render, texture, screen);
			center += Point(0, 20);
		}
	}

	bool check_click(const double mouse_x, const double mouse_y, const Mouse_click_state* par_mouse_status) override {

		if(rect->is_point_belongs_to_rectangle(mouse_x, mouse_y)) {
			//printf("!!\n");
			for(size_t i = 0; i < count_of_tools; ++i) {

				if(tools[i]->rect->is_point_belongs_to_rectangle( Point(mouse_x, mouse_y) )) {
					if(*par_mouse_status == Mouse_click_state::MOUSE_DOWN) {
						if(tools[i]->check_click(mouse_x, mouse_y, par_mouse_status)) {
							active_tool = tools[i];
							return true;
						}
					}

					return true;
				}
			}
		}

		//printf("return false Button_manager\n");

		return false;
	}

	void add_tool(Tool* new_tool) {
		Point center = rect->get_left_up_corner();
		if(count_of_tools > 0) {
			center = tools[count_of_tools]->rect->get_center();
		} else {
			center += Point(30, 0);
		}

		center += Point(0, 30);
		new_tool->rect->set_center(center);
		tools[count_of_tools] = new_tool;
		++count_of_tools;

		++widget_types[new_tool->get_yourself_type()];
	}

};

#endif
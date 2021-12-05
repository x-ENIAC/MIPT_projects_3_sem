#include <dlfcn.h>
#include "plugin_interface.h"

#ifndef PLUGIN_TOOL_H
#define PLUGIN_TOOL_H

class Plugin_tool: public Tool {
  public:

  	//PAppInterface* app_interface;
  	void* library;
  	PPluginInterface* pl_interface;

	Plugin_tool(const char* file_name, const PAppInterface* app_interface) {

		library = dlopen(file_name, RTLD_NOW);
		if(library == NULL) {
			printf("error dlopen\n");
			return;
		}

		PPluginInterface* (*PIFunc)() get_plugin_interface = dlsym(library, PGET_INTERFACE_FUNC);
		if(!get_plugin_interface) {
			printf("error dlsym\n");
			return;
		}

		pl_interface = get_plugin_interface();

		PPluginStatus status = PPluginInterface->general.init(app_interface);
		if(status != PPS_OK) {
			printf("error init\n");
			return;
		}
	}
};

#endif
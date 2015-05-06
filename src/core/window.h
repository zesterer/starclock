#ifndef STARCLOCK_CORE_WINDOW_H
#define STARCLOCK_CORE_WINDOW_H

//----STANDARD----
#include "string"

//----LIBRARY----
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

using namespace std;

namespace Starclock
{
	namespace Core
	{
		class Window
		{
			public: unsigned int width = 640 * 1.5;
			public: unsigned int height = 480 * 1.5;
			public: string window_title = "Starclock";

			public: GLFWwindow* glfw_window;

			public: Window();
			public: ~Window();
			public: bool refresh();
			public: void activate();
		};
	}
}

#endif // STARCLOCK_CORE_WINDOW_H

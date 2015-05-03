//----LOCAL----
#include "window.h"
#include "../common/out.h"

namespace Starclock
{
	namespace Core
	{
		Window::Window()
		{
			Common::Out::put("Creating Window");

			//Start up GLFW
			Common::Out::test(glfwInit(), "Initialising GLFW", true);

			//Create the window
			Common::Out::test((this->glfw_window = glfwCreateWindow(this->width, this->height, this->window_title.c_str(), NULL, NULL)), "Creating window", true);
		}

		void Window::activate()
		{
			Common::Out::put("Activating Window");

			glfwMakeContextCurrent(this->glfw_window);
		}

		Window::~Window()
		{
			glfwDestroyWindow(this->glfw_window);

			glfwTerminate();

			Common::Out::put("Closing Window");
		}

		bool Window::run()
		{
			//Render here

			glfwSwapBuffers(this->glfw_window);

			glfwPollEvents();

			return !glfwWindowShouldClose(this->glfw_window);
		}
	}
}

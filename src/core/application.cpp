//----STANDARD----
#include "string"

//----LIBRARY----
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

//----LOCAL----
#include "application.h"
#include "../common/out.h"
#include "../render/scene.h"

namespace Starclock
{
	namespace Core
	{
		Application::Application(int argc, char* argv[])
		{
			Common::Out::put("Creating Application");

			//Place the program arguments into a more manageable form
			for (int count = 0; count < argc; count ++)
				this->args.push_back((string)argv[count]);

			//Create the window
			this->window = new Window();
			this->window->activate();

			//Create the scene
			this->scene = new Render::Scene();
		}

		void Application::run()
		{
			Common::Out::put("Running Application");

			//The game loop
			while (this->running)
			{
				///*Testing - Check keyboard
				if (glfwGetKey(this->window->glfw_window, GLFW_KEY_D) == GLFW_PRESS)
					this->scene->camera->position.x += 0.05;
				if (glfwGetKey(this->window->glfw_window, GLFW_KEY_A) == GLFW_PRESS)
					this->scene->camera->position.x -= 0.05;
				if (glfwGetKey(this->window->glfw_window, GLFW_KEY_W) == GLFW_PRESS)
					this->scene->camera->position.y += 0.05;
				if (glfwGetKey(this->window->glfw_window, GLFW_KEY_S) == GLFW_PRESS)
					this->scene->camera->position.y -= 0.05;
				if (glfwGetKey(this->window->glfw_window, GLFW_KEY_RIGHT) == GLFW_PRESS)
					this->scene->camera->rotation.x += 0.02;
				if (glfwGetKey(this->window->glfw_window, GLFW_KEY_LEFT) == GLFW_PRESS)
					this->scene->camera->rotation.x -= 0.02;
				if (glfwGetKey(this->window->glfw_window, GLFW_KEY_UP) == GLFW_PRESS)
					this->scene->camera->rotation.y += 0.02;
				if (glfwGetKey(this->window->glfw_window, GLFW_KEY_DOWN) == GLFW_PRESS)
					this->scene->camera->rotation.y -= 0.02;
				//*/

				//Render the scene
				this->scene->render();

				//Refresh the window
				this->running = this->window->refresh();
			}
		}
	}
}

//----STANDARD----
#include "string"

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
				//Render the scene
				this->scene->render();

				//Refresh the window
				this->running = this->window->refresh();
			}
		}
	}
}

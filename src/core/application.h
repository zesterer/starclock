#ifndef STARCLOCK_CORE_APPLICATION_H
#define STARCLOCK_CORE_APPLICATION_H

//----STANDARD----
#include "vector"
#include "string"

//----LOCAL----
#include "window.h"
#include "../render/scene.h"

using namespace std;

namespace Starclock
{
	namespace Core
	{
		class Application
		{
			public: vector<string> args;

			public: bool running = true; //Run until told otherwise

			public: Window* window;
			public: Render::Scene* scene;

			public: Application(int argc, char* argv[]);
			public: void run();
		};
	}
}

#endif // STARCLOCK_CORE_APPLICATION_H

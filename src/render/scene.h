#ifndef STARCLOCK_RENDER_SCENE_H
#define STARCLOCK_RENDER_SCENE_H

//----STANDARD----
#include "list"

//----LOCAL----
#include "camera.h"
#include "entity.h"

using namespace std;

namespace Starclock
{
	namespace Render
	{
		class Scene
		{
			public: Camera* camera;
			public: list<Entity> entities;

			public: Scene();
			public: void update();
			public: void render();
		};
	}
}

#endif // STARCLOCK_RENDER_SCENE_H

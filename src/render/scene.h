#ifndef STARCLOCK_RENDER_SCENE_H
#define STARCLOCK_RENDER_SCENE_H

//----LOCAL----
#include "camera.h"

namespace Starclock
{
	namespace Render
	{
		class Scene
		{
			public: Camera* camera;

			public: Scene();
			public: void update();
			public: void render();
		};
	}
}

#endif // STARCLOCK_RENDER_SCENE_H

#ifndef STARCLOCK_RENDER_ENTITY_H
#define STARCLOCK_RENDER_ENTITY_H

//----STANDARD----
#include "string"

//----LIBRARY----
#include "glm/glm.hpp"
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"

#include "glbinding/gl/gl.h"
#include "glbinding/Binding.h"

using namespace std;
using namespace gl;

namespace Starclock
{
	namespace Render
	{
		class Scene; //Definition here for use above (to avoid include loop)

		class Entity
		{
			public: glm::vec3 position;
			public: glm::vec3 scale;
			public: glm::vec3 rotation;

			public: glm::mat4 matrix;

			public: Scene* scene;
			public: string model_id;

			public: Entity(Scene* scene);
			public: void update();
			public: void setModel(string model_id);
		};
	}
}

#endif // STARCLOCK_RENDER_ENTITY_H

#ifndef STARCLOCK_RENDER_ENTITY_H
#define STARCLOCK_RENDER_ENTITY_H

//----LIBRARY----
#include "glm/glm.hpp"
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"

#include "glbinding/gl/gl.h"
#include "glbinding/Binding.h"

using namespace gl;

namespace Starclock
{
	namespace Render
	{
		class Entity
		{
			public: glm::vec3 position;
			public: glm::vec3 rotation;

			public: char model_id[8];
			public: char texture_id[8];
		};
	}
}

#endif // STARCLOCK_RENDER_ENTITY_H

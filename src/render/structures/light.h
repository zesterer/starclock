#ifndef STARCLOCK_RENDER_STRUCTURES_LIGHT_H
#define STARCLOCK_RENDER_STRUCTURES_LIGHT_H

//----LIBRARY----
#include "glbinding/gl/gl.h"
#include "glbinding/Binding.h"

#include "glm/glm.hpp"
#include "glm/vec3.hpp"

using namespace gl;

namespace Starclock
{
	namespace Render
	{
		namespace Structures
		{
			enum LightType
			{
				DIRECTIONAL,
				POINT
			};

			struct Light
			{
				public: LightType type;
				public: glm::vec3 position;
				public: glm::vec3 colour;
				public: GLfloat ambiance;
			};
		}
	}
}

#endif // STARCLOCK_RENDER_STRUCTURES_LIGHT_H

#ifndef STARCLOCK_RENDER_STRUCTURES_GEOMETRY_H
#define STARCLOCK_RENDER_STRUCTURES_GEOMETRY_H

//----LIBRARY----
#include "glbinding/gl/gl.h"
#include "glbinding/Binding.h"

#include "glm/glm.hpp"
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"

using namespace gl;

namespace Starclock
{
	namespace Render
	{
		namespace Structures
		{
			struct Vertex
			{
				glm::vec3 pos;
				glm::vec3 col;
				glm::vec2 tex;
				glm::vec3 norm;
			};

			struct Polygon
			{
				Vertex a, b, c;
			};
		}
	}
}

#endif // STARCLOCK_RENDER_STRUCTURES_GEOMETRY_H

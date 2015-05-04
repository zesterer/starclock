#ifndef STARCLOCK_RENDER_STRUCTURES_SHADERS_H
#define STARCLOCK_RENDER_STRUCTURES_SHADERS_H

//----STANDARD----
#include "string"

//----LIBRARY----
#include "glbinding/gl/gl.h"
#include "glbinding/Binding.h"

using namespace std;
using namespace gl;

namespace Starclock
{
	namespace Render
	{
		class Scene; //Definition here for use above (to avoid include loop)

		namespace Structures
		{
			class Shaders
			{
				public: Scene* scene;

				public: GLuint gl_id;
				public: string id;

				public: Shaders(Scene* scene, string id);
				public: void loadFromFiles(const char * vertex_file_path, const char * fragment_file_path);
			};
		}
	}
}

#endif // STARCLOCK_RENDER_STRUCTURES_SHADERS_H

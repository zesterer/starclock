#ifndef STARCLOCK_RENDER_STRUCTURES_TEXTURE_H
#define STARCLOCK_RENDER_STRUCTURES_TEXTURE_H

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
			class Texture
			{
				public: string id;
				public: Scene* scene;

				public: GLuint gl_id;
				public: unsigned int width, height;
				public: unsigned char* file_data;
				public: unsigned int data_pos; //The data position within the file data
				public: bool clear_on_buffer = true;

				public: Texture(Scene* scene, string id);
				public: bool loadFromBMP(string filename);
				public: void buffer();
			};
		}
	}
}

#endif // STARCLOCK_RENDER_STRUCTURES_TEXTURE_H

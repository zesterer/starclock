#ifndef STARCLOCK_RENDER_STRUCTURES_MESH_H
#define STARCLOCK_RENDER_STRUCTURES_MESH_H

//----STANDARD----
#include "vector"
#include "string"

//----LIBRARY----
#include "glbinding/gl/gl.h"
#include "glbinding/Binding.h"

//----LOCAL----
#include "geometry.h"

using namespace std;
using namespace gl;

namespace Starclock
{
	namespace Render
	{
		class Scene; //Definition here for use above (to avoid include loop)

		namespace Structures
		{
            class Mesh
            {
            	public: string id;
            	public: Scene* scene;

				public: GLuint gl_id;
				public: GLuint polygon_number;

            	public: vector<Polygon> polygons;
            	public: bool clear_on_buffer = true;

				public: Mesh(Scene* scene, string id);
            	public: bool loadFromOBJ(string filename);
            	public: void buffer();
            };
		}
	}
}

#endif // STARCLOCK_RENDER_STRUCTURES_MESH_H

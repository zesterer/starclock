#ifndef STARCLOCK_RENDER_STRUCTURES_MESH_H
#define STARCLOCK_RENDER_STRUCTURES_MESH_H

//----STANDARD----
#include "vector"
#include "string"

//----LIBRARY----
#include "glbinding/gl/gl.h"
#include "glbinding/Binding.h"

#include "glm/glm.hpp"
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/detail/func_geometric.hpp"

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
				public: GLenum render_mode = GL_TRIANGLES;

            	public: vector<Polygon> polygons;
            	public: bool clear_on_buffer = true;

				public: Mesh(Scene* scene, string id);
            	public: bool loadFromOBJ(string filename);
            	public: void addMesh(Mesh* mesh, glm::mat4x4 matrix);
            	public: void buffer();
            };

            struct Face
            {
            	unsigned int a_pos, a_col, a_tex, a_norm;
            	unsigned int b_pos, b_col, b_tex, b_norm;
            	unsigned int c_pos, c_col, c_tex, c_norm;

            	unsigned char has_parts;
            };
		}
	}
}

#endif // STARCLOCK_RENDER_STRUCTURES_MESH_H

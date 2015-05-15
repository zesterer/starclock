#ifndef STARCLOCK_RENDER_STRUCTURES_MODEL_H
#define STARCLOCK_RENDER_STRUCTURES_MODEL_H

//----STANDARD----
#include "string"

//----LIBRARY----
#include "glbinding/gl/gl.h"
#include "glbinding/Binding.h"

//----LOCAL----
#include "mesh.h"
#include "texture.h"

using namespace std;

namespace Starclock
{
	namespace Render
	{
		class Scene; //Definition here for use above (to avoid include loop)

		namespace Structures
		{
			class Model
			{
				public: string id;
				public: Scene* scene;
				public: bool buffered = false;

				public: string mesh_id;
				public: string texture_id;
				public: string shaders_id;
				public: string material_id;

				public: Model(Scene* scene, string id);
				public: bool setMesh(string mesh_id);
				public: bool setTexture(string texture_id);
				public: bool setShaders(string shaders_id);
				public: bool setMaterial(string material_id);
				public: void buffer();
			};
		}
	}
}

#endif // STARCLOCK_RENDER_STRUCTURES_MODEL_H

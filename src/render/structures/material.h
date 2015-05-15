#ifndef STARCLOCK_RENDER_STRUCTURES_MATERIAL_H
#define STARCLOCK_RENDER_STRUCTURES_MATERIAL_H

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
			class Material
			{
                public: string id;
                public: Scene* scene;

                public: GLfloat shininess;
                public: GLfloat specular_amount;
                public: GLfloat specular_cap;
                public: GLint effects;

                public: Material(Scene* scene, string id);
                public: void setFromData(GLfloat shininess, GLfloat specular_amount, GLfloat specular_cap, GLint effects);
			};
		}
	}
}

#endif // STARCLOCK_RENDER_STRUCTURES_MATERIAL_H

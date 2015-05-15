//----LOCAL----
#include "material.h"

namespace Starclock
{
	namespace Render
	{
		namespace Structures
		{
			Material::Material(Scene* scene, string id)
			{
				this->scene = scene;
				this->id = id;
			}

			void Material::setFromData(GLfloat shininess, GLfloat specular_amount, GLfloat specular_cap, GLint effects)
			{
				this->shininess = shininess;
				this->specular_amount = specular_amount;
				this->specular_cap = specular_cap;
				this->effects = effects;
			}
		}
	}
}

//----STANDARD----
#include "string"

//----LIBRARY----
#include "glm/glm.hpp"
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"

//----LOCAL----
#include "entity.h"

using namespace std;

namespace Starclock
{
	namespace Render
	{
		Entity::Entity(Scene* scene)
		{
			this->scene = scene;

			this->position = glm::vec3(0.0, 10.0, 0.0);
			this->scale = glm::vec3(0.0005, 0.0005, 0.0005);
			this->rotation = glm::vec3(M_PI, -M_PI / 2, 0.0);
		}

		void Entity::setModel(string model_id)
		{
			this->model_id = model_id;
		}
	}
}

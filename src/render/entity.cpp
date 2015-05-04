//----STANDARD----
#include "string"

//----LIBRARY----
#include "glm/glm.hpp"
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"

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

			this->position = glm::vec3(0.0, 0.0, 0.0);
			this->scale = glm::vec3(1.0, 1.0, 1.0);
			this->rotation = glm::vec3(0.0, 0.0, 0.0);

			//Update the transformation matrix
			this->update();
		}

		void Entity::update()
		{
			//Clear the matrix ready to change it
			this->matrix = glm::mat4(1.0f);

			//Apply entity transformations
			this->matrix = glm::translate(this->matrix, this->position);
			this->matrix = glm::rotate(this->matrix, this->rotation.x, glm::vec3(0.0, 0.0, 1.0)); //Yaw
			this->matrix = glm::rotate(this->matrix, this->rotation.y, glm::vec3(1.0, 0.0, 0.0)); //Pitch
			this->matrix = glm::rotate(this->matrix, this->rotation.z, glm::vec3(0.0, 0.0, 1.0)); //Roll
			this->matrix = glm::scale(this->matrix, this->scale);
		}

		void Entity::setModel(string model_id)
		{
			this->model_id = model_id;
		}
	}
}

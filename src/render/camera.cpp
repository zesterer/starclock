//----LIBRARY----
#include "glm/glm.hpp"
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"

//----LOCAL----
#include "camera.h"

namespace Starclock
{
	namespace Render
	{
		Camera::Camera()
		{
			this->position = glm::vec3(0.0, 0.0, 0.0);
			this->rotation = glm::vec3(0.0, 0.0, 0.0);

			this->update();
		}

		void Camera::update()
		{
			//Clear the matrix ready for updating
			this->matrix = glm::mat4(1.0);

			//Apply the new transformations to it
			this->matrix = glm::rotate(this->matrix, this->rotation.z, glm::vec3(0.0, 0.0, 1.0)); //Roll
			this->matrix = glm::rotate(this->matrix, this->rotation.y - (float)M_PI / 2.0f, glm::vec3(1.0, 0.0, 0.0)); //Pitch
			this->matrix = glm::rotate(this->matrix, this->rotation.x, glm::vec3(0.0, 0.0, 1.0)); //Yaw
			this->matrix = glm::translate(this->matrix, glm::vec3(-this->position.x, -this->position.y, -this->position.z));
		}
	}
}

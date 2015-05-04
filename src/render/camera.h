#ifndef STARCLOCK_RENDER_CAMERA_H
#define STARCLOCK_RENDER_CAMERA_H

//----LIBRARY----
#include "glm/glm.hpp"
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"

namespace Starclock
{
	namespace Render
	{
		enum CameraMode
		{
			EULER,
			QUATERNION
		};

		class Camera
		{
			public: glm::vec3 position;
			public: glm::vec3 rotation;
			public: glm::mat4 matrix;

			public: CameraMode mode = CameraMode::EULER;
			public: float fov = 0.95;
			public: float min_render = 0.01;
			public: float max_render = 100;

			public: Camera();
			public: void update();
		};
	}
}

#endif // STARCLOCK_RENDER_CAMERA_H

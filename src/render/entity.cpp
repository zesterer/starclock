//----STANDARD----
#include "string"

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
		}

		void Entity::setModel(string model_id)
		{
			this->model_id = model_id;
		}
	}
}

//----STANDARD----
#include "string"

//----LOCAL----
#include "../scene.h"
#include "model.h"
#include "../../common/out.h"

using namespace std;

namespace Starclock
{
	namespace Render
	{
		namespace Structures
		{
			Model::Model(Scene* scene, string id)
			{
				this->scene = scene;
				this->id = id;
			}

			bool Model::setMesh(string mesh_id)
			{
				this->mesh_id = mesh_id;

				return true;
			}

			bool Model::setTexture(string texture_id)
			{
				this->texture_id = texture_id;

				return true;
			}

			bool Model::setShaders(string shaders_id)
			{
				this->shaders_id = shaders_id;

				return true;
			}

			bool Model::setMaterial(string material_id)
			{
				this->material_id = material_id;

				return true;
			}

			void Model::buffer()
			{
				if (this->scene != nullptr)
				{
					this->scene->getMesh(this->mesh_id)->buffer();
					this->scene->getTexture(this->texture_id)->buffer();

					//It's now buffered!
					this->buffered = true;
				}

				if (buffered)
					Common::Out::put("Buffered model with id '" + this->id + "'");
			}
		}
	}
}

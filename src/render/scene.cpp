//----STANDARD----
#include "string"
#include "map"

//----LIBRARY----
#include "glbinding/gl/gl.h"
#include "glbinding/Binding.h"

//----LOCAL----
#include "scene.h"
#include "../common/out.h"
#include "structures/model.h"
#include "structures/mesh.h"
#include "structures/texture.h"

using namespace std;
using namespace gl;

namespace Starclock
{
	namespace Render
	{
		Scene::Scene()
		{
			Common::Out::put("Creating Scene");

			//Initialise GLBinding
			Common::Out::put("Initialising GLbinding");
			glbinding::Binding::initialize();

			//Create the camera
			this->camera = new Camera();

			///* Testing
			this->addMeshFromOBJ("bowser", "../bowser.obj");
			this->addTextureFromBMP("bowser", "../bowser.bmp");
			Structures::Model* model = this->addModelFromMeshTexture("bowser", "bowser", "bowser");
			model->buffer();
			Entity entity(this);
			entity.setModel("bowser");
			this->entities.push_back(entity);
			//*/
		}

		Structures::Model* Scene::addModelFromMeshTexture(string id, string mesh_id, string texture_id)
		{
			Structures::Model model(this, id);
			model.setMesh(mesh_id);
			model.setTexture(texture_id);
			this->models.push_back(model);
			return &this->models.back();
		}

		Structures::Mesh* Scene::addMeshFromOBJ(string id, string filename)
		{
			Structures::Mesh mesh(this, id);
			mesh.loadFromOBJ(filename);
			this->meshes.push_back(mesh);
			return &this->meshes.back();
		}

		Structures::Texture* Scene::addTextureFromBMP(string id, string filename)
		{
			Structures::Texture texture(this, id);
			texture.loadFromBMP(filename);
			this->textures.push_back(texture);
			return &this->textures.back();
		}

		Structures::Model* Scene::getModel(string model_id) //THIS METHOD IS TEMPORARY - the pointer will break
		{
			for (unsigned long count = 0; count < this->models.size(); count ++)
			{
				if (this->models[count].id == model_id)
					return &this->models[count];
			}
			return nullptr;
		}

		Structures::Mesh* Scene::getMesh(string mesh_id) //THIS METHOD IS TEMPORARY - the pointer will break
		{
			for (unsigned long count = 0; count < this->meshes.size(); count ++)
			{
				if (this->meshes[count].id == mesh_id)
					return &this->meshes[count];
			}
			return nullptr;
		}

		Structures::Texture* Scene::getTexture(string texture_id) //THIS METHOD IS TEMPORARY - the pointer will break
		{
			for (unsigned long count = 0; count < this->textures.size(); count ++)
			{
				if (this->textures[count].id == texture_id)
					return &this->textures[count];
			}
			return nullptr;
		}

		void Scene::update()
		{
			//Update the camera logic
			this->camera->update();
		}

		void Scene::render()
		{
			//Before any rendering is done, update scene logic
			this->update();

			glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			//Render each entity
		}
	}
}

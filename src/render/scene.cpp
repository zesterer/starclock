//----STANDARD----
#include "string"
#include "map"

//----LIBRARY----
#include "glbinding/gl/gl.h"
#include "glbinding/Binding.h"

#include "glm/glm.hpp"
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"

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

			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LESS);

			//Create the camera
			this->camera = new Camera();

			///* Testing
			this->addMeshFromOBJ("bowser", "../bowser.obj");
			this->addTextureFromBMP("bowser", "../bowser.bmp");
			this->addShadersFromFiles("primary", "../shaders/primary_vertex_shader.glsl", "../shaders/primary_fragment_shader.glsl");
			Structures::Model* model = this->addModelFromMeshTexture("bowser", "bowser", "bowser", "primary");
			model->buffer();
			Entity entity(this);
			entity.setModel("bowser");
			this->entities.push_back(entity);
			//*/
		}

		Structures::Model* Scene::addModelFromMeshTexture(string id, string mesh_id, string texture_id, string shader_id)
		{
			Structures::Model model(this, id);
			model.setMesh(mesh_id);
			model.setTexture(texture_id);
			model.setShaders(shader_id);
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

		Structures::Shaders* Scene::addShadersFromFiles(string id, string vertex_shader_file, string fragment_shader_file)
		{
			Structures::Shaders shaders(this, id);
			shaders.loadFromFiles(vertex_shader_file.c_str(), fragment_shader_file.c_str());
			this->shaders.push_back(shaders);
			return &this->shaders.back();
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

		Structures::Shaders* Scene::getShaders(string shaders_id) //THIS METHOD IS TEMPORARY - the pointer will break
		{
			for (unsigned long count = 0; count < this->shaders.size(); count ++)
			{
				if (this->shaders[count].id == shaders_id)
					return &this->shaders[count];
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
			for (unsigned long count = 0; count < this->entities.size(); count ++)
			{
				//Find all the resources from the IDs
				Entity* entity = &this->entities[count];
				Structures::Model* model = this->getModel(entity->model_id);
				Structures::Mesh* mesh = this->getMesh(model->mesh_id);
				Structures::Texture* texture = this->getTexture(model->texture_id);
				Structures::Shaders* shaders = this->getShaders(model->shaders_id);

				//Bind the vertex buffer
				glBindBuffer(GL_ARRAY_BUFFER, mesh->gl_id);

				//Bind the texture buffer
				glBindTexture(GL_TEXTURE_2D, texture->gl_id);

				//Use the correct shaders program
				glUseProgram(shaders->gl_id);

				//Enable all the arrays
				long offset = 0;
				glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Structures::Vertex), (void*)offset);
				offset += sizeof(Structures::VertexPos);

				glEnableVertexAttribArray(1);
				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Structures::Vertex), (void*)offset);
				offset += sizeof(Structures::VertexCol);

				glEnableVertexAttribArray(2);
				glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Structures::Vertex), (void*)offset);
				offset += sizeof(Structures::VertexTex);

				glEnableVertexAttribArray(3);
				glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Structures::Vertex), (void*)offset);

				//Find the projection matrix
				glm::mat4 matrix = this->camera->matrix * entity->matrix;

				//Find the uniform MVP matrix, then assign it
				GLuint mvp_id = glGetUniformLocation(shaders->gl_id, "MVP");
				glUniformMatrix4fv(mvp_id, 1, GL_FALSE, &matrix[0][0]);

				//Draw the model
				glDrawArrays(GL_TRIANGLES, 0, mesh->polygon_number * 3);

				//Disable all the vertex attribute arrays again
				glDisableVertexAttribArray(0);
				glDisableVertexAttribArray(1);
				glDisableVertexAttribArray(2);
				glDisableVertexAttribArray(3);
			}
		}
	}
}

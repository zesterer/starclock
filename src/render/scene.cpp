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

			this->enable();

			//Create the camera
			this->camera = new Camera();

			///* Testing
			this->addShadersFromFiles("primary", "../shaders/primary_vertex_shader.glsl", "../shaders/primary_fragment_shader.glsl");

			this->addMeshFromOBJ("bowser", "../bowser.obj");
			this->addMeshFromOBJ("flower", "../flower.obj");
			this->addMeshFromOBJ("floor", "../floor.obj");
			this->addMeshFromOBJ("mickey", "../mickey.obj");
			this->addMeshFromOBJ("trooper", "../trooper.obj");
			this->addMeshFromOBJ("yoshi", "../yoshi.obj");
			this->addMeshFromOBJ("hog", "../chief.obj");

			this->addTextureFromBMP("bowser", "../bowser.bmp");
			this->addTextureFromBMP("fire", "../fire.bmp");
			this->addTextureFromBMP("grass", "../grass.bmp");
			this->addTextureFromBMP("mickey", "../mickey.bmp");
			this->addTextureFromBMP("trooper", "../trooper.bmp");
			this->addTextureFromBMP("yoshi", "../yoshi.bmp");
			this->addTextureFromBMP("hog", "../chief.bmp");

			this->addModelFromMeshTexture("bowser", "bowser", "bowser", "primary");
			this->addModelFromMeshTexture("flower", "flower", "fire", "primary");
			this->addModelFromMeshTexture("floor", "floor", "grass", "primary");
			this->addModelFromMeshTexture("mickey", "mickey", "mickey", "primary");
			this->addModelFromMeshTexture("trooper", "trooper", "trooper", "primary");
			this->addModelFromMeshTexture("yoshi", "yoshi", "yoshi", "primary");
			this->addModelFromMeshTexture("hog", "hog", "hog", "primary");

			auto bowser = this->addEntityWithModel("bowser");
			bowser->position = glm::vec3(0.0, 5.0, 0.0);
			bowser->scale = glm::vec3(0.0005, 0.0005, 0.0005);
			bowser->rotation = glm::vec3(M_PI / 5, M_PI / 2, 0.0);
			bowser->update();

			auto flower = this->addEntityWithModel("flower");
			flower->position = glm::vec3(-4.5, 4.0, 0.0);
			flower->scale = glm::vec3(0.01, 0.01, 0.01);
			flower->rotation = glm::vec3(M_PI / 12, M_PI / 2, 0.0);
			flower->update();

			auto floor = this->addEntityWithModel("floor");
			floor->position = glm::vec3(0.0, 0.0, 0.0);
			floor->scale = glm::vec3(20.0, 20.0, 20.0);
			floor->rotation = glm::vec3(0.0, M_PI / 2, 0.0);
			floor->update();

			auto mickey = this->addEntityWithModel("mickey");
			mickey->position = glm::vec3(5.0, 9.0, 0.0);
			mickey->scale = glm::vec3(0.4, 0.4, 0.4) * 1.0f;
			mickey->rotation = glm::vec3(-M_PI / 5, M_PI / 2, 0.0);
			mickey->update();

			for (int x = 0; x < 10; x ++)
			{
				for (int y = 0; y < 10; y ++)
				{
					mickey = this->addEntityWithModel("yoshi");
					mickey->position = glm::vec3(9.0 + 3.0 * (float)x, 9.0 + 3.0 * (float)y, 2.0);
					mickey->scale = glm::vec3(0.4, 0.4, 0.4) * 2.0f;
					mickey->rotation = glm::vec3(-M_PI / 5, M_PI / 2, 0.0);
					mickey->update();
				}
			}

			auto trooper = this->addEntityWithModel("trooper");
			trooper->position = glm::vec3(5.0, -9.0, 0.0);
			trooper->scale = glm::vec3(2.0, 2.0, 2.0) * 1.0f;
			trooper->rotation = glm::vec3(-M_PI / 5, M_PI / 2, 0.0);
			trooper->update();

			auto troopers = this->addEntityWithModel("yoshi");
			troopers->position = glm::vec3(-5.0, -4.0, 1.55);
			troopers->scale = glm::vec3(0.6, 0.6, 0.6) * 1.0f;
			troopers->rotation = glm::vec3(M_PI / 3, M_PI / 2, 0.0);
			troopers->update();

			auto troope = this->addEntityWithModel("hog");
			troope->position = glm::vec3(2.0, -4.0, 0.0);
			troope->scale = glm::vec3(0.6, 0.6, 0.6) * 8.0f;
			troope->rotation = glm::vec3(M_PI / 3, M_PI / 2, 0.0);
			troope->update();
			//*/
		}

		void Scene::enable()
		{
			Common::Out::put("Enabling Scene");

			//Enable backface culling
			glEnable(GL_CULL_FACE);

			//Enable the depth buffer
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LESS);
		}

		Entity* Scene::addEntityWithModel(string model_id)
		{
			Entity entity(this);
			entity.setModel(model_id);
			this->entities.push_back(entity);
			return &this->entities.back();
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
			//Increment the tick
			this->tick += 1;

			//Update the camera logic
			this->camera->update();
		}

		void Scene::render()
		{
			//Before any rendering is done, update scene logic
			this->update();

			glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			for (unsigned long count = 0; count < this->models.size(); count ++)
			{
				if (!this->models[count].buffered)
					this->models[count].buffer();
			}

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

				//What is the buffer array composed of?
				int length[] = {sizeof(Structures::VertexPos), sizeof(Structures::VertexCol), sizeof(Structures::VertexTex), sizeof(Structures::VertexNorm)};

				//Tell the shaders what different parts of the buffer mean using the above array
				GLuint offset = 0;
				for (int array_id = 0; array_id < 4; array_id ++)
				{
					glEnableVertexAttribArray(array_id);
					glVertexAttribPointer(array_id, length[array_id] / sizeof(GLfloat), GL_FLOAT, GL_FALSE, sizeof(Structures::Vertex), (void*)offset);
					offset += length[array_id];
				}

				//Find the uniform camera matrix, then assign it
				GLuint perspective_matrix_id = glGetUniformLocation(shaders->gl_id, "PERSPECTIVE_MATRIX");
				glUniformMatrix4fv(perspective_matrix_id, 1, GL_FALSE, &this->camera->perspective_matrix[0][0]);

				//Find the uniform camera matrix, then assign it
				GLuint camera_matrix_id = glGetUniformLocation(shaders->gl_id, "CAMERA_MATRIX");
				glUniformMatrix4fv(camera_matrix_id, 1, GL_FALSE, &this->camera->matrix[0][0]);

				//Find the uniform model vector, then assign it
				GLuint model_matrix_id = glGetUniformLocation(shaders->gl_id, "MODEL_MATRIX");
				glUniformMatrix4fv(model_matrix_id, 1, GL_FALSE, &entity->matrix[0][0]);

				//Find the uniform lighting vector, then assign it
				GLuint light_vector_id = glGetUniformLocation(shaders->gl_id, "LIGHT_VECTOR");
				glm::vec4 light_vector(sin((float)this->tick / 100), cos((float)this->tick / 100), -0.5, 0.25);
				light_vector = glm::vec4(1.0, 1.0, -0.5, 0.35);
				glUniform4fv(light_vector_id, 1, &light_vector[0]);

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

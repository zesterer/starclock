#ifndef STARCLOCK_RENDER_SCENE_H
#define STARCLOCK_RENDER_SCENE_H

//----STANDARD----
#include "list"
#include "vector"
#include "string"

//----LIBRARY----
#include "glbinding/gl/gl.h"
#include "glbinding/Binding.h"

//----LOCAL----
#include "camera.h"
#include "entity.h"
#include "structures/model.h"
#include "structures/mesh.h"
#include "structures/texture.h"
#include "structures/shaders.h"
#include "structures/material.h"
#include "structures/light.h"

using namespace std;
using namespace gl;

namespace Starclock
{
	namespace Render
	{
		class Scene
		{
			public: Camera* camera;
			public: GLuint tick = 0;

			public: vector<Entity> entities;
			public: vector<Structures::Model> models;
			public: vector<Structures::Mesh> meshes;
			public: vector<Structures::Texture> textures;
			public: vector<Structures::Shaders> shaders;
			public: vector<Structures::Material> materials;
			public: vector<Structures::Light> lights;

			public: Scene();
			public: void enable();
			public: void update();
			public: void render();
			public: Entity* addEntityWithModel(string model_id);
			public: Structures::Light* addLightWithData(Structures::LightType type, glm::vec3 position, glm::vec3 colour, GLfloat ambiance);
			public: Structures::Model* addModelFromParts(string id, string mesh_id, string texture_id, string shader_id, string material_id);
			public: Structures::Mesh* addMeshFromOBJ(string id, string filename);
			public: Structures::Texture* addTextureFromBMP(string id, string filename);
			public: Structures::Shaders* addShadersFromFiles(string id, string vertex_shader_file, string fragment_shader_file);
			public: Structures::Material* addMaterialFromData(string id, GLfloat shininess, GLfloat specular_amount, GLfloat specular_cap, GLint effects);
			public: Structures::Model* getModel(string model_id);
			public: Structures::Mesh* getMesh(string mesh_id);
			public: Structures::Texture* getTexture(string texture_id);
			public: Structures::Shaders* getShaders(string shaders_id);
			public: Structures::Material* getMaterial(string material_id);
		};
	}
}

#endif // STARCLOCK_RENDER_SCENE_H

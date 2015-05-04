#ifndef STARCLOCK_RENDER_SCENE_H
#define STARCLOCK_RENDER_SCENE_H

//----STANDARD----
#include "list"
#include "vector"
#include "string"

//----LOCAL----
#include "camera.h"
#include "entity.h"
#include "structures/model.h"
#include "structures/mesh.h"
#include "structures/texture.h"

using namespace std;

namespace Starclock
{
	namespace Render
	{
		class Scene
		{
			public: Camera* camera;
			public: vector<Entity> entities;
			public: vector<Structures::Model> models;
			public: vector<Structures::Mesh> meshes;
			public: vector<Structures::Texture> textures;

			public: Scene();
			public: void update();
			public: void render();
			public: Structures::Model* addModelFromMeshTexture(string id, string mesh_id, string texture_id);
			public: Structures::Mesh* addMeshFromOBJ(string id, string filename);
			public: Structures::Texture* addTextureFromBMP(string id, string filename);
			public: Structures::Model* getModel(string model_id);
			public: Structures::Mesh* getMesh(string mesh_id);
			public: Structures::Texture* getTexture(string texture_id);
		};
	}
}

#endif // STARCLOCK_RENDER_SCENE_H

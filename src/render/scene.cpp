//----LIBRARY----
#include "glbinding/gl/gl.h"
#include "glbinding/Binding.h"

//----LOCAL----
#include "scene.h"
#include "../common/out.h"

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
		}
	}
}

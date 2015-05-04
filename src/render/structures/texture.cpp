//----STANDARD----
#include "stdlib.h"
#include "string"
#include "fstream"
#include "vector"

//----LIBRARY----
#include "glbinding/gl/gl.h"
#include "glbinding/Binding.h"

//----LOCAL----
#include "texture.h"
#include "../../common/out.h"

using namespace gl;

namespace Starclock
{
	namespace Render
	{
		namespace Structures
		{
			Texture::Texture(Scene* scene, string id)
			{
				this->scene = scene;
				this->id = id;
			}

            bool Texture::loadFromBMP(string filename)
			{
				unsigned int image_size; //In bytes

				ifstream file(filename.c_str(), ios::in | ios::binary);

				if (!Common::Out::test(file.is_open(), "Opening file '" + filename + "'", false))
					return false;

				long beg = file.tellg();
				file.seekg(0, ios::end);
				long end = file.tellg();
				file_data = new unsigned char[end - beg];
				file.seekg(0, ios::beg);

				//Load the file
				long x = 0;
				while (file)
				{
					char a;
					file.get(a);
					this->file_data[x] = a;
					//printf("%c", a);
					x ++;
				}

				Common::Out::put("File size of '" + filename + "' in bytes: " + to_string(x));

				if (!Common::Out::test(this->file_data[0] == 'B' && this->file_data[1] == 'M', "Validating header", false, false))
					return false;

				// Read ints from the byte array
				this->data_pos = *(int*)&(this->file_data[0x0A]);
				image_size = *(int*)&(this->file_data[0x22]);
				this->width = *(int*)&(this->file_data[0x12]);
				this->height = *(int*)&(this->file_data[0x16]);

				//Some data might be missing, so let's fill that in
				if (image_size == 0)
					image_size = this->width * this->height * 3;
				if (data_pos == 0)
					data_pos = 54;

				return true;
			}

			void Texture::buffer()
			{
				//Clear any existing memory before rebuffering
				glDeleteTextures(1, &this->gl_id);

				//Create the OpenGL texture
				glGenTextures(1, &this->gl_id);

				//Bind the texture
				glBindTexture(GL_TEXTURE_2D, this->gl_id);

				//Pass the image to OpenGL
				glTexImage2D(GL_TEXTURE_2D, 0, (GLint)GL_RGB, this->width, this->height, 0, GL_BGR, GL_UNSIGNED_BYTE, (void*)(&this->file_data[this->data_pos]));

				//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
				glGenerateMipmap(GL_TEXTURE_2D);

				//We've buffered the data, so let's clear it
				if (this->clear_on_buffer)
					delete[] this->file_data;
			}
		}
	}
}

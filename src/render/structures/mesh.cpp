//----LIBRARY----
#include "stdlib.h"
#include "stdio.h"
#include "string"
#include "vector"
#include "fstream"

//----LIBRARY----
#include "glbinding/gl/gl.h"
#include "glbinding/Binding.h"

//----LOCAL----
#include "mesh.h"
#include "geometry.h"
#include "../../common/out.h"

using namespace gl;

namespace Starclock
{
	namespace Render
	{
		namespace Structures
		{
			Mesh::Mesh(Scene* scene, string id)
			{
				this->scene = scene;
				this->id = id;
			}

			bool Mesh::loadFromOBJ(string filename)
			{
				//Clear the polygon vector ready for new data
				this->polygons.clear();

				vector<VertexPos> tmp_pos;
				vector<VertexTex> tmp_tex;
				vector<VertexNorm> tmp_norm;

				//Open the file
				ifstream file (filename);

				//Return false if the read operation failed
				if (!Common::Out::test(file.is_open(), "Opening '" + filename + "'"))
					return false;

				//We'll be using this later...
				string line;

				//Keep reading file lines from the stream
				while (getline(file, line))
				{
					//Verbose output
					//Common::output(line);

					//Some functions here only take c-style strings, so convert it for them
					const char* c_line = line.c_str();
					//Common::output(c_line);

					//Parse the line
					if (c_line[0] == 'v' && c_line[1] == ' ') //Deal with the vertex positions
					{
						VertexPos pos;
						sscanf(c_line, "v %f %f %f", &pos.x, &pos.y, &pos.z);
						tmp_pos.push_back(pos);
					}
					else if (c_line[0] == 'v' && c_line[1] == 't') //Deal with the vertex UV coordinates
					{
						VertexTex tex;
						sscanf(c_line, "vt %f %f", &tex.x, &tex.y);
						tmp_tex.push_back(tex);
					}
					else if (c_line[0] == 'v' && c_line[1] == 'n') //Deal with the vertex UV coordinates
					{
						VertexNorm norm;
						sscanf(c_line, "vn %f %f %f", &norm.i, &norm.j, &norm.k);
						tmp_norm.push_back(norm);
					}
					else if (c_line[0] == 'f' && c_line[1] == ' ') //Deal with the vertex UV coordinates
					{
						//The actual string
						char vertex[3][20];
						//The ids of all the data
						unsigned int pos_index[3], tex_index[3], norm_index[3];

						//Scan the vertex strings
						bool matches = (sscanf(c_line, "f %s %s %s", vertex[0], vertex[1], vertex[2]) == 3);

						if (!Common::Out::test(matches, "Parsing file", false, true))
							return false;

						//Scan each vertex for data
						for (int n = 0; n < 3; n ++)
						{
							//Default to 3-format (with normals)
							matches = (sscanf(vertex[n], "%d/%d/%d", &pos_index[n], &tex_index[n], &norm_index[n]) == 3);

							//...and just in case there aren't normals!
							if (!matches)
								matches = (sscanf(vertex[n], "%d/%d", &pos_index[n], &tex_index[n]) == 2);

							if (!Common::Out::test(matches, "Parsing file", false, true))
								return false;
						}

						Polygon poly;

						//Find the parts of the polygon
						poly.a.pos = tmp_pos[pos_index[0] - 1];
						poly.b.pos = tmp_pos[pos_index[1] - 1];
						poly.c.pos = tmp_pos[pos_index[2] - 1];

						poly.a.tex = tmp_tex[tex_index[0] - 1];
						poly.b.tex = tmp_tex[tex_index[1] - 1];
						poly.c.tex = tmp_tex[tex_index[2] - 1];

						//We got normals!
						if (matches == 3)
						{
							poly.a.norm = tmp_norm[norm_index[0]];
							poly.b.norm = tmp_norm[norm_index[1]];
							poly.c.norm = tmp_norm[norm_index[2]];
						}

						this->polygons.push_back(poly);
					}
				}

				return true;
			}

			void Mesh::buffer()
			{
				//Create the vertex array id and bind it
				glGenVertexArrays(1, &this->gl_id);
				glBindVertexArray(this->gl_id);

				//Create the vertex buffer id and bind it
				glGenBuffers(1, &this->gl_id);
				glBindBuffer(GL_ARRAY_BUFFER, this->gl_id);

				this->polygon_number = this->polygons.size();
				Common::Out::put("Polygon number = " + to_string(this->polygon_number));

				//Pass the vertex position data to GL (the graphics card)
				glBufferData(GL_ARRAY_BUFFER, this->polygon_number * sizeof(Polygon), &this->polygons[0], GL_STATIC_DRAW);
			}
		}
	}
}

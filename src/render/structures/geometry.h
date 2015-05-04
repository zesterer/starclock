#ifndef STARCLOCK_RENDER_STRUCTURES_GEOMETRY_H
#define STARCLOCK_RENDER_STRUCTURES_GEOMETRY_H

//----LIBRARY----
#include "glbinding/gl/gl.h"
#include "glbinding/Binding.h"

using namespace gl;

namespace Starclock
{
	namespace Render
	{
		namespace Structures
		{
			struct VertexPos
			{
				GLfloat x, y, z;
			};

			struct VertexCol
			{
				GLfloat r, g, b;
			};

			struct VertexTex
			{
				GLfloat x, y;
			};

			struct VertexNorm
			{
				GLfloat i, j, k;
			};

			struct Vertex
			{
				VertexPos pos;
				VertexCol col;
				VertexTex tex;
				VertexNorm norm;
			};

			struct Polygon
			{
				Vertex a, b, c;
			};
		}
	}
}

#endif // STARCLOCK_RENDER_STRUCTURES_GEOMETRY_H

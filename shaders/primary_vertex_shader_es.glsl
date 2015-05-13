#version 300 es

uniform mat4 PERSPECTIVE_MATRIX;
uniform mat4 CAMERA_MATRIX;
uniform mat4 MODEL_MATRIX;

layout(location = 0) in highp   vec3 vertex_pos;
layout(location = 1) in lowp    vec3 vertex_col;
layout(location = 2) in mediump vec2 vertex_uv;
layout(location = 3) in lowp    vec3 vertex_norm;

smooth out highp vec4 frag_pos;
smooth out lowp vec3 frag_col;
smooth out mediump vec2 frag_uv;
smooth out lowp vec4 frag_norm;

struct Vertex
{
	highp vec3 pos;
	lowp vec3 col;
	mediump vec2 uv;
	lowp vec3 norm;
};

void main()
{
	Vertex vertex;
	vertex.pos = vertex_pos;
	vertex.col = vertex_col;
	vertex.uv = vertex_uv;
	vertex.norm = vertex_norm;

	//Find the final position. It's a position, so w is 1.
	gl_Position = PERSPECTIVE_MATRIX * CAMERA_MATRIX * MODEL_MATRIX * vec4(vertex.pos, 1.0);
	frag_pos = CAMERA_MATRIX * MODEL_MATRIX * vec4(vertex.pos, 1.0);

	//The high effect
	//gl_Position.x += sin(gl_Position.y * 2.0) / 10.0;
	//gl_Position.y += cos(gl_Position.x * 2.0) / 10.0;

	//Find the final normal. It's a vector, so w is 0.
	frag_norm = vec4(vertex.norm, 0.0);
	//Set the fragment normal
	frag_col = vertex.col;
	//Set the UV coordinates
	frag_uv = vertex.uv;
}

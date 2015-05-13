#version 130

uniform mat4 PERSPECTIVE_MATRIX;
uniform mat4 CAMERA_MATRIX;
uniform mat4 MODEL_MATRIX;

in highp   vec3 vertex_pos;
in lowp    vec3 vertex_col;
in mediump vec2 vertex_uv;
in lowp    vec3 vertex_norm;

smooth out highp   vec4 FRAG_POS;
smooth out lowp    vec3 FRAG_COL;
smooth out mediump vec2 FRAG_UV;
smooth out lowp    vec4 FRAG_NORM;

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
	FRAG_POS = CAMERA_MATRIX * MODEL_MATRIX * vec4(vertex.pos, 1.0);

	//The high effect
	//gl_Position.x += sin(gl_Position.y * 2.0) / 10.0;
	//gl_Position.y += cos(gl_Position.x * 2.0) / 10.0;

	//Find the final normal. It's a vector, so w is 0.
	FRAG_NORM = vec4(vertex.norm, 0.0);
	//Set the fragment normal
	FRAG_COL = vertex.col;
	//Set the UV coordinates
	FRAG_UV = vertex.uv;
}

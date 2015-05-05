#version 300 es

uniform mat4 CAMERA_MATRIX;
uniform mat4 MODEL_MATRIX;
uniform vec3 LIGHT_VECTOR;

//Get the vertex position in the model
layout(location = 0) in lowp vec3 vert_pos;
//Get the vertex colour
layout(location = 1) in lowp vec3 vert_col;
//Get the vertex texture UV position
layout(location = 2) in lowp vec2 vert_uv;
//Get the vertex normal
layout(location = 3) in lowp vec3 vert_norm;


//Output the normal
smooth out lowp vec3 frag_norm;
//Output the fragment colour
out lowp vec3 frag_col;
//Output the fragment UV coordinates
out lowp vec2 frag_uv;

void main()
{
	//Find the final position. It's a position, so w is 1.
	gl_Position = CAMERA_MATRIX * MODEL_MATRIX * vec4(vert_pos, 1);

	//The high effect
	//gl_Position.x += sin(gl_Position.y * 2.0) / 10.0;
	//gl_Position.y += cos(gl_Position.x * 2.0) / 10.0;

	//Find the final normal. It's a vector, so w is 0.
	frag_norm = vert_norm;
	//Set the fragment normal
	frag_col = vert_col;
	//Set the UV coordinates
	frag_uv = vert_uv;
}

#version 300 es

uniform mat4 PERSPECTIVE_MATRIX;
uniform mat4 CAMERA_MATRIX;
uniform mat4 MODEL_MATRIX;

//Get the vertex position in the model
layout(location = 0) in lowp vec3 vert_pos;
//Get the vertex colour
layout(location = 1) in lowp vec3 vert_col;
//Get the vertex texture UV position
layout(location = 2) in lowp vec2 vert_uv;
//Get the vertex normal
layout(location = 3) in lowp vec3 vert_norm;


//Output the relative position, smoothed between vertices
smooth out lowp vec4 frag_pos;
//Output the normal
smooth out lowp vec4 frag_norm;
//Output the fragment colour
smooth out lowp vec3 frag_col;
//Output the fragment UV coordinates
smooth out lowp vec2 frag_uv;

void main()
{
	//Find the final position. It's a position, so w is 1.
	gl_Position = PERSPECTIVE_MATRIX * CAMERA_MATRIX * MODEL_MATRIX * vec4(vert_pos, 1.0);
	frag_pos = CAMERA_MATRIX * MODEL_MATRIX * vec4(vert_pos, 1.0);

	//The high effect
	//gl_Position.x += sin(gl_Position.y * 2.0) / 10.0;
	//gl_Position.y += cos(gl_Position.x * 2.0) / 10.0;

	//Find the final normal. It's a vector, so w is 0.
	frag_norm = vec4(vert_norm, 0.0);
	//Set the fragment normal
	frag_col = vert_col;
	//Set the UV coordinates
	frag_uv = vert_uv;
}

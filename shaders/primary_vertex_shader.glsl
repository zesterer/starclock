#version 300 es

//Get the final matrix that includes all transformations
uniform mat4 MVP;

//Get the vertex position in the model
layout(location = 0) in lowp vec3 pos;

//Get the vertex colour
layout(location = 1) in lowp vec3 col;

//Get the vertex texture position
layout(location = 2) in lowp vec2 tex;

//Get the vertex normal
layout(location = 3) in lowp vec3 norm;

//Output the fragment colour
out lowp vec3 fragmentColor;

//Output the fragment UV coordinates
out lowp vec2 UV;

void main()
{
	//Find the final position. It's a position, so w is 1.
	lowp vec4 position = vec4(pos, 1);
	gl_Position = MVP * position;

	fragmentColor = vec3(position.x, position.y, position.z);//col;

	//Set the UV coordinates
	UV = tex;
}

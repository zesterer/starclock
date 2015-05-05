#version 300 es

uniform lowp mat4 MODEL_MATRIX;
uniform lowp vec3 LIGHT_VECTOR;

//Output the find colour
out lowp vec3 color;

//Get the fragment normal
smooth in lowp vec3 frag_norm;
//Get the fragment colour
in lowp vec3 frag_col;
//Get the texture UV coordinates
in lowp vec2 frag_uv;

//The texture / sampler itself
uniform sampler2D texture_sampler;

void main()
{
	lowp vec3 normal = normalize((MODEL_MATRIX * vec4(frag_norm, 0)).xyz);
	lowp vec3 light_vector = normalize((vec4(LIGHT_VECTOR, 0)).xyz);
	lowp float diffuse;

	if (normal.xyz == vec3(0, 0, 0))
		diffuse = 1.0;
	else
		diffuse = clamp(dot(normal, light_vector), 0.0, 1.0);
	//diffuse = 1.0;

	lowp vec3 tex;
	if (frag_uv == vec2(-1.0, -1.0))
		tex = vec3(1.0, 1.0, 1.0);
	else
		tex = texture(texture_sampler, frag_uv).rgb;

	//Cartoon (cel shading) effect
	lowp float parts = 5.0;
	//tex = floor(tex * parts) / parts;

	color = tex * frag_col * diffuse;
}

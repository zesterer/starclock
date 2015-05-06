#version 300 es

uniform lowp mat4 PERSPECTIVE_MATRIX;
uniform lowp mat4 CAMERA_MATRIX;
uniform lowp mat4 MODEL_MATRIX;
uniform lowp vec4 LIGHT_VECTOR;

//Output the final colour
out lowp vec3 color;
//Output the final texture position
out lowp vec2 uv;

//Get the position in space
smooth in lowp vec4 frag_pos;
//Get the fragment normal
smooth in lowp vec4 frag_norm;
//Get the fragment colour
smooth in lowp vec3 frag_col;
//Get the texture UV coordinates
smooth in lowp vec2 frag_uv;

//The texture / sampler itself
uniform sampler2D texture_sampler;

void main()
{
	//----GENERAL----
	lowp vec4 coord_normal = MODEL_MATRIX * frag_norm;
	lowp vec4 cam_normal = CAMERA_MATRIX * coord_normal;
	lowp float dist_to_cam = length(cam_normal);
	lowp vec4 light_vector = vec4(LIGHT_VECTOR.xyz, 0.0);

	//----AMBIANCE----
	lowp float ambiance = LIGHT_VECTOR.w;

	//----DIFFUSE----
	lowp float diffuse;
	if (coord_normal.xyz == vec3(0, 0, 0))
		diffuse = 1.0;
	else
		diffuse = min(1.0, max(0.0, dot(normalize(coord_normal).xyz, -normalize(light_vector.xyz))) + ambiance);

	//----TEXTURE----
	uv = frag_uv;
	lowp vec3 tex;
	if (frag_uv == vec2(-1.0, -1.0))
		tex = vec3(1.0, 1.0, 1.0);
	else
		tex = texture2DProjLod(texture_sampler, vec3(frag_uv, 1.0), 0.05 * dist_to_cam).rgb;
	//tex = vec3(0.5, 1.0, 0.5);

	//----SPOTLIGHT----
	lowp float spotlight = 0.0;
	//spotlight = 3.0 * max(0.0, 0.5 - length(frag_pos.xy) / (0.9 * frag_pos.z));

	//----SPECULAR----
	lowp float specular_shininess = 15.0;
	lowp float specular_amount = 0.3;
	lowp float specular_cap = 1.0;
	lowp float specular = 0.0;
	if (true) //Might be useful later
	{
		lowp vec3 N = normalize((cam_normal).xyz);
		lowp vec3 L = - normalize((CAMERA_MATRIX * light_vector).xyz);
		lowp vec3 R = normalize(2.0 * N * dot(N, L) - L);
		lowp vec3 V = - normalize(vec3(frag_pos.x, frag_pos.y, frag_pos.z) / 2.0);
		specular = min(specular_cap, pow(max(0.0, (dot(R, V) - (1.0 - specular_amount)) * 1.0 / specular_amount), specular_shininess) * specular_shininess * 0.2); //Constant
	}

	//Cartoon (cel shading) effect
	lowp float parts = 6.0;
	//diffuse = 1.0;
	//diffuse = floor(diffuse * parts) / parts + 0.5 / parts;
	//specular = floor(specular * parts) / parts + 0.5 / parts;

	color = tex * frag_col * (diffuse + spotlight) + specular;

	//color = floor(color * parts) / parts + 0.5 / parts;
}

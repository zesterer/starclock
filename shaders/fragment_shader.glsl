#version 130

uniform lowp mat4 PERSPECTIVE_MATRIX;
uniform lowp mat4 CAMERA_MATRIX;
uniform lowp mat4 MODEL_MATRIX;
//uniform lowp vec4 LIGHT_VECTOR;

uniform lowp vec4 LIGHT_VECTOR[16];
uniform lowp vec4 LIGHT_COLOUR[16];

//Output the final colour
out lowp vec3 COLOR;

//Get the position in space
smooth in lowp vec4 FRAG_POS;
smooth in lowp vec4 FRAG_NORM;
smooth in lowp vec3 FRAG_COL;
smooth in lowp vec2 FRAG_UV;

//The texture / sampler itself
uniform sampler2D texture_sampler;

vec3 getSpecular(vec4 vector, vec4 colour)
{
	lowp float specular_shininess = 15.0;
	lowp float specular_amount = 0.6;
	lowp float specular_cap = 2.0;

	vec4 cam_normal = CAMERA_MATRIX * MODEL_MATRIX * FRAG_NORM;

	lowp vec3 N = normalize((cam_normal).xyz);
	lowp vec3 L = - normalize((CAMERA_MATRIX * vector).xyz);
	lowp vec3 R = normalize(2.0 * N * dot(N, L) - L);
	lowp vec3 V = - normalize(FRAG_POS.xyz / 2.0);

	lowp float specular = (dot(R, V) - (1.0 - specular_amount)) * 1.0 / specular_amount;
	specular = min(specular_cap, pow(max(0.0, specular), specular_shininess) * specular_shininess * 0.2);
	return colour.xyz * specular;
}

vec3 getDiffuse(vec4 vector, vec4 colour, float ambiance)
{
	return colour.xyz * min(1.0, max(ambiance, dot(normalize(MODEL_MATRIX * FRAG_NORM).xyz, -normalize(vector.xyz))));
}

void main()
{
	//----GENERAL----
	lowp vec4 coord_normal = MODEL_MATRIX * FRAG_NORM;
	lowp vec4 cam_normal = CAMERA_MATRIX * coord_normal;
	lowp float dist_to_cam = length(cam_normal);
	//lowp vec4 light_vector = vec4(LIGHT_VECTOR.xyz, 0.0);

	//Find the texture colour
	lowp vec3 tex;
	if (FRAG_UV == vec2(-1.0, -1.0)) //If there's no texture
		tex = FRAG_COL * vec3(1.0, 1.0, 1.0);
	else //It's got a texture!
		tex = FRAG_COL * texture2DProjLod(texture_sampler, vec3(FRAG_UV, 1.0), 0.05 * dist_to_cam).rgb;

	//Initialise the specular, ambiance and diffuse
	lowp vec3 specular = vec3(0.0, 0.0, 0.0);
	lowp vec3 diffuse = vec3(0.0, 0.0, 0.0);

	//Loop through all the lights
	for (int count = 0; count < 16; count ++)
	{
		//Find the direction and colour of each light
		vec4 vector = LIGHT_VECTOR[count];
		vec4 colour = LIGHT_COLOUR[count];

		if (colour.xyz != vec3(0.0, 0.0, 0.0))
		{
			specular += getSpecular(vector, colour); //Find the specular component
			diffuse += getDiffuse(vector, colour, colour.w); //Find the diffuse component
		}
	}

	COLOR = tex * diffuse + specular;
}

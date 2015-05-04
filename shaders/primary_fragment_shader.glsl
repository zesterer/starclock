#version 300 es

//Output the find colour
out lowp vec3 color;

//Get the fragment colour
in lowp vec3 fragmentColor;

//Get the texture UV coordinates
in lowp vec2 UV;

uniform sampler2D texture_sampler;

void main()
{
	//color = fragmentColor;
	color = texture(texture_sampler, UV).rgb * fragmentColor;
}

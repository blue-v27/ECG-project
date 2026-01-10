#version 400

in vec2 textureCoord; 
in vec3 norm;
in vec3 fragPos;
in vec4 vColor;

out vec4 fragColor;

uniform sampler2D texture1;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
	//TO DO: Add illumination from Lab 9

	//fragColor = texture(texture1, textureCoord);
	fragColor = vec4(1.f, 1.f, 1.f, 1.f);
}
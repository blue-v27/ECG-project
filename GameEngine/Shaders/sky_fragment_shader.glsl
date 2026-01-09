#version 400

in vec2 textureCoord; 
in vec3 norm;
in vec3 fragPos;

out vec4 fragColor;

uniform sampler2D texture1;
uniform vec3 viewPos;

void main()
{
    fragColor = vec4(texture(texture1, textureCoord).rgb, 1.0);
}
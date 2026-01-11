#version 400

#define MAX_LIGHTS 16

in vec2 textureCoord;
in vec3 norm;
in vec3 fragPos;

out vec4 fragColor;

uniform sampler2D texture1;

void main()
{
    vec3 texColor = texture(texture1, textureCoord).rgb;

    fragColor = vec4(texColor, 1.0);
}
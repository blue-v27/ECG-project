#version 400

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normals;
layout (location = 2) in vec2 texCoord;

out vec2 textureCoord;
out vec3 norm;
out vec3 fragPos;

uniform mat4 projection;
uniform mat4 view;

void main()
{
	textureCoord = texCoord;
	mat4 rotView = mat4(mat3(view)); 
	vec3 centeredPos = pos - vec3(0.133236, 2.355064, 2.553428);;
	gl_Position = projection * rotView * vec4(centeredPos, 1.0);
	gl_Position.xyww; 
}
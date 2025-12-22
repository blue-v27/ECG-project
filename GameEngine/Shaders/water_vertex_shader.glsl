#version 400

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normals;
layout (location = 2) in vec2 texCoord;

out vec2 textureCoord;
out vec3 norm;
out vec3 fragPos;

uniform mat4 MVP;
uniform mat4 model;

void main()
{
	textureCoord = texCoord;

	float waveHeight = 10.f;
	vec2  waveDir	 = vec2(0.5f, 0.5f);
	float length	 = 2.f;					// distance between the top of the waves
	float pi		 = 3.14159265359;
	float waveFreq	 = 2 * pi / length;

	fragPos	= vec3(model * vec4(pos, 1.0f));
	norm	= mat3(transpose(inverse(model)))*normals;

	float newY   = 2 * waveHeight * (sin(dot(waveDir, fragPos.xz) * waveFreq)) * (sin(dot(waveDir, fragPos.xz) * waveFreq)) / 4;
	vec3  newPos = vec3(fragPos.x, newY, fragPos.z);

	gl_Position = MVP * vec4(newPos, 1.0f);
}
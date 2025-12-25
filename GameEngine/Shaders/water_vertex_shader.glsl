#version 400

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normals;
layout (location = 2) in vec2 texCoord;

out vec2 textureCoord;
out vec3 norm;
out vec3 fragPos;

uniform mat4  MVP;
uniform mat4  model;
uniform float  waveLength;
uniform float time;
uniform float amplitude;

float hash(vec2 p) 
{
    p = vec2(dot(p, vec2(127, 311)), dot(p, vec2(269, 183)));
    return fract(sin(p.x + p.y) * 43758);
}

void main()
{
	textureCoord = texCoord + sin(time / 2) / 100.f;

	float waveHeight = amplitude * sin(time) / 2;

	vec2 waveDir = vec2(hash(pos.xz) * 2.0 - 1.0, hash(pos.xz + 1.0) * 2.0 - 1.0);
	waveDir		 = normalize(waveDir);

	float length   = 2.f * waveLength; // distance between the top of the waves
	float pi	   = 3.14;
	float waveFreq = 2 * pi / length;

	//fragPos	= vec3(model * vec4(pos, 1.0f));
	//norm	= mat3(transpose(inverse(model)))*normals;

	float newY   = 2 * waveHeight * (sin(dot(waveDir, pos.xz) * waveFreq + time) + 1.f) * (sin(dot(waveDir, pos.xz) * waveFreq + time) + 1.f) / 4.f;
	vec3  newPos = vec3(pos.x, newY, pos.z);

	gl_Position = MVP * vec4(newPos, 1.0f);
} 
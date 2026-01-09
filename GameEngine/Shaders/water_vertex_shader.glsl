#version 400

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normals;
layout (location = 2) in vec2 texCoord;

out vec2 textureCoord;
out vec3 norm;
out vec3 fragPos;

uniform mat4 MVP;
uniform mat4 model;
uniform float waveLength;
uniform float time;
uniform float amplitude;

/* ---------- helpers ---------- */
float hash(vec2 p)
{
    p = vec2(dot(p, vec2(127.1, 311.7)),
             dot(p, vec2(269.5, 183.3)));
    return fract(sin(p.x + p.y) * 43758.5453);
}

/* ---------- globals for wave ---------- */
vec2  gWaveDir;
float gWaveFreq;
float gWaveHeight;

/* ---------- wave height ---------- */
float waveHeightAt(vec2 xz)
{
    float A = dot(gWaveDir, xz) * gWaveFreq + time;
    float s = sin(A) + 1.0;
    return gWaveHeight * s * s * 0.5;
}

/* ---------- main ---------- */
void main()
{
    /* texture animation */
    textureCoord = texCoord + sin(time * 0.5) * 0.01;

    /* wave parameters */
    gWaveHeight = amplitude * 0.5;

    gWaveDir = vec2(
        hash(pos.xz) * 2.0 - 1.0,
        hash(pos.xz + 1.0) * 2.0 - 1.0
    );
    gWaveDir = normalize(gWaveDir);

    gWaveFreq = 2.0 * 3.14159265 / (2.0 * waveLength);

    /* vertex displacement */
    float newY = waveHeightAt(pos.xz);
    vec3 newPos = vec3(pos.x, newY, pos.z);

    fragPos = vec3(model * vec4(newPos, 1.0));

    /* normal calculation */
    float eps = waveLength * 0.01;

    float hL = waveHeightAt(pos.xz - vec2(eps, 0.0));
    float hR = waveHeightAt(pos.xz + vec2(eps, 0.0));
    float hD = waveHeightAt(pos.xz - vec2(0.0, eps));
    float hU = waveHeightAt(pos.xz + vec2(0.0, eps));

    vec3 dx = vec3(2.0 * eps, hR - hL, 0.0);
    vec3 dz = vec3(0.0, hU - hD, 2.0 * eps);

    mat3 normalMatrix = inverse(mat3(model));
    norm = normalize(normalMatrix * cross(dx, dz));

    if (norm.y < 0.0)
        norm = -norm;

    gl_Position = MVP * vec4(newPos, 1.0);
}

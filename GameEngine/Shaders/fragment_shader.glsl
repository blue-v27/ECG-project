#version 400

#define MAX_LIGHTS 16

in vec2 textureCoord;
in vec3 norm;
in vec3 fragPos;

out vec4 fragColor;

uniform sampler2D texture1;
uniform vec3 viewPos;

struct Light
{
    vec3 position;
    vec3 color;

    float ka;  
    float kd;   
    float ks;  
};

uniform Light lights[MAX_LIGHTS];
uniform int   numLights;

void main()
{
    vec3 N        = normalize(norm);
    vec3 viewDir  = normalize(viewPos - fragPos);
    vec3 texColor = texture(texture1, textureCoord).rgb;

    float shininess = 32.0;

    vec3 lighting = vec3(0.0);

    for (int i = 0; i < numLights; ++i)
    {
        Light light = lights[i];

        vec3 lightDir = normalize(light.position - fragPos);

        vec3 ambient = light.ka * light.color;

        float diff = max(dot(N, lightDir), 0.0);
        vec3 diffuse = light.kd * diff * light.color;

        vec3 reflectDir = reflect(-lightDir, N);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
        vec3 specular = light.ks * spec * light.color;

        lighting += ambient + diffuse + specular;
    }

    fragColor = vec4(lighting * texColor, 1.0);
}
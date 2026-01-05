#version 400

in vec2 textureCoord; 
in vec3 norm;
in vec3 fragPos;

out vec4 fragColor;

uniform sampler2D texture1;
uniform vec3	  lightColor;
uniform vec3	  lightPos;
uniform vec3	  viewPos;

void main()
{
	float ka	 = 0.1; 
	vec3 ambient = ka * lightColor;

	vec3 N		  = normalize(norm);
	vec3 lightDir = normalize(lightPos - fragPos);

	float kd	  = 1;
	float diff    = max(dot(N, lightDir), 0.0);
	vec3  diffuse = kd * diff * lightColor;

	float ks		 = 0.5;
	vec3  viewDir    = normalize(viewPos - fragPos);
	vec3  reflectDir = reflect(-lightDir, N);
	float shininess  = 32;
	float spec		 = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
	vec3  specular   = ks * spec * lightColor; 

	vec3 lighting = ambient + diffuse + specular;
	vec3 texColor = texture(texture1, textureCoord).rgb;

	fragColor	  = vec4(lighting * texColor, 1.0);
}
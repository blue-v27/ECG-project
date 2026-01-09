#version 330 core
layout(location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 view;
uniform mat4 projection;

void main()
{
    TexCoords = aPos;
    
    // Remove translation from view matrix to keep skybox centered
    mat4 viewNoTrans = mat4(mat3(view));
    gl_Position = projection * viewNoTrans * vec4(aPos, 1.0);
}

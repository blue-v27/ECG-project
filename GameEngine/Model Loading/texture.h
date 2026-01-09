#pragma once
#include <glew.h>
#include <glfw3.h>
#include <vector>

GLuint loadBMP(const char * imagepath);
GLuint loadCubemap(const std::vector<const char*>& faces);

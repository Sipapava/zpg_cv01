#pragma once
#define GLEW_STATIC

#include <GL/glew.h>
#include <vector>;
#include "vertex.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
std::vector<Vertex> buildCircle(float radius, int vCount);
std::vector<Vertex> FromFloat(const float* data, size_t size);
//
// Created by Jainil Patel on 25/12/22.
//

#ifndef RASPAINTER_MAIN_H
#define RASPAINTER_MAIN_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
using namespace std;

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Shader.h"
#include "Camera.h"
#include "mesh.h"
#include "Model.h"

#endif //RASPAINTER_MAIN_H

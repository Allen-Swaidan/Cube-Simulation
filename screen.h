#ifndef SCREEN_H
#define SCREEN_H

#include <GL/glew.h> 
#include <GLFW/glfw3.h>
#include<glm/glm/glm.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include "shader.h"
#include "shape.h"

#define numVAOs 1
#define numVBOs 2

class Screen
{
public:
	Screen();
	void initalize(GLFWwindow* window);
	void display(GLFWwindow* window, double currentTime);

private:
	GLuint renderingProgram, vao[numVAOs], vbo[numVBOs];;
	GLuint mvLoc, projLoc, moveLoc;

	float cameraX, cameraY, cameraZ, aspect, cubeLocX, cubeLocY, cubeLocZ;
	int width, height;

	glm::mat4 pMat, vMat, mMat, mvMat, tMat, rMat;
};
#endif 


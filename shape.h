#ifndef SHAPE_H
#define SHAPE_H

#include <GL/glew.h> 
#include <GLFW/glfw3.h>
#include <array>

#define numVAOs 1
#define numVBOs 2

class Shape
{
public:
	Shape();
	void cube();

private:
	std::array<float, 108> cubeVertices;
	GLuint vao[numVAOs], vbo[numVBOs];
};
#endif

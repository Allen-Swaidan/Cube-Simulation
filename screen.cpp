#include "screen.h"

Screen::Screen()
{
	
}

void Screen::initalize(GLFWwindow* window)
{
	Shader::Instance()->createProgram();
	Shader::Instance()->createShaders();
	Shader::Instance()->compileShaders();
	Shader::Instance()->attachShaders();
	Shader::Instance()->linkProgram();
	renderingProgram = Shader::Instance()->linkProgram();

	cameraX = 0.0f;
	cameraY = 0.0f;
	cameraZ = 8.0f;

	cubeLocX = 0.0f;
	cubeLocY = -2.0f;
	cubeLocZ = 0.0f;
	Shape shape;
	shape.cube();
}

void Screen::display(GLFWwindow* window, double currentTime)
{
	glClear(GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT);

	//loads the program onto the gpu
	glUseProgram(renderingProgram);

	//build perspective matrix
	glfwGetFramebufferSize(window, &width, &height);
	aspect = (float)width / (float)height;
	pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f); //1.0472 radians = 60 degrees

	//build view matrix, model matrix, and model-view matrix
	vMat = glm::translate(glm::mat4(1.0f), glm::vec3(-cameraX, -cameraY, -cameraZ));
	mMat = glm::translate(glm::mat4(1.0f), glm::vec3(cubeLocX, cubeLocY, cubeLocZ));
	mvMat = vMat * mMat;

	//building translation and rotation matrices to animate the cube
	tMat = glm::translate(glm::mat4(1.0f), glm::vec3(sin(0.35f * currentTime) * 2.0f, cos(0.52f * currentTime) * 2.0f, sin(0.7f * currentTime) * 2.0f));
	rMat = glm::rotate(glm::mat4(1.0f), 1.75f * (float)currentTime, glm::vec3(0.0f, 1.0f, 0.0f));
	rMat = glm::rotate(rMat, 1.75f * (float)currentTime, glm::vec3(1.0f, 0.0f, 0.0f));
	rMat = glm::rotate(rMat, 1.75f * (float)currentTime, glm::vec3(0.0f, 0.0f, 1.0f));
	mMat = tMat * rMat;

	//getting the uniform variables for move matrix
	mvLoc = glGetUniformLocation(renderingProgram, "mv_matrix");
	projLoc = glGetUniformLocation(renderingProgram, "proj_matrix");
	moveLoc = glGetUniformLocation(renderingProgram, "move_matrix");

	//copy perspective and MV matrices to corresponding uniform variables
	glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(pMat));

	//copy the mMat movement matrix into the move_matrix uniform variable
	glUniformMatrix4fv(moveLoc, 1, GL_FALSE, glm::value_ptr(mMat));

	//associate VBO with the corresponding vertex attribute in the vertex shader
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	//adjust OpenGL settings and draw model
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
/*
 * GLApplication.cpp
 *
 *  Created on: 07/08/2016
 *      Author: rey
 */

#include "Headers/GLApplication.h"

Shader shader;

GLuint VAO, VBO, EBO;

GLApplication::GLApplication() :
		windowManager(nullptr), camera(nullptr) {
}

GLApplication::~GLApplication() {
	destroy();
}

void GLApplication::GLMain() {
	initialize();
	applicationLoop();
}

void GLApplication::initialize() {
	if (!windowManager
			|| !windowManager->initialize(800, 700, "Window GLFW", false)) {
		this->destroy();
		exit(-1);
	}

	glViewport(0, 0, WindowManager::screenWidth, WindowManager::screenHeight);
	glClearColor(0.2f, 0.2f, 0.2f, 0.0f);

	//glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	shader.initialize("Shaders/shader.vs", "Shaders/shader.fs");
}
void GLApplication::applicationLoop() {
	bool processInput = true;
	glm::vec3 modelPositions[] =
		{ glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(2.0f, 5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f)};

	glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
	Model objModel("objects/cat/cat.obj");
	Model objModel2("objects/Charizard/Charizard.obj");
	Model objModel3("objects/Rabbit/Rabbit.obj");

	while (processInput) {
		processInput = windowManager->processInput(true);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.turnOn();

		// Transformation matrices
		glm::mat4 view = camera->GetViewMatrix();
		glm::mat4 projection;
		projection = glm::perspective(45.0f,
				(GLfloat) WindowManager::screenWidth
						/ (GLfloat) WindowManager::screenHeight, 0.1f, 100.0f);
		// Get the uniform locations
		GLint modelLoc = shader.getUniformLocation("model");
		GLint viewLoc = shader.getUniformLocation("view");
		GLint projLoc = shader.getUniformLocation("projection");
		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		// Draw the loaded model
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		objModel.render(&shader);
		
		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(2.0f, -1.75f, 0.0f));
		model2 = glm::scale(model2, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		objModel2.render(&shader);

		glm::mat4 model3;
		model3 = glm::translate(model3, glm::vec3(-2.0f, -1.75f, 0.0f));
		model3 = glm::scale(model3, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model3));
		objModel3.render(&shader);
		
		shader.turnOff();

		





		windowManager->swapTheBuffers();
	}
}

void GLApplication::destroy() {
	if (windowManager) {
		delete windowManager;
		windowManager = nullptr;
	}

	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glDeleteBuffers(1, &EBO);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VAO);

}

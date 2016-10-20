

#include "Headers/GLApplication.h"

Plano plano;
Shader shader;

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
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	shader.initialize("Shaders/Color.vs", "Shaders/Color.fs");
	plano.init();
	plano.load();

}
void GLApplication::applicationLoop() {
	bool processInput = true;
	while (processInput) {
		processInput = windowManager->processInput(true);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
		shader.turnOn();
		//GLfloat timeValue = TimeManager::Instance().GetTime() - lastTime;

		plano.render();

		// Create transformations
		glm::mat4 view;
		glm::mat4 projection;
		view = glm::scale(view, glm::vec3(0.7f, 0.7f, 0.7f));
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, 0.0f));


		/*view = glm::rotate(view,
			glm::radians(windowManager->inputManager.getPitch()),
			glm::vec3(1, 0, 0));
		view = glm::rotate(view,
			glm::radians(windowManager->inputManager.getYaw()),
			glm::vec3(0, 1, 0));
		glm::vec3 cameraPos = windowManager->inputManager.getCameraPos();
		view = glm::translate(view,
			glm::vec3(-cameraPos.x, -cameraPos.y, -cameraPos.z));*/




		projection = glm::ortho(-0.5f, 0.5f, -0.5f, 0.5f, 0.1f, 10.0f);

		//projection = glm::ortho(view,glm::vec3(0.0f,0.0f,0.0f));
		// Get their uniform location
		shader.getUniformLocation("model");
		GLint modelLoc = shader.getUniformLocation("model");
		GLint viewLoc = shader.getUniformLocation("view");
		GLint projLoc = shader.getUniformLocation("projection");
		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		// Note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glm::mat4 model;

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));



		//glBindVertexArray(VAO);
		/*glDrawElements( GL_TRIANGLES, 36, GL_UNSIGNED_INT,
		(GLvoid*) (sizeof(GLuint) * 0));*/
		//glBindVertexArray(0);



		shader.turnOff();





		windowManager->swapTheBuffers();
	}
}

void GLApplication::destroy() {
	if (windowManager) {
		delete windowManager;
		windowManager = nullptr;
	}
}

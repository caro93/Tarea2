

#include "Headers/GLApplication.h"
#include "Headers/Colision.h"

Shader shader;
Shader shader2;
Shader shader3;
Shader shader4;
Sphere sphere(1.0, 25, 25, MODEL_MODE::VERTEX_LIGHT_COLOR);
GLuint VAO, VBO, EBO;
Plano plano;
Caja caja(1.0);


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
	shader2.initialize("Shaders/lampShader.vs", "Shaders/lampShader.fs");


	sphere.init();
	sphere.load();
	caja.init();
	caja.load();

	shader3.initialize("Shaders/Color.vs", "Shaders/Color.fs");
	plano.init();
	plano.load();

	//shader4.initialize("Shaders/lampShader.vs", "Shaders/lampShader.fs");
	
}
void GLApplication::applicationLoop() {
	bool processInput = true;
	glm::vec3 modelPositions[] =
		{ glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(10.0f, 5.0f, -15.0f),
		glm::vec3(-15.5f, -2.2f, -2.5f)};

	glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
	Model objModel("objects/cat/cat.obj");
	Model objModel2("objects/Charizard/Charizard.obj");
	Model objModel3("objects/Rabbit/Rabbit.obj");
	Model objModel4("objects/Charizard/Charizard.obj");

	SBB sbb1 = getSBB(objModel.getMeshes());
	SBB sbb2 = getSBB(objModel2.getMeshes());
	SBB sbb3 = getSBB(objModel3.getMeshes());
	SBB sbb4 = getSBB(objModel4.getMeshes());
	AABB aabb1 = getAABB(objModel.getMeshes());
	AABB aabb2 = getAABB(objModel2.getMeshes());
	AABB aabb3 = getAABB(objModel3.getMeshes());
	AABB aabb4 = getAABB(objModel4.getMeshes());
	while (processInput) {
		processInput = windowManager->processInput(true);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glm::vec4 viewport = glm::vec4(0.0f, 0.0f, WindowManager::screenWidth,
			WindowManager::screenHeight);

		
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
		model = glm::translate(model, glm::vec3(0.0f, -2.75f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		objModel.render(&shader);
		
		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(0.0f, -1.75f, 0.0f));
		model2 = glm::scale(model2, glm::vec3(0.1f, 0.1f, 0.1f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		objModel2.render(&shader);

		glm::mat4 model3;
		model3 = glm::translate(model3, glm::vec3(-12.0f, -2.75f, 0.0f));
		model3 = glm::scale(model3, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model3));
		objModel3.render(&shader);

		/*glm::mat4 model4;
		model4 = glm::translate(model4, glm::vec3(6.0f, -2.75f, -10.0f));
		model4 = glm::scale(model4, glm::vec3(0.1f,0.1f,0.1f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model4));
		objModel4.render(&shader);
		*/
		shader.turnOff();

		

		shader2.turnOn();
		modelLoc = shader2.getUniformLocation("model");
		viewLoc = shader2.getUniformLocation("view");
		projLoc = shader2.getUniformLocation("projection");

		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		//Primer modelo con caja envolvente
		model = glm::translate(model,
			glm::vec3(sbb1.center.x, sbb1.center.y, sbb1.center.z));
		model = glm::scale(model,
			glm::vec3(aabb1.max.x - aabb1.min.x, aabb1.max.y - aabb1.min.y, aabb1.max.z - aabb1.min.z));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		caja.render();

		//Segundo modelo con esfera envolvente
		/*model2 = glm::translate(model2,
			glm::vec3(sbb2.center.x, sbb2.center.y, sbb2.center.z));
		model2 = glm::scale(model2,
			glm::vec3(sbb2.ratio, sbb2.ratio, sbb2.ratio));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		sphere.render();*/

		//Segundo modelo con caja envolvente

		model2 = glm::translate(model2,
			glm::vec3(aabb2.center.x,aabb2.center.y,aabb2.center.z));
		model2 = glm::scale(model2,
			glm::vec3(aabb2.max.x - aabb2.min.x, aabb2.max.y - aabb2.min.y, aabb2.max.z - aabb2.min.z));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		
		caja.render();

		//Tercer modelo con esfera envolvente
		model3 = glm::translate(model3,
			glm::vec3(sbb3.center.x, sbb3.center.y, sbb3.center.z));
		model3 = glm::scale(model3,
			glm::vec3(sbb3.ratio, sbb3.ratio, sbb3.ratio));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model3));
		sphere.render();

		/*model3 = glm::scale(model3,
			glm::vec3(aabb3.dist, aabb3.dist, aabb3.dist));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model3));
		caja.render();*/

		/*model3 = glm::scale(model3,
			glm::vec3(aabb1.dist, aabb1.dist, aabb1.dist));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model3));
		caja.render();*/
		
		//Cuarto modelo con esfera envolvente
		/*model4 = glm::translate(model4,
			glm::vec3(sbb4.center.x, sbb4.center.y, sbb4.center.z));
		model4 = glm::scale(model4,
			glm::vec3(sbb4.ratio, sbb4.ratio, sbb4.ratio));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model4));
		sphere.render();
		
		*/
		shader2.turnOff();


		shader3.turnOn();
		
		modelLoc = shader3.getUniformLocation("model");
		viewLoc = shader3.getUniformLocation("view");
		projLoc = shader3.getUniformLocation("projection");
		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		// Note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		model = glm::scale(model, glm::vec3(100.0f, 50.0f, 70.0f));
		model = glm::translate(model, glm::vec3(0.0f, -0.05f, 0.0f));
		

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		plano.render();
		shader3.turnOff();




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

#include <GL/glew.h>


#include "Headers/GLApplication.h"



Plano::Plano():
	VAO(0), VBO(0), EBO(0) {
}

Plano::~Plano() {

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glDeleteBuffers(1, &EBO);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VAO);

}

void Plano::init() {
	vertices.resize(4);
	indices.resize(6); 
	vertices[0].pos = glm::vec3(0.5f, 0.0f, -0.5f);
	vertices[1].pos = glm::vec3(-0.5f, 0.0f, -0.5f);
	vertices[2].pos = glm::vec3(-0.5f, 0.0f, 0.5f);
	vertices[3].pos = glm::vec3(0.5f, 0.0f, 0.5f);

	vertices[0].color = glm::vec3(1.0f, 1.0f, 1.0f);
	vertices[1].color = glm::vec3(1.0f, 1.0f, 1.0f);
	vertices[2].color = glm::vec3(1.0f, 1.0f, 1.0f);
	vertices[3].color = glm::vec3(1.0f, 1.0f, 1.0f);

	vertices[0].textcoord = glm::vec2{ 1.0f, 1.0f };
	vertices[1].textcoord = glm::vec2{ 0.0f, 1.0f };
	vertices[2].textcoord = glm::vec2{ 0.0f, 0.0f };
	vertices[3].textcoord = glm::vec2{ 1.0f, 0.0f };

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 3;
	indices[3] = 1;
	indices[4] = 2;
	indices[5] = 3;
	
}

void Plano::load() {

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * (sizeof(glm::vec3) * 2 + sizeof(glm::vec2)),
		vertices.data(),
		GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
		indices.data(),
		GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]),
		(GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]),
		(GLvoid*) sizeof(vertices[0].pos));
	glEnableVertexAttribArray(1);
	// Texture Mapping attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]),
		(GLvoid*)(sizeof(vertices[0].color) + sizeof(vertices[0].pos)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO

	texture1 = new Texture(GL_TEXTURE_2D, "Textures/pasto.png");
	texture1->load();

}

void Plano::render() {

	// Bind Texture
	texture1->bind(GL_TEXTURE0);
	glUniform1i(shader.getUniformLocation("ourTexture"), 0);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

}


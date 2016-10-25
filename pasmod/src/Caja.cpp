#include <GL/glew.h>


#include "Headers/GLApplication.h"



Caja::Caja(float tam) :
tam(tam), VAO(0), VBO(0), EBO(0) {
}

Caja::~Caja() {

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glDeleteBuffers(1, &EBO);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VAO);

}

void Caja::init() {
	vertices.resize(8);
	indices.resize(36);
	vertices[0].position = glm::vec3(0.5f, -0.5f, -0.5f);
	vertices[1].position = glm::vec3(-0.5f, -0.5f, -0.5f);
	vertices[2].position = glm::vec3(-0.5f, -0.5f, 0.5f);
	vertices[3].position = glm::vec3(0.5f, -0.5f, 0.5f);
	vertices[4].position = glm::vec3(0.5f, 0.5f, -0.5f);
	vertices[5].position = glm::vec3(-0.5f, 0.5f, -0.5f);
	vertices[6].position = glm::vec3(-0.5f, 0.5f, 0.5f);
	vertices[7].position = glm::vec3(0.5f, 0.5f, 0.5f);

	vertices[0].color = glm::vec3(0.0f, 0.0f, 1.0f);
	vertices[1].color = glm::vec3(0.0f, 0.0f, 1.0f);
	vertices[2].color = glm::vec3(0.0f, 0.0f, 1.0f);
	vertices[3].color = glm::vec3(0.0f, 0.0f, 1.0f);
	vertices[4].color = glm::vec3(0.0f, 0.0f, 1.0f);
	vertices[5].color = glm::vec3(0.0f, 0.0f, 1.0f);
	vertices[6].color = glm::vec3(0.0f, 0.0f, 1.0f);
	vertices[7].color = glm::vec3(0.0f, 0.0f, 1.0f);

	//inferior
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 3;
	indices[3] = 2;
	indices[4] = 1;
	indices[5] = 3;
	//Derecho
	indices[6] = 0;
	indices[7] = 4;
	indices[8] = 7;
	indices[9] = 3;
	indices[10] = 0;
	indices[11] = 7;
	//Arriba
	indices[12] = 4;
	indices[13] = 5;
	indices[14] = 7;
	indices[15] = 6;
	indices[16] = 5;
	indices[17] = 7;
	//Izquierdo
	indices[18] = 6;
	indices[19] = 5;
	indices[20] = 1;
	indices[21] = 2;
	indices[22] = 6;
	indices[23] = 1;
	//Delante
	indices[24] = 7;
	indices[25] = 6;
	indices[26] = 2;
	indices[27] = 3;
	indices[28] = 7;
	indices[29] = 2;
	//Detrás
	indices[30] = 4;
	indices[31] = 0;
	indices[32] = 1;
	indices[33] = 5;
	indices[34] = 4;
	indices[35] = 1;

}

void Caja::load() {

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
		(GLvoid*) sizeof(vertices[0].position));
	glEnableVertexAttribArray(1);
	// Texture Mapping attribute
	

	glBindVertexArray(0); // Unbind VAO


}

void Caja::render() {

	
	glBindVertexArray(VAO);
	glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT,
		(GLvoid*)(sizeof(GLuint) * 0));
	glBindVertexArray(0);

}

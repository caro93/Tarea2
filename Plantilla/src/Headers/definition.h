
#ifndef HEADERS_DEFINITION_H_
#define HEADERS_DEFINITION_H_

#include <glm/glm.hpp>
#include <GL/glew.h>

typedef struct _VertexColorTexture {

	_VertexColorTexture() {
	}

	_VertexColorTexture(glm::vec3 pos, glm::vec3 color, glm::vec2 textcoord) {
		this->pos = pos;
		this->color = color;
		this->textcoord = textcoord;
	}

	glm::vec3 pos;
	glm::vec3 color;
	glm::vec2 textcoord;
} VertexColorTexture;

#endif /* HEADERS_DEFINITION_H_ */

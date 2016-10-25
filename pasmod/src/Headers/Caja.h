#ifndef CAJA_H_
#define CAJA_H_

#include <vector>

#define _USE_MATH_DEFINES
#include <math.h>

#include "definition.h"
#include "Shader.h"
//#include "Texture.h"

class Caja {
public:
	Caja(float tam);
	void init();
	void load();
	void render();
	virtual ~Caja();
private:
	std::vector<VertexColor> vertices;
	std::vector<GLuint> indices;
	float tam;
	MODEL_MODE mode;
	GLuint VAO, VBO, EBO;
	Shader shader;
	
};

#endif /* CAJA_H_ */

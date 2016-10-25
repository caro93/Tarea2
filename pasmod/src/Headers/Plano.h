#ifndef PLANO_H_
#define PLANO_H_

#include <vector>

#define _USE_MATH_DEFINES
#include <math.h>

#include "definition.h"
#include "Shader.h"
//#include "Texture.h"

class Plano {
public:
	Plano();
	void init();
	void load();
	void render();
	virtual ~Plano();
private:
	std::vector<VertexColorTexture> vertices;
	std::vector<GLuint> indices;
	float ancho;
	float largo;

	GLuint VAO, VBO, EBO;
	Shader shader;
	Texture * texture1;
};

#endif /* PLANO_H_ */

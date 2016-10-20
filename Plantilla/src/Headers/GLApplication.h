

#ifndef GLAPPLICATION_H_
#define GLAPPLICATION_H_

#include <stdlib.h>

#include <GL/glew.h>

#include "WindowManager.h"
#include "Plano.h"
#include "Shader.h"
#include "CameraFPS.h"
#include "TimeManager.h"

class GLApplication {
public:

	GLApplication();
	~GLApplication();

	void GLMain();
	void initialize();
	void applicationLoop();
	void destroy();

	void setWindowManager(WindowManager * windowManager) {
		this->windowManager = windowManager;
	}

	WindowManager * getWindowManager() {
		return windowManager;
	}

	CameraFPS* getCamera() {
		return camera;
	}

	void setCamera(CameraFPS* camera) {
		this->camera = camera;
	}

protected:
	WindowManager * windowManager;
	CameraFPS * camera;

};

#endif /* GLAPPLICATION_H_ */

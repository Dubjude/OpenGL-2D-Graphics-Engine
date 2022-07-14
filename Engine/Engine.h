#pragma once

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

namespace mem
{ // temp only

	class Engine
	{
	public:
		Engine(unsigned int _winWidth, unsigned int _winHeight);
		void run();

	private:
		void setupWindow();
		void loop(VAO& VAO1);
		void destroy(VAO& VAO1, VBO& VBO1);
		void setupVertices();

		unsigned int winWidth;
		unsigned int winHeight;

		float scale = 1.0f;

		GLFWwindow* window;
		Shader shaderProgram;
		std::vector<float> vertices;
	};

}

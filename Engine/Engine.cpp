#include"Engine.h"

namespace mem
{ // temp only

	Engine::Engine(unsigned int _winWidth, unsigned int _winHeight)
	{
		winWidth = _winWidth;
		winHeight = _winHeight;
	}


	void Engine::run()
	{
		setupWindow();
		setupVertices();

		shaderProgram.LinkShader("../Engine/default.glsl");

		VAO VAO1;
		VAO1.Bind();

		VBO VBO1(vertices.data(), sizeof(float) * vertices.size());

		VAO1.LinkAttrib(VBO1, 0, 2, GL_FLOAT, 2 * sizeof(float), (void*)0);

		VAO1.Unbind();
		VBO1.Unbind();

		shaderProgram.Activate();
		shaderProgram.setVec2("screenSize", winWidth, winHeight);

		loop(VAO1);
		destroy(VAO1, VBO1);
	}
	void Engine::setupWindow()
	{
		glfwInit();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		window = glfwCreateWindow(winWidth, winHeight, "Fractals", NULL, NULL);
		glfwSetWindowPos(window, (1920 / 2) - (winWidth / 2), 30);
		glfwMakeContextCurrent(window);
		gladLoadGL();
		glViewport(0, 0, winWidth, winWidth);
	}

	void Engine::loop(VAO& VAO1)
	{
		double previousTime = glfwGetTime();
		int fps = 0;
		while (!glfwWindowShouldClose(window))
		{
			if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
			{
				scale += 0.05f;
			}
			if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
			{
				scale -= 0.05f;
			}
			if (scale < 0.0) { scale = 0.01; }
			double xpos, ypos;
			glfwGetCursorPos(window, &xpos, &ypos);

			shaderProgram.setVec2("mousePos", xpos, ypos);
			shaderProgram.setFloat("scale", scale);

			// --- counting frames
			double currentTime = glfwGetTime();
			fps++;
			if (currentTime - previousTime >= 1.0f)
			{
				std::stringstream ss;
				ss << "Fractals" << " [" << fps << " FPS] Mouse: [" << xpos << ", " << ypos << "] Scale: [" << scale << "]";
				glfwSetWindowTitle(window, ss.str().c_str());
				fps = 0;
				previousTime = currentTime;
			}

			// ----- draw sequence ----- //
			glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			shaderProgram.Activate();
			VAO1.Bind();
			glDrawArrays(GL_TRIANGLES, 0, (GLsizei)(sizeof(float) * vertices.size()));

			// update screen
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}

	void Engine::destroy(VAO& VAO1, VBO& VBO1)
	{
		VAO1.Delete();
		VBO1.Delete();

		shaderProgram.Delete();

		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void Engine::setupVertices()
	{
		// trig 1
		vertices.push_back(-1.0f);
		vertices.push_back(-1.0f);
		vertices.push_back(-1.0f);
		vertices.push_back(1.0f);
		vertices.push_back(1.0f);
		vertices.push_back(1.0f);

		// trig 2
		vertices.push_back(-1.0f);
		vertices.push_back(-1.0f);
		vertices.push_back(1.0f);
		vertices.push_back(-1.0f);
		vertices.push_back(1.0f);
		vertices.push_back(1.0f);
	}

}
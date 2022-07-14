#include "Window.h"
/*#include "pch.h"

namespace mem
{
	Window::Window(int32_t width, int32_t height, const char* title)
	{
		initWindow(width, height, title);
	}

	void Window::initWindow(int32_t width, int32_t height, const char* title)
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		m_Window = glfwCreateWindow(width, height, title, NULL, NULL);
		glfwMakeContextCurrent(m_Window);
		gladLoadGL();
		glViewport(0, 0, width, height);

		m_PreviousTime = glfwGetTime();
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	void Window::setPos(int32_t x, int32_t y)
	{
		glfwSetWindowPos(m_Window, x, y);
	}

	void Window::setTitle(const char* title)
	{
		glfwSetWindowTitle(m_Window, title);
	}

	void Window::fillBackground(const glm::vec3& color)
	{
		glm::vec3 goodColor = colorToNormal(color);
		glClearColor(goodColor.r, goodColor.g, goodColor.b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	int Window::getFPS()
	{
		return m_LastFPS;
	}

	glm::vec2 Window::getMousePos()
	{
		double xpos, ypos;
		glfwGetCursorPos(m_Window, &xpos, &ypos);
		return glm::vec2(xpos, ypos);
	}
	
	void Window::update(Renderer* renderer)
	{
		float currentTime = glfwGetTime();
		m_FPS++;
		if (currentTime - m_PreviousTime >= 1.0f)
		{
			m_LastFPS = m_FPS;
			m_FPS = 0;
			m_PreviousTime = currentTime;
		}

		renderer->refreshBuffers();
		renderer->shaderProgram.Activate();
		renderer->vao.Bind();
		glDrawArrays(GL_TRIANGLES, 0, (GLsizei)(sizeof(float) * renderer->vertices.size()));

		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}
}*/
#pragma once
/*
#include "pch.h"
#include "Draw.h"

namespace mem
{
	class Window
	{
	public:
		Window() {}
		Window(int32_t width, int32_t height, const char* title);
		void initWindow(int32_t width, int32_t height, const char* title);
		~Window();

		Renderer* getRenderer()
		{
			auto tmp = new Renderer();
			return tmp;
		}

		void setPos(int32_t x, int32_t y);
		void setTitle(const char* title);
		void fillBackground(const glm::vec3& color);

		int32_t getFPS();
		glm::vec2 getMousePos();

		void update(Renderer* renderer);

	private:
		GLFWwindow* m_Window;

		float m_PreviousTime;
		int32_t m_FPS = 0;
		int32_t m_LastFPS = 0;
	};
}*/
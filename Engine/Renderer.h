#pragma once

#include "utility.h"
#include "Geometry.h"
#include "Texture.h"
#include "Text.h"

#define initRenderer() mem::Renderer mem::Renderer::s_Instance;

namespace mem
{
	struct Window
	{
		GLFWwindow* window;
		uint32_t width;
		uint32_t height;
		std::string title;
		uint32_t x;
		uint32_t y;

		float aspectRatio()
		{
			return (float)width / (float)height;
		}
	}; 

	class Renderer
	{
	public:
		FT_Library ft;

		/*                       WINDOW STUFF                       */

		static void createWindow(uint32_t width, uint32_t height, const char* title) 
		{ 
			get().IcreateWindow(width, height, title); 
		}
		static void fillBackground(const glm::vec3& color) { get().IfillBackground(color); }
		static void update() { get().Iupdate(); }
		static bool windowShouldClose() { return glfwWindowShouldClose(get().m_Window.window); }

		/*                          SETTERS                         */

		static void setWindowPos(uint32_t x, uint32_t y) { get().IsetPos(x, y); };
		static void setWindowTitle(const std::string& title) { get().IsetTitle(title); }

		/*                          GETTERS                         */

		static uint32_t getFPS() { return get().IgetFPS(); }
		static glm::vec2 getMousePos() { return get().IgetMousePos(); }
		static bool getKeyDown(int32_t key) { return glfwGetKey(get().m_Window.window, key) == GLFW_PRESS; };
		static bool getKeyUp(int32_t key) { return glfwGetKey(get().m_Window.window, key) == GLFW_RELEASE; };
		static bool getMouseButtonDown(int32_t key) { return  glfwGetMouseButton(get().m_Window.window, key) == GLFW_PRESS; };
		static bool getMouseButtonUp(int32_t key) { return  glfwGetMouseButton(get().m_Window.window, key) == GLFW_RELEASE; };

		 
		/*                         TRIANGLES  (kinda useless when u got polygons)                */

		/*static void drawTriangle(const glm::vec3& color, const glm::vec2& a, const glm::vec2& b, const glm::vec2& c)
		{
			get().IdrawTriangle(glm::vec4(color, 255), a, b, c);
		}
		static void drawTriangle(const glm::vec4& color, const glm::vec2& a, const glm::vec2& b, const glm::vec2& c)
		{
			get().IdrawTriangle(color, a, b, c);
		}*/

		/*                         POLYGON                          */

		static void drawPolygon(const glm::vec4& color, const std::vector<glm::vec2>& points)
		{
			get().IdrawFilledPolygon(color, points);
		}
		static void drawPolygon(const glm::vec3& color, const std::vector<glm::vec2>& points)
		{
			get().IdrawFilledPolygon(glm::vec4(color, 255), points);
		}
		static void drawPolygon(const glm::vec4& color, const std::vector<glm::vec2>& points, uint32_t width, bool rounded = true)
		{
			get().IdrawPolygon(color, points, width, rounded);
		}
		static void drawPolygon(const glm::vec3& color, const std::vector<glm::vec2>& points, uint32_t width, bool rounded = true)
		{
			get().IdrawPolygon(glm::vec4(color, 255), points, width, rounded);
		}

		/*                         RECTANGLES                       */

		static void drawRect(const glm::vec3& color, const Rect& rect)
		{
			get().IdrawRect(glm::vec4(color, 255), rect);
		}
		static void drawRect(const glm::vec4& color, const Rect& rect)
		{
			get().IdrawRect(color, rect);
		}
		static void drawRect(const glm::vec3& color, const Rect& rect, uint32_t width, bool rounded = true)
		{
			drawRect(glm::vec4(color, 255), rect, width, rounded);
		}
		static void drawRect(const glm::vec4& color, const Rect& rect, uint32_t width, bool rounded = true)
		{
			get().IdrawLine(color, { rect.x, rect.y }, { rect.x + rect.w, rect.y }, width, rounded);
			get().IdrawLine(color, { rect.x + rect.w, rect.y }, { rect.x + rect.w, rect.y + rect.h }, width, rounded);
			get().IdrawLine(color, { rect.x, rect.y + rect.h }, { rect.x + rect.w, rect.y + rect.h }, width, rounded);
			get().IdrawLine(color, { rect.x, rect.y }, { rect.x, rect.y + rect.h }, width, rounded);
		}

		static void drawRect(const glm::vec3& color, const PolyRect& rect)
		{
			get().IdrawPolyRect(glm::vec4(color, 255), rect);
		}
		static void drawRect(const glm::vec4& color, const PolyRect& rect)
		{
			get().IdrawPolyRect(color, rect);
		}
		static void drawRect(const glm::vec3& color, const PolyRect& rect, uint32_t width, bool rounded = true)
		{
			drawRect(glm::vec4(color, 255), rect, width, rounded);
		}
		static void drawRect(const glm::vec4& color, const PolyRect& rect, uint32_t width, bool rounded = true)
		{
			get().IdrawLine(color, rect.p1, rect.p2, width, rounded);
			get().IdrawLine(color, rect.p3, rect.p4, width, rounded);
			get().IdrawLine(color, rect.p2, rect.p3, width, rounded);
			get().IdrawLine(color, rect.p1, rect.p4, width, rounded);
		}

		/*                          CIRLCLES                        */

		static void drawCircle(const glm::vec3& color, const glm::vec2& pos, uint32_t radius)
		{
			get().IdrawEllipse(glm::vec4(color, 255), pos, radius, radius, radius);
		}
		static void drawCircle(const glm::vec4& color, const glm::vec2& pos, uint32_t radius)
		{
			get().IdrawEllipse(color, pos, radius, radius, radius);
		}
		static void drawCircle(const glm::vec3& color, const glm::vec2& pos, uint32_t radius, uint32_t width)
		{
			get().IdrawEllipse(glm::vec4(color, 255), pos, radius, radius, width);
		}
		static void drawCircle(const glm::vec4& color, const glm::vec2& pos, uint32_t radius, uint32_t width)
		{
			get().IdrawEllipse(color, pos, radius, radius, width);
		}

		/*                          ELLIPSES                        */

		static void drawEllipse(const glm::vec3& color, const glm::vec2& pos, uint32_t radiusX, uint32_t radiusY)
		{
			float width = (radiusX > radiusY) ? radiusX : radiusY;
			get().IdrawEllipse(glm::vec4(color, 255), pos, radiusX, radiusY, width);
		}
		static void drawEllipse(const glm::vec4& color, const glm::vec2& pos, uint32_t radiusX, uint32_t radiusY)
		{
			float width = (radiusX > radiusY) ? radiusX : radiusY;
			get().IdrawEllipse(color, pos, radiusX, radiusY, width);
		}
		static void drawEllipse(const glm::vec3& color, const glm::vec2& pos, uint32_t radiusX, uint32_t radiusY, uint32_t width)
		{
			get().IdrawEllipse(glm::vec4(color, 255), pos, radiusX, radiusY, width);
		}
		static void drawEllipse(const glm::vec4& color, const glm::vec2& pos, uint32_t radiusX, uint32_t radiusY, uint32_t width)
		{
			get().IdrawEllipse(color, pos, radiusX, radiusY, width);
		}

		/*					    	LINES					        */

		static void drawLine(const glm::vec3& color, const glm::vec2& p1, const glm::vec2& p2, uint32_t width, bool rounded = true)
		{
			get().IdrawLine(glm::vec4(color, 255), p1, p2, width, rounded);
		}
		static void drawLine(const glm::vec4& color, const glm::vec2& p1, const glm::vec2& p2, uint32_t width, bool rounded = true)
		{
			get().IdrawLine(color, p1, p2, width, rounded);
		}

		/*					    	BEZIER LINES			        */

		static void drawBezier(const glm::vec3& color, const glm::vec2& p1, const glm::vec2& p2, uint32_t width)
		{
			get().IdrawLine(glm::vec4(color, 255), p1, p2, width);
		}
		static void drawBezier(const glm::vec4& color, const glm::vec2& p1, const glm::vec2& p2, uint32_t width)
		{
			get().IdrawLine(color, p1, p2, width);
		}
		// p3 is control point
		static void drawBezier(const glm::vec3& color, const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& p3, uint32_t width)
		{
			get().IdrawBezier(glm::vec4(color, 255), p1, p2, p3, width);
		}
		// p3 is control point
		static void drawBezier(const glm::vec4& color, const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& p3, uint32_t width)
		{
			get().IdrawBezier(color, p1, p2, p3, width);
		}
		// p3, p4 are control points
		static void drawBezier(const glm::vec3& color, const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& p3, const glm::vec2& p4, uint32_t width)
		{
			get().IdrawBezier(glm::vec4(color, 255), p1, p2, p3, p4, width);
		}
		// p3, p4 are control points
		static void drawBezier(const glm::vec4& color, const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& p3, const glm::vec2& p4, uint32_t width)
		{
			get().IdrawBezier(color, p1, p2, p3, p4, width);
		}

		/*					    	TEXTURES			            */

		static Ref<Texture> loadTexture(const std::string& path)
		{
			return get().IloadTexture(path);
		}

		static Ref<Texture> loadTexture(const Image& image)
		{
			return get().IloadTexture(image);
		}

		static void drawTexture(const Ref<Texture>& texture, const Rect& rect)
		{
			get().IdrawTexture(texture, rect, glm::vec4(255));
		}

		static void drawTexture(const Ref<Texture>& texture, const Rect& rect, const glm::vec3& color)
		{
			get().IdrawTexture(texture, rect, glm::vec4(color, 255));
		}

		static void drawTexture(const Ref<Texture>& texture, const Rect& rect, const glm::vec4& color)
		{
			get().IdrawTexture(texture, rect, color);
		}

		static void drawTexture(const Ref<Texture>& texture, const PolyRect& rect)
		{
			get().IdrawTexture(texture, rect, glm::vec4(255));
		}

		static void drawTexture(const Ref<Texture>& texture, const PolyRect& rect, const glm::vec3& color)
		{
			get().IdrawTexture(texture, rect, glm::vec4(color, 255));
		}

		static void drawTexture(const Ref<Texture>& texture, const PolyRect& rect, const glm::vec4& color)
		{
			get().IdrawTexture(texture, rect, color);
		}

		/*					    	FONTS			                */

		static Ref<Font> loadFont(const std::string& path, uint32_t fontSize)
		{
			return get().IloadFont(path, fontSize);
		}

		static Ref<Font> defaultFont(const std::string& name, uint32_t fontSize)
		{
			return get().IloadFont(get().m_FontShortcuts[name], fontSize);
		}

		static void drawText(const Ref<Font>& font, const std::string& text, const glm::vec2& pos, const glm::vec4& color)
		{
			get().IdrawText(font, text, pos, color);
		}

		// u got no friends
		Renderer(const Renderer&) = delete;

	private:
		// no one likes u
		Renderer() {}
		~Renderer() {}
		static Renderer s_Instance;
		static Renderer& get() { return s_Instance; }

		// for fots so ur life easier
		std::unordered_map<std::string, std::string> m_FontShortcuts = {
			{"Arial","../Fonts/arial.ttf"},
			{"FreeSans","../Fonts/FreeSans.ttf"},
			{"Sans Serif","../Fonts/SansSerif.ttf"},
			{"ComicSans","../Fonts/comicsansms3.ttf"}
		};

		// private stuff
		void IcreateWindow(uint32_t width, uint32_t height, const char* title);
		void IsetPos(uint32_t x, uint32_t y);
		void IsetTitle(const std::string& title);
		void IfillBackground(const glm::vec3& color);
		uint32_t IgetFPS();
		glm::vec2 IgetMousePos();
		void Iupdate();
		void IdrawTriangle(const glm::vec4& color, const glm::vec2& a, const glm::vec2& b, const glm::vec2& c);
		void IdrawFilledPolygon(const glm::vec4& color, const std::vector<glm::vec2>& points);
		void IdrawPolygon(const glm::vec4& color, const std::vector<glm::vec2>& points, float width, bool rounded);
		void IdrawRect(const glm::vec4& color, const Rect& rect);
		void IdrawPolyRect(const glm::vec4& color, const PolyRect& rect);
		void IdrawEllipse(const glm::vec4& color, const glm::vec2& pos, uint32_t radius1, uint32_t radius2, uint32_t width);
		void IdrawLine(const glm::vec4& color, const glm::vec2& p1, const glm::vec2& p2, float width, bool rounded = true);
		void IdrawBezier(const glm::vec4& color, const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& p3, float width);
		void IdrawBezier(const glm::vec4& color, const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& p3, const glm::vec2& p4, float width);
		Ref<Texture> IloadTexture(const std::string& path);
		Ref<Texture> IloadTexture(const Image& image);
		void IdrawTexture(const Ref<Texture>& texture, const Rect& rect, const glm::vec4& color);
		void IdrawTexture(const Ref<Texture>& texture, const PolyRect& rect, const glm::vec4& color); 
		Ref<Font> IloadFont(const std::string& path, uint32_t fontSize); 
		void IdrawText(const Ref<Font>& font, const std::string& text, const glm::vec2& pos, const glm::vec4& color);

		// utility
		void refreshBuffers();
		glm::vec2 convertPos(const glm::vec2& pos);
		
		Window m_Window;

		float m_PreviousTime;
		uint32_t m_FPS, m_LastFPS;

		BatchTriangle m_Triangles;
		BatchCircle m_Circles;
		BatchTexture m_Textures;
	};
}
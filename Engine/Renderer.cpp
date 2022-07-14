#include "Renderer.h"

namespace mem
{
	void Renderer::IcreateWindow(uint32_t width, uint32_t height, const char* title)
	{
		m_Window.width = width;
		m_Window.height = height;
		m_Window.title = title;

		if (!glfwInit()) 
		{
			print("Could not init OpenGL library");
			throw std::exception("Could not init OpenGL library");
		}

		if (FT_Init_FreeType(&ft))
		{
			print("Could not init freetype library");
			throw std::exception("Could not init freetype library");
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_SAMPLES, 4);
		m_Window.window = glfwCreateWindow(width, height, title, NULL, NULL);
		glfwMakeContextCurrent(m_Window.window);

		gladLoadGL();
		glViewport(0, 0, width, height);
		glEnable(GL_BLEND);
		glEnable(GL_MULTISAMPLE);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		m_PreviousTime = glfwGetTime();
		m_FPS = 0;
		m_LastFPS = 0;

		m_Triangles.setup("../Engine/default.glsl");
		m_Circles.setup("../Engine/circle.glsl");
		m_Textures.setup("../Engine/texture.glsl");
	}

	void Renderer::IsetPos(uint32_t x, uint32_t y)
	{
		m_Window.x = x;
		m_Window.y = y;
		glfwSetWindowPos(m_Window.window, x, y);
	}

	void Renderer::IsetTitle(const std::string& title)
	{
		m_Window.title = title;
		glfwSetWindowTitle(m_Window.window, title.c_str());
	}

	void Renderer::IfillBackground(const glm::vec3& color)
	{
		glm::vec3 goodColor = colorToNormal(color);
		glClearColor(goodColor.r, goodColor.g, goodColor.b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	uint32_t Renderer::IgetFPS()
	{
		return m_LastFPS;
	}

	glm::vec2 Renderer::IgetMousePos()
	{
		double xpos, ypos;
		glfwGetCursorPos(m_Window.window, &xpos, &ypos);
		return glm::vec2(xpos, ypos);
	}

	void Renderer::Iupdate()
	{
		float currentTime = glfwGetTime();
		m_FPS++;
		if (currentTime - m_PreviousTime >= 1.0f)
		{
			m_LastFPS = m_FPS;
			m_FPS = 0;
			m_PreviousTime = currentTime;
		}

		refreshBuffers();

		m_Triangles.draw();
		m_Circles.draw();
		m_Textures.draw();

		glfwSwapBuffers(m_Window.window);
		glfwPollEvents();
	}

	void Renderer::refreshBuffers()
	{
		m_Triangles.refreshBuffers();
		m_Circles.refreshBuffers();
		m_Textures.refreshBuffers();
	}

	glm::vec2 Renderer::convertPos(const glm::vec2& pos)
	{
		return glm::vec2
		(
			map(pos.x, 0.0f, m_Window.width, -1.0f, 1.0f),
			map(pos.y, 0.0f, m_Window.height, 1.0f, -1.0f)
		);
	}

	void Renderer::IdrawFilledPolygon(const glm::vec4& color, const std::vector<glm::vec2>& points)
	{
		for (int64_t i = 1; i < points.size() - 1; i++)
		{
			IdrawTriangle(color, points[0], points[i], points[i + 1]);
		}
	}

	void Renderer::IdrawPolygon(const glm::vec4& color, const std::vector<glm::vec2>& points, float width, bool rounded)
	{
		float _width = width / m_Window.width;
		IdrawLine(color, points[0], points[points.size() - 1], width, rounded);
		for (int64_t i = 1; i < points.size(); i++)
		{
			IdrawLine(color, points[i - 1], points[i], width, rounded);
		}
	}

	void Renderer::IdrawTriangle(const glm::vec4& color, const glm::vec2& a, const glm::vec2& b, const glm::vec2& c)
	{
		glm::vec2 _a = convertPos(a);
		glm::vec2 _b = convertPos(b);
		glm::vec2 _c = convertPos(c);
		glm::vec4 _color = colorToNormal(color);

		m_Triangles.addVertex(_a, _color);
		m_Triangles.addVertex(_b, _color);
		m_Triangles.addVertex(_c, _color);
	}

	void Renderer::IdrawRect(const glm::vec4& color, const Rect& rect)
	{
		float _ax = map(rect.x, 0.0f, m_Window.width, -1.0f, 1.0f);
		float _ay = map(rect.y, 0.0f, m_Window.height, 1.0f, -1.0f);
		float _bx = map(rect.x + rect.w, 0.0f, m_Window.width, -1.0f, 1.0f);
		float _by = map(rect.y + rect.h, 0.0f, m_Window.height, 1.0f, -1.0f);
		glm::vec4 _color = colorToNormal(color);

		// triangle one
		m_Triangles.addVertex({ _ax, _ay }, _color);
		m_Triangles.addVertex({ _ax, _by }, _color);
		m_Triangles.addVertex({ _bx, _ay }, _color);

		// triangle two
		m_Triangles.addVertex({ _ax, _by }, _color);
		m_Triangles.addVertex({ _bx, _ay }, _color);
		m_Triangles.addVertex({ _bx, _by }, _color);
	}

	void Renderer::IdrawPolyRect(const glm::vec4& color, const PolyRect& rect)
	{
		glm::vec2 _p1 = convertPos(rect.p1);
		glm::vec2 _p2 = convertPos(rect.p2);
		glm::vec2 _p3 = convertPos(rect.p3);
		glm::vec2 _p4 = convertPos(rect.p4);
		glm::vec4 _color = colorToNormal(color);

		// triangle one
		m_Triangles.addVertex(_p1, _color);
		m_Triangles.addVertex(_p2, _color);
		m_Triangles.addVertex(_p3, _color);

		// triangle two
		m_Triangles.addVertex(_p2, _color);
		m_Triangles.addVertex(_p3, _color);
		m_Triangles.addVertex(_p4, _color);
	}

	void Renderer::IdrawEllipse(const glm::vec4& color, const glm::vec2& pos, uint32_t radius1, uint32_t radius2, uint32_t width)
	{
		float _ax = map(pos.x - radius1, 0.0f, m_Window.width, -1.0f, 1.0f);
		float _ay = map(pos.y - radius2, 0.0f, m_Window.height, 1.0f, -1.0f);
		float _bx = map(pos.x + radius1, 0.0f, m_Window.width, -1.0f, 1.0f);
		float _by = map(pos.y + radius2, 0.0f, m_Window.height, 1.0f, -1.0f);
		glm::vec2 _pos = convertPos(pos);
		glm::vec4 _color = colorToNormal(color);
		float _radius = radius1 * 2.0 / m_Window.width;
		float _radiusRatio = (float)radius2 / (float)radius1;
		float _innerRadius = width * 2.0 / m_Window.width;
		float _ratio = 1.0 / m_Window.aspectRatio();

		// triangle one
		m_Circles.addVertex({ _ax, _ay }, _pos, _radius, _color, _innerRadius, _ratio, _radiusRatio);
		m_Circles.addVertex({ _ax, _by }, _pos, _radius, _color, _innerRadius, _ratio, _radiusRatio);
		m_Circles.addVertex({ _bx, _ay }, _pos, _radius, _color, _innerRadius, _ratio, _radiusRatio);

		// triangle two
		m_Circles.addVertex({ _ax, _by }, _pos, _radius, _color, _innerRadius, _ratio, _radiusRatio);
		m_Circles.addVertex({ _bx, _ay }, _pos, _radius, _color, _innerRadius, _ratio, _radiusRatio);
		m_Circles.addVertex({ _bx, _by }, _pos, _radius, _color, _innerRadius, _ratio, _radiusRatio);
	}

	void Renderer::IdrawLine(const glm::vec4& color, const glm::vec2& p1, const glm::vec2& p2, float width, bool rounded)
	{
		float mag = glm::distance(p1, p2);
		float slope = (p2.y - p1.y) / (p2.x - p1.x);
		float angle = atan(slope);

		glm::vec2 A, B, C, D;
		float slopeA, slopeB, slopeC, slopeD;
		float angleA, angleB, angleC, angleD;

		A = { p1.x + mag, p1.y - width };
		slopeA = (A.y - p1.y) / (A.x - p1.x);
		B = { p1.x + mag, p1.y + width };
		slopeB = (B.y - p1.y) / (B.x - p1.x);
		C = { p1.x, p1.y - width };
		slopeC = (C.y - p1.y) / (C.x - p1.x);
		D = { p1.x, p1.y - width };
		slopeD = (D.y - p1.y) / (D.x - p1.x);

		if ((slope < 0.0f && p2.x < p1.x) || (slope > 0.0f && p2.y < p1.y))
		{
			angleA = atan(slopeA) + angle + PI;
			angleB = atan(slopeB) + angle + PI;
			angleC = 3 * PI / 2 + angle + PI;
			angleD = PI / 2 + angle + PI;
		}
		else
		{
			angleA = atan(slopeA) + angle;
			angleB = atan(slopeB) + angle;
			angleC = 3 * PI / 2 + angle;
			angleD = PI / 2 + angle;
		}

		IdrawTriangle(color,
			{ p1.x + cos(angleA) * mag, p1.y + sin(angleA) * mag },
			{ p1.x + cos(angleB) * mag, p1.y + sin(angleB) * mag },
			{ p1.x + cos(angleC) * width, p1.y + sin(angleC) * width }
		);

		IdrawTriangle(color,
			{ p1.x + cos(angleB) * mag, p1.y + sin(angleB) * mag },
			{ p1.x + cos(angleC) * width, p1.y + sin(angleC) * width },
			{ p1.x + cos(angleD) * width, p1.y + sin(angleD) * width }
		);

		if (rounded)
		{
			IdrawEllipse(color, p1, width, width, width);
			IdrawEllipse(color, p2, width, width, width);
		}
	}

	void Renderer::IdrawBezier(const glm::vec4& color, const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& p3, float width)
	{
		glm::vec2 last = p1;
		float dt = 0.05f;
		for (float t = 0.0f; t <= 1.0f + dt; t += dt)
		{
			glm::vec2 pos = lerp(lerp(p1, p3, t), lerp(p3, p2, t), t);
			mem::Renderer::drawLine(color, last, pos, width);
			last = pos;
		}
	}

	void Renderer::IdrawBezier(const glm::vec4& color, const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& p3, const glm::vec2& p4, float width)
	{
		glm::vec2 last = p1;
		float dt = 0.05f;
		for (float t = 0.0f; t <= 1.0f + dt; t += dt)
		{
			glm::vec2 pos1 = lerp(lerp(p1, p3, t), lerp(p3, p2, t), t);
			glm::vec2 pos2 = lerp(lerp(p3, p4, t), lerp(p4, p2, t), t);
			glm::vec2 pos = lerp(pos1, pos2, t);
			mem::Renderer::drawLine(color, last, pos, width);
			last = pos;
		}
	}

	Ref<Texture> Renderer::IloadTexture(const std::string& path)
	{
		Ref<Texture> temp = std::make_shared<Texture>(path, GL_TEXTURE_2D, m_Textures.getSlot(), GL_RGB, GL_UNSIGNED_BYTE);
		m_Textures.addTexture(temp);
		return temp;
	}

	void Renderer::IdrawTexture(const Ref<Texture>& texture, const Rect& rect, const glm::vec4& color)
	{
		float _ax = map(rect.x, 0.0f, m_Window.width, -1.0f, 1.0f);
		float _ay = map(rect.y, 0.0f, m_Window.height, 1.0f, -1.0f);
		float _bx = map(rect.x + rect.w, 0.0f, m_Window.width, -1.0f, 1.0f);
		float _by = map(rect.y + rect.h, 0.0f, m_Window.height, 1.0f, -1.0f);
		glm::vec4 _color = colorToNormal(color);

		m_Textures.addQuad({ _ax, _ay, _bx, _by }, _color, texture->getID());
	}

	void Renderer::IdrawTexture(const Ref<Texture>& texture, const PolyRect& rect, const glm::vec4& color)
	{
		glm::vec2 _p1 = convertPos(rect.p1);
		glm::vec2 _p2 = convertPos(rect.p2);
		glm::vec2 _p3 = convertPos(rect.p3);
		glm::vec2 _p4 = convertPos(rect.p4);
		glm::vec4 _color = colorToNormal(color);

		m_Textures.addQuad(std::array<glm::vec2, 4>{ _p1, _p2, _p3, _p4 }, _color, texture->getID());
	}

	Ref<Font> Renderer::IloadFont(const std::string& path, uint32_t fontSize)
	{
		FT_Face face;
		if (FT_New_Face(ft, path.c_str(), 0, &face))
		{
			print("Could not open font");
			throw std::exception("Could not open font");
		}
		Ref<Font> font = std::make_shared<Font>(face, fontSize, m_Window.height);
		FT_Done_FreeType(ft);
		return font;
	}
}

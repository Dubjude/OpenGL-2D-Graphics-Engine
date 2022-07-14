#include "Geometry.h"

namespace mem
{
	/*                          TRIANGLES                           */

	void BatchTriangle::setup(const std::string& file)
	{
		m_ShaderProgram.LinkShader(file);
		m_VAO.init();
	}

	void BatchTriangle::draw()
	{
		m_ShaderProgram.Activate();
		m_VAO.Bind();
		glDrawArrays(GL_TRIANGLES, 0, sizeof(float) * m_Vertices.size());
		m_Vertices.clear();
	}

	void BatchTriangle::refreshBuffers()
	{
		m_VAO.Bind();
		VBO VBO1(m_Vertices.data(), sizeof(float) * m_Vertices.size());
		m_VAO.LinkAttrib(VBO1, 0, 2, GL_FLOAT, 6 * sizeof(float), (void*)0);
		m_VAO.LinkAttrib(VBO1, 1, 4, GL_FLOAT, 6 * sizeof(float), (void*)(2 * sizeof(float)));
		m_VAO.Unbind();
		VBO1.Unbind();
	}

	void BatchTriangle::addVertex(const glm::vec2& pos, const glm::vec4& color)
	{
		m_Vertices.reserve(6 * sizeof(float));
		m_Vertices.push_back(pos.x);
		m_Vertices.push_back(pos.y);
		m_Vertices.push_back(color.r);
		m_Vertices.push_back(color.g);
		m_Vertices.push_back(color.b);
		m_Vertices.push_back(color.a);
	}

	/*                           CIRCLES                            */

	void BatchCircle::setup(const std::string& file)
	{
		m_ShaderProgram.LinkShader(file);
		m_VAO.init();
	}

	void BatchCircle::draw()
	{
		m_ShaderProgram.Activate();
		m_VAO.Bind();
		glDrawArrays(GL_TRIANGLES, 0, sizeof(float) * m_Vertices.size());
		m_Vertices.clear();
	}

	void BatchCircle::refreshBuffers()
	{
		m_VAO.Bind();
		VBO VBO2(m_Vertices.data(), sizeof(float) * m_Vertices.size());
		m_VAO.LinkAttrib(VBO2, 0, 2, GL_FLOAT, 12 * sizeof(float), (void*)0);
		m_VAO.LinkAttrib(VBO2, 1, 3, GL_FLOAT, 12 * sizeof(float), (void*)(2 * sizeof(float)));
		m_VAO.LinkAttrib(VBO2, 2, 3, GL_FLOAT, 12 * sizeof(float), (void*)(5 * sizeof(float)));
		m_VAO.LinkAttrib(VBO2, 3, 4, GL_FLOAT, 12 * sizeof(float), (void*)(8 * sizeof(float)));
		m_VAO.Unbind();
		VBO2.Unbind();
	}

	void BatchCircle::addVertex(const glm::vec2& pos, const glm::vec2& center, float radius, const glm::vec4& color, float innerRadius, float ratio, float radiusRatio)
	{
		m_Vertices.reserve(12 * sizeof(float));
		m_Vertices.push_back(pos.x);
		m_Vertices.push_back(pos.y);
		m_Vertices.push_back(radius);
		m_Vertices.push_back(innerRadius);
		m_Vertices.push_back(radiusRatio);
		m_Vertices.push_back(center.x);
		m_Vertices.push_back(center.y);
		m_Vertices.push_back(ratio);
		m_Vertices.push_back(color.r);
		m_Vertices.push_back(color.g);
		m_Vertices.push_back(color.b);
		m_Vertices.push_back(color.a);
	}

	/*                           TEXTURES                           */

	void BatchTexture::setup(const std::string& file)
	{
		m_ShaderProgram.LinkShader(file);
		m_VAO.init();
		for (int32_t x = 0; x < m_MaxSlots; x++)
			m_Indexes[x] = x;
	}

	void BatchTexture::draw()
	{
		m_ShaderProgram.Activate();
		m_ShaderProgram.setSamplerArray("uTexture", m_Indexes, m_MaxSlots);
		for (int32_t i = 0; i < m_MaxSlots; i++) if (m_Textures[i]) m_Textures[i]->Bind();
		m_VAO.Bind();
		glDrawArrays(GL_TRIANGLES, 0, sizeof(float) * m_Vertices.size());
		m_Vertices.clear();
	}

	void BatchTexture::refreshBuffers()
	{
		m_VAO.Bind();
		VBO VBO1(m_Vertices.data(), sizeof(float) * m_Vertices.size());
		m_VAO.LinkAttrib(VBO1, 0, 2, GL_FLOAT, 9 * sizeof(float), (void*)0);
		m_VAO.LinkAttrib(VBO1, 1, 2, GL_FLOAT, 9 * sizeof(float), (void*)(2 * sizeof(float)));
		m_VAO.LinkAttrib(VBO1, 2, 4, GL_FLOAT, 9 * sizeof(float), (void*)(4 * sizeof(float)));
		m_VAO.LinkAttrib(VBO1, 3, 1, GL_FLOAT, 9 * sizeof(float), (void*)(8 * sizeof(float)));
		m_VAO.Unbind();
		VBO1.Unbind();
	}

	void BatchTexture::addVertex(const glm::vec2& pos, const glm::vec4& color, float tex_ID, const glm::vec2& texPos)
	{
		m_Vertices.reserve(9 * sizeof(float));
		m_Vertices.push_back(pos.x);
		m_Vertices.push_back(pos.y);
		m_Vertices.push_back(texPos.x);
		m_Vertices.push_back(texPos.y);
		m_Vertices.push_back(color.r);
		m_Vertices.push_back(color.g);
		m_Vertices.push_back(color.b);
		m_Vertices.push_back(color.a);
		m_Vertices.push_back(tex_ID-1);
	}

	void BatchTexture::addQuad(const glm::vec4& corners, const glm::vec4& color, float tex_ID)
	{
		// triangle 1
		addVertex({ corners.x, corners.y }, color, tex_ID, { 0.0f, 0.0f });
		addVertex({ corners.x, corners.w }, color, tex_ID, { 0.0f, 1.0f });
		addVertex({ corners.z, corners.y }, color, tex_ID, { 1.0f, 0.0f });		

		// triangle 2
		addVertex({ corners.x, corners.w }, color, tex_ID, { 0.0f, 1.0f });
		addVertex({ corners.z, corners.y }, color, tex_ID, { 1.0f, 0.0f });
		addVertex({ corners.z, corners.w }, color, tex_ID, { 1.0f, 1.0f });
	}

	void BatchTexture::addQuad(const std::array<glm::vec2, 4>& corners, const glm::vec4& color, float tex_ID)
	{
		// triangle 1
		addVertex(corners[0], color, tex_ID, {0.0f, 0.0f});
		addVertex(corners[1], color, tex_ID, {0.0f, 1.0f});
		addVertex(corners[2], color, tex_ID, { 1.0f, 0.0f });

		// triangle 2
		addVertex(corners[1], color, tex_ID, { 0.0f, 1.0f });
		addVertex(corners[2], color, tex_ID, { 1.0f, 0.0f });
		addVertex(corners[3], color, tex_ID, { 1.0f, 1.0f });
	}

	void BatchTexture::addTexture(const Ref<Texture>& texture)
	{
		m_Textures[texture->getSlot() - GL_TEXTURE0] = texture;
		m_TexSlot++;
	}
}
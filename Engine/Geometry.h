#pragma once

#include "utility.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "shaderClass.h"
#include "Texture.h"

namespace mem
{
	/*                         SINGLE RENDERERS                        */

	class Geometry
	{
	public:
		virtual void draw() = 0;
	};

	/*                         BATCH RENDERERS                         */

	class BatchGeometry
	{
	public:
		virtual void setup(const std::string& file) = 0;
		virtual void draw() = 0;
		virtual void refreshBuffers() = 0;
		// void addVertex() here
	};

	class BatchTriangle : public BatchGeometry
	{
	public:
		BatchTriangle() = default;
		~BatchTriangle() = default;

		virtual void setup(const std::string& file) override;
		virtual void draw() override;
		virtual void refreshBuffers() override;
		void addVertex(const glm::vec2& pos, const glm::vec4& color);

	private:
		VAO m_VAO;
		Shader m_ShaderProgram;
		std::vector<float> m_Vertices;
	};

	class BatchCircle : public BatchGeometry
	{
	public:
		BatchCircle() = default;
		~BatchCircle() = default;

		virtual void setup(const std::string& file) override;
		virtual void draw() override;
		virtual void refreshBuffers() override;
		void addVertex(const glm::vec2& pos, const glm::vec2& center, float radius, const glm::vec4& color, float innerRadius, float ratio, float radiusRatio);

	private:
		VAO m_VAO;
		Shader m_ShaderProgram;
		std::vector<float> m_Vertices;
	};

	class BatchTexture : public BatchGeometry
	{
	public:
		BatchTexture() = default;
		~BatchTexture() = default;

		virtual void setup(const std::string& file) override;
		virtual void draw() override;
		virtual void refreshBuffers() override;
		void addVertex(const glm::vec2& pos, const glm::vec4& color, float tex_ID, const glm::vec2& texPos);
		void addQuad(const glm::vec4& corners, const glm::vec4& color, float tex_ID);
		void addQuad(const std::array<glm::vec2, 4>& corners, const glm::vec4& color, float tex_ID);
		void addTexture(const Ref<Texture>& texture);
		uint32_t getSlot() { return m_TexSlot; }

	private:
		VAO m_VAO;
		Shader m_ShaderProgram;
		std::vector<float> m_Vertices;

		const static int32_t m_MaxSlots = 32;
		uint32_t m_TexSlot = GL_TEXTURE0;
		std::array<Ref<Texture>, m_MaxSlots> m_Textures;
		int32_t m_Indexes[m_MaxSlots];
	};
}
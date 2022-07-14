#pragma once

#include "Geometry.h"

namespace mem
{
	struct Character
	{
		unsigned int textureID;  // ID handle of the glyph texture
		glm::vec2 size;          // Size of glyph
		glm::vec2 bearing;       // Offset from baseline to left/top of glyph
		unsigned int advance;    // Offset to advance to next glyph
	};

	class Font
	{
	public:
		Font(const FT_Face& _face, uint32_t fontSize, uint32_t windowHeight);
		~Font() = default;

		void draw(const std::string& text, const glm::vec2& pos, float scale, const glm::vec4& color);

		FT_Face face;

	private:
		uint32_t winHeight;
		uint32_t m_VAO, m_VBO;
		Shader m_ShaderProgram;
		std::unordered_map<char, Character> m_Characters;
	};

	// if u too lazy to type
	using Font_ptr = Ref<Font>;
}
#pragma once

#include "utility.h"
#include "shaderClass.h"

namespace mem
{
	class Texture
	{
	public:
		Texture(const std::string& image, uint32_t texType, uint32_t texSlot, uint32_t format, uint32_t pixelType);

		void Bind();
		void Unbind();
		void Delete();

		uint32_t getID() { return ID; }
		uint32_t getType() { return type; }
		uint32_t getSlot() { return slot; }

	private:
		uint32_t ID;
		uint32_t type;
		uint32_t slot;
	};

	// if u too lazy to type
	using Texture_ptr = Ref<Texture>;
}
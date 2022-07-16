#pragma once

#include "utility.h"

namespace mem
{
	struct Image
	{
		unsigned char* pixels;
		uint32_t width, height, numChannels;

		Image(int32_t _width, int32_t _height, int32_t _numChannels)
			: width(_width), height(_height), numChannels(_numChannels)
		{}

		Image(unsigned char* _pixels, int32_t _width, int32_t _height, int32_t _numChannels)
			: pixels(_pixels), width(_width), height(_height), numChannels(_numChannels)
		{}
	};

	class Texture
	{
	public:
		Texture(const std::string& file, uint32_t texType, uint32_t texSlot, uint32_t format, uint32_t pixelType);
		Texture(const Image& image, uint32_t texType, uint32_t texSlot, uint32_t format, uint32_t pixelType);

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
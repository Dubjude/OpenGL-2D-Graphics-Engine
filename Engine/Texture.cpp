#include "Texture.h"

namespace mem
{
	Texture::Texture(const std::string& image, uint32_t texType, uint32_t texSlot, uint32_t format, uint32_t pixelType)
		: type(texType), slot(texSlot)
	{
		glGenTextures(1, &ID);
		glActiveTexture(texSlot);
		glBindTexture(texType, ID);

		glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		int32_t widthImg, heightImg, nrChannels;
		//stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(image.c_str(), &widthImg, &heightImg, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, data);
			glGenerateMipmap(texType);
		}
		else
		{
			print("Failed to load texture");
		}
		stbi_image_free(data);

		glBindTexture(texType, 0);
	}

	void Texture::Bind()
	{
		glActiveTexture(slot);
		glBindTexture(type, ID);
	}

	void Texture::Unbind()
	{
		glBindTexture(type, 0);
	}

	void Texture::Delete()
	{
		glDeleteTextures(1, &ID);
	}

}
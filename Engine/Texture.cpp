#include "Texture.h"
#include "shaderClass.h"

namespace mem
{
	Texture::Texture(const std::string& file, uint32_t texType, uint32_t texSlot, uint32_t format, uint32_t pixelType)
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
		unsigned char* data = stbi_load(file.c_str(), &widthImg, &heightImg, &nrChannels, 0);
		//stbi_set_flip_vertically_on_load(true);
		if (data)
		{
			glTexImage2D(texType, 0, GL_RGB, widthImg, heightImg, 0, format, pixelType, data);
			glGenerateMipmap(texType);
		}
		else
		{
			print("Failed to load texture");
		}
		stbi_image_free(data);

		glBindTexture(texType, 0);
	}

	Texture::Texture(const Image& image, uint32_t texType, uint32_t texSlot, uint32_t format, uint32_t pixelType)
		: type(texType), slot(texSlot)
	{
		glGenTextures(1, &ID);
		glActiveTexture(texSlot);
		glBindTexture(texType, ID);

		glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		/*int32_t widthImg, heightImg, nrChannels;
		unsigned char* data = new unsigned char[heightImg * widthImg * 4];
		for (int y = 0; y < heightImg; y++) {
			for (int x = 0; x < widthImg; x++)
			{
				data[4 * (y * widthImg + x) + 0] = 255;
				data[4 * (y * widthImg + x) + 1] = 0;
				data[4 * (y * widthImg + x) + 2] = 0;
				data[4 * (y * widthImg + x) + 3] = 255;
			}
		}*/

		glTexImage2D(texType, 0, GL_RGBA, image.width, image.height, 0, format, pixelType, image.pixels);
		glGenerateMipmap(texType);

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
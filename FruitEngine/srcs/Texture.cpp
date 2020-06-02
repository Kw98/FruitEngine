#include <iostream>

#include "Texture.h"
#include "stb_image.h"

namespace FE {

	void	Texture::InitFromFile(const std::string& file, bool alpha)
	{
		int	width;
		int	height;
		int	nbchannel;

		unsigned char* data = stbi_load(file.c_str(), &width, &height, &nbchannel, 0);
		if (data)
			Generate(width, height, data);
		else
			std::cerr << "Couldn't load file: " << file << std::endl;
		stbi_image_free(data);
	}

	void	Texture::Generate(std::size_t width, std::size_t height, unsigned char* data)
	{
		_width = width;
		_height = height;
		glGenTextures(1, &_id);
		glBindTexture(GL_TEXTURE_2D, _id);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _wrapS);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _wrapT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _filterMin);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _filterMax);

		glTexImage2D(GL_TEXTURE_2D, 0, _internalFormat, _width, _height, 0, _imageFormat, GL_UNSIGNED_BYTE, data);
		glBindTexture(GL_TEXTURE_2D, 0);
		//glGenerateMipmap(GL_TEXTURE_2D);
	}

}
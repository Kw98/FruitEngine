#pragma once

#include <string>

#include <GL/glew.h>
#include <GL/gl.h>

namespace FE {

	class Texture {
	public:
		Texture() : _width(0), _height(0), _internalFormat(GL_RGB), _imageFormat(GL_RGB), _wrapS(GL_REPEAT), _wrapT(GL_REPEAT), _filterMin(GL_LINEAR), _filterMax(GL_LINEAR) {}
		~Texture() {}

		void	InitFromFile(const std::string& file, bool alpha);
		inline void	Bind() { glBindTexture(GL_TEXTURE_2D, _id); }
		inline void	UnBind() { glBindTexture(GL_TEXTURE_2D, 0); }

	private:
		void	Generate(std::size_t width, std::size_t height, unsigned char *data);

		std::size_t	_width;
		std::size_t	_height;
		// texture Format
		GLuint _internalFormat; // format of texture object
		GLuint _imageFormat; // format of loaded image
		// texture configuration
		GLuint _wrapS; // wrapping mode on S axis
		GLuint _wrapT; // wrapping mode on T axis
		GLuint _filterMin; // filtering mode if texture pixels < screen pixels
		GLuint _filterMax;
		GLuint	_id;
	};

}
#pragma once

#include <string>

#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>

namespace FE {

	enum class shaderlog {
		SHADER,
		PROGRAM
	};

	class Shader {
	public:
		Shader() : _init(false), _programid(0), _vshaderid(0), _fshaderid(0) {}
		~Shader() {}

		void	InitFromFiles(const std::string& vshaderfile, const std::string fshaderfile);
		void	InitFromStrings(const std::string& vshader, const std::string fshader);

		void	Use();
		void	Disable();

		void    SetFloat(const char* name, float value);
		void    SetInteger(const char* name, int value);
		void    SetVector2f(const char* name, const glm::vec2& value);
		void    SetVector3f(const char* name, const glm::vec3& value);
		void    SetVector4f(const char* name, const glm::vec4& value);
		void    SetMatrix4(const char* name, const glm::mat4& matrix);
	
	private:
		GLuint	CompileShader(const std::string& shadersrc, GLenum shadertype);
		void	GetLogs(GLuint shaderId, shaderlog logType);
		std::string	LoadFile(const std::string& shaderfile);

		bool	_init;
		GLuint	_programid;
		GLuint	_vshaderid;
		GLuint	_fshaderid;
	};

}
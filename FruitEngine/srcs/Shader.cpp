#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

namespace FE {

	void	Shader::InitFromFiles(const std::string& vshaderfile, const std::string fshaderfile)
	{
		std::string vshadersrc = LoadFile(vshaderfile);
		std::string fshadersrc = LoadFile(fshaderfile);
		InitFromStrings(vshaderfile, fshaderfile);
	}

	std::string	Shader::LoadFile(const std::string& shaderfile)
	{
		std::ifstream	file(shaderfile.c_str());
		if (!file.good())
			std::cerr << "Error: couldn't open file " << shaderfile << std::endl;
		std::stringstream	vsrc;
		vsrc << file.rdbuf();
		return vsrc.str();
	}

	void	Shader::InitFromStrings(const std::string& vshader, const std::string fshader)
	{
		_vshaderid = CompileShader(vshader, GL_VERTEX_SHADER);
		_fshaderid = CompileShader(fshader, GL_FRAGMENT_SHADER);
		_programid = glCreateProgram();
		glAttachShader(_programid, _vshaderid);
		glAttachShader(_programid, _fshaderid);
		glLinkProgram(_programid);

		GLint isLinked = 0;
		glGetProgramiv(_programid, GL_LINK_STATUS, &isLinked);
		if (!isLinked) {
			GetLogs(_programid, shaderlog::PROGRAM);
			glDeleteProgram(_programid);
			glDeleteShader(_vshaderid);
			glDeleteShader(_fshaderid);
			return;
		}

		glDetachShader(_programid, _vshaderid);
		glDetachShader(_programid, _fshaderid);
	}

	void	Shader::Use()
	{
		glUseProgram(_programid);
	}

	void	Shader::Disable()
	{
		glUseProgram(0);
	}

	void    Shader::SetFloat(const char* name, float value)
	{
		glUniform1f(glGetUniformLocation(_programid, name), value);
	}

	void    Shader::SetInteger(const char* name, int value)
	{
		glUniform1i(glGetUniformLocation(_programid, name), value);
	}

	void    Shader::SetVector2f(const char* name, const glm::vec2& value)
	{
		glUniform2f(glGetUniformLocation(_programid, name), value.x, value.y);
	}

	void    Shader::SetVector3f(const char* name, const glm::vec3& value)
	{
		glUniform3f(glGetUniformLocation(_programid, name), value.x, value.y, value.z);
	}

	void    Shader::SetVector4f(const char* name, const glm::vec4& value)
	{
		glUniform4f(glGetUniformLocation(_programid, name), value.x, value.y, value.z, value.w);
	}

	void    Shader::SetMatrix4(const char* name, const glm::mat4& matrix)
	{
		glUniformMatrix4fv(glGetUniformLocation(_programid, name), 1, false, glm::value_ptr(matrix));
	}

	GLuint	Shader::CompileShader(const std::string& shadersrc, GLenum shadertype)
	{
		if (shadertype != GL_VERTEX_SHADER && shadertype != GL_FRAGMENT_SHADER)
			return 0;
		GLuint	shaderId = glCreateShader(shadertype);
		const char* shaderSourceChars = shadersrc.c_str();
		glShaderSource(shaderId, 1, &shaderSourceChars, NULL);
		glCompileShader(shaderId);
		GLint success = 0;
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
		if (!success) {
			GetLogs(shaderId, shaderlog::SHADER);
			glDeleteShader(shaderId);
		}
		return shaderId;
	}

	void	Shader::GetLogs(GLuint shaderId, shaderlog logType)
	{
		GLint	logLength;
		if (logType == shaderlog::SHADER)
			glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);
		else
			glGetProgramiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);
		std::vector<GLchar> errorLog(logLength);
		glGetShaderInfoLog(shaderId, logLength, &logLength, &errorLog[0]);
		std::string	log(errorLog.begin(), errorLog.end());
		std::cerr << "Shader errorlog: " << log << std::endl;
	}

}
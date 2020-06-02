#pragma once

#include <string>
#include <unordered_map>

#include "Shader.h"
#include "Texture.h"

namespace FE {

	class RessourceManager {
	public:

		static Shader&	LoadShaderFromFile(const std::string& vshaderfile, const std::string& fshaderfile, const std::string& name);
		static Shader& LoadShaderFromString(const std::string& vshader, const std::string& fshader, const std::string& name);
		static Texture& LoadTextureFromFile(const std::string& texturefile, bool alpha, const std::string& name);

		static Shader& GetShader(const std::string& name) { return _shaders[name]; }
		static Texture& GetTexture(const std::string& name) { return _textures[name]; }


	private:
		RessourceManager() {}

		static std::unordered_map<std::string, Shader>	_shaders;
		static std::unordered_map<std::string, Texture>	_textures;

	};

}
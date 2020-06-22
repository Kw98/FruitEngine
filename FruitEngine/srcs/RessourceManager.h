#pragma once

#include <string>
#include <unordered_map>

#include "Shader.h"
#include "Texture.h"

namespace FE {

	class RessourceManager {
	public:

		static Shader&	LoadShaderFromFile(const std::string& vshaderfile, const std::string& fshaderfile, const std::string& name) {
			Shader	s;
			s.InitFromFiles(vshaderfile, fshaderfile);
			_shaders[name] = std::move(s);
			return _shaders[name];
		}

		static Shader& LoadShaderFromString(const std::string& vshader, const std::string& fshader, const std::string& name) {
			Shader	s;
			s.InitFromStrings(vshader, fshader);
			_shaders[name] = std::move(s);
			return _shaders[name];
		}

		static Texture& LoadTextureFromFile(const std::string& texturefile, bool alpha, const std::string& name) {
			Texture	t;
			t.InitFromFile(texturefile, alpha);
			_textures[name] = std::move(t);
			return _textures[name];
		}

		static Shader& GetShader(const std::string& name) { return _shaders[name]; }
		static Texture& GetTexture(const std::string& name) { return _textures[name]; }


	private:
		RessourceManager() {}

		static std::unordered_map<std::string, Shader>	_shaders;
		static std::unordered_map<std::string, Texture>	_textures;
	};

	std::unordered_map<std::string, Shader>	RessourceManager::_shaders;
	std::unordered_map<std::string, Texture>	RessourceManager::_textures;
}
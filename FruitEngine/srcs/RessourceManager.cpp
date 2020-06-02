#include "RessourceManager.h"

namespace FE {

	Shader& RessourceManager::LoadShaderFromFile(const std::string& vshaderfile, const std::string& fshaderfile, const std::string& name)
	{
		Shader	s;
		s.InitFromFiles(vshaderfile, fshaderfile);
		_shaders[name] = std::move(s);
		return _shaders[name];
	}

	Shader& RessourceManager::LoadShaderFromString(const std::string& vshader, const std::string& fshader, const std::string& name)
	{
		Shader	s;
		s.InitFromStrings(vshader, fshader);
		_shaders[name] = std::move(s);
		return _shaders[name];
	}

	Texture& RessourceManager::LoadTextureFromFile(const std::string& texturefile, bool alpha, const std::string& name)
	{
		Texture	t;
		t.InitFromFile(texturefile, alpha);
		_textures[name] = std::move(t);
		return _textures[name];
	}

}
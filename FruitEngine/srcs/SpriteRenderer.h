#pragma once

#include <string>
#include <vector>
#include <functional>

#include "GameObject.h"
#include "Transform.h"
#include "Sprite.h"
#include "Texture.h"
#include "Shader.h"

namespace FE {

	enum class VBO {
		POSITION,
		COLOR,
		NORMAL,
		TEXTCOORD
	};

	void	__default_setup_spriterenderer(GLuint& vao, GLuint vbo[4]);
	void	__default_draw_spriterenderer(FE::GameObject* gameobject, GLuint& vao, GLuint vbo[4], FE::Shader& shader);

	using SetupFunction = std::function<void(GLuint&, GLuint[4])>;
	using DrawFunction = std::function<void(FE::GameObject*, GLuint&, GLuint[4], FE::Shader&)>;

	class SpriteRenderer {
	public:
		SpriteRenderer(const FE::Shader& shader, const FE::SetupFunction& setup = FE::__default_setup_spriterenderer, const FE::DrawFunction& draw = FE::__default_draw_spriterenderer)
			: _shader(shader) 
		{
			setup(_vao, _vbo); 
			_drawFunction = draw;
		}
		~SpriteRenderer() {}

		const FE::Shader& Shader() { return _shader; }
		void	Draw(FE::GameObject* go) { _drawFunction(go, _vao, _vbo, _shader); }
	private:
		FE::Shader	_shader;
		DrawFunction	_drawFunction;
		GLuint	_vao;
		GLuint	_vbo[4];
	};

}
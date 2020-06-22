#include <glm/gtx/normal.hpp>
#include <glm/gtx/transform.hpp>

#include "RessourceManager.h"
#include "SpriteRenderer.h"

struct __default_vertex {
	glm::vec3	pos;
	glm::vec3	norm;
};

namespace FE {

	void	__default_setup_spriterenderer(GLuint& vao, GLuint vbo[4])
	{
		glm::vec3	p1(-0.5f, 0.5f, 0.0f);
		glm::vec3	p2(0.5f, -0.5f, 0.0f);
		glm::vec3	p3(-0.5f, -0.5f, 0.0f);
		glm::vec3	p4(0.5f, 0.5f, 0.0f);

		__default_vertex	vertices[] = {
			{p1, glm::triangleNormal(p1, p2, p3)},
			{p2, glm::triangleNormal(p1, p2, p3)},
			{p3, glm::triangleNormal(p1, p2, p3)},
			{p1, glm::triangleNormal(p1, p4, p2)},
			{p4, glm::triangleNormal(p1, p4, p2)},
			{p2, glm::triangleNormal(p1, p4, p2)}
		};

		glm::vec2	textcoords[] = {
			glm::vec2{0.0f, 1.0f},
			glm::vec2{1.0f, 0.0f},
			glm::vec2{0.0f, 0.0f},
			glm::vec2{0.0f, 1.0f},
			glm::vec2{1.0f, 1.0f},
			glm::vec2{1.0f, 0.0f}
		};

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		glGenBuffers(1, &vbo[0]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		//POSITION
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(__default_vertex), NULL);
		glEnableVertexAttribArray(0);
		//NORMAL
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(__default_vertex), (void*)sizeof(glm::vec3));
		glEnableVertexAttribArray(1);
		//TEXTCOORD
		glGenBuffers(1, &vbo[3]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(textcoords), textcoords, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat), NULL);
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void	__default_draw_spriterenderer(FE::GameObject* gameobject, GLuint& vao, GLuint vbo[4], FE::Shader& shader)
	{
		FE::Sprite* sprite = gameobject->GetComponent<FE::Sprite>();
		FE::Transform* transform = gameobject->GetComponent<FE::Transform>();
		FE::Texture t = FE::RessourceManager::GetTexture(sprite->TextureName);
		glm::mat4	model(1.0f);

		model = glm::scale(model, transform->scale);
		model = glm::rotate(model, glm::radians(transform->rotation.z), glm::vec3{ 0.0f, 0.0f, 1.0f });
		model = glm::translate(model, transform->position);

		shader.SetMatrix4("model", model);

		if (sprite->Mode == FE::SpriteMode_e::SINGLE) {

		}
		else if (sprite->Mode == FE::SpriteMode_e::MULTIPLE_NORMED) {

		} 
		else {

		}

		glActiveTexture(GL_TEXTURE0);
		t.Bind();

		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		t.UnBind();

		glBindVertexArray(0);

	}

}
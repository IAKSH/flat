#include "core/application.hpp"
#include "core/shader.hpp"
#include "core/keyevent.hpp"
#include "core/winevent.hpp"

#include <iostream>

const char* vshader =
"#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"}\n";

const char* fshader =
"#version 330 core\n"
"out vec4 color;\n"
"void main()\n"
"{\n"
"   color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n";

class MainLayer : public flat::core::Layer
{
private:
	flat::core::Shader mainShader;
	GLuint VBO, VAO;

public:
	MainLayer()
		: Layer("MainLayer")
	{
	}

	~MainLayer() = default;

	virtual void onAttach() override
	{
		mainShader.loadFromGLSL(vshader, fshader);

		// Set up vertex data and buffers
		GLfloat vertices[] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f,  0.5f, 0.0f
		};
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		glBindVertexArray(0);
	}

	virtual void onDetach() override
	{

	}

	virtual void onUpdate() override
	{

	}

	virtual void onRender() override
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(mainShader.getShaderID());
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
	}

	virtual void onEvent(flat::core::Event& e) override
	{
		if (auto ptr = dynamic_cast<flat::core::KeyPress*>(&e); ptr && ptr->getKeyCode() == flat::core::KeyCode::A)
			std::cout << "A pressed\n";
		else if (auto ptr = dynamic_cast<flat::core::KeyPress*>(&e); ptr && ptr->getKeyCode() == flat::core::KeyCode::ESCAPE)
			flat::core::Application::getInstance()->exit();
	}
};

static MainLayer mainlayer;

int main()
{
	flat::core::Application app;
	app.pushLayer(static_cast<flat::core::Layer*>(&mainlayer));
	app.run();
}
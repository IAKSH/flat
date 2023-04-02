#include "core/application.hpp"
#include "core/keyevent.hpp"
#include "core/winevent.hpp"
#include "utils/shader.hpp"
#include "utils/texture.hpp"

#include <iostream>

#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>

const char* vshader =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec2 aTexCoord;\n"
"out vec2 aTexCoordOut;\n"
"void main()\n"
"{\n"
"    gl_Position =  vec4(aPos, 1.0f);\n"
"    aTexCoordOut = vec2(aTexCoord.x, 1.0 - aTexCoord.y);\n"
"}\0";

const char* fshader =
"#version 330 core\n"
"out vec4 FragColor;\n"
"in vec2 aTexCoordOut;\n"
"uniform sampler2D texture0;\n"
"void main()\n"
"{\n"
"    vec4 texColor = texture(texture0,aTexCoordOut);\n"
"    FragColor = texColor * vec4(1.0f,1.0f,1.0f,1.0f);\n"
"}\n\0";

class MainLayer : public flat::core::Layer
{
private:
	flat::utils::Shader mainShader;
	GLuint vbo, vao, ebo;
	flat::utils::Texture testTex;

public:
	MainLayer()
		: Layer("MainLayer")
	{
	}

	~MainLayer() = default;

	virtual void onAttach() override
	{
		mainShader.loadFromGLSL(vshader, fshader);
		glUniform1i(glGetUniformLocation(mainShader.getShaderID(), "texture0"), 0);

		// Set up vertex data and buffers
		float vertices[] = {
				1.0f,  1.0f,  0.0f, 1.0f, 1.0f,  // top right
				1.0f,  -1.0f, 0.0f, 1.0f, 0.0f,  // bottom right
				-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,  // bottom left
				-1.0f, 1.0f,  0.0f, 0.0f, 1.0f   // top left
		};
		unsigned int indices[] = {
			0, 1, 3,  // first Triangle
			1, 2, 3   // second Triangle
		};
		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &ebo);
		glBindVertexArray(vao);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// texture coord attribute
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		// imgui test
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		ImGuiIO& io = ImGui::GetIO();
		ImGui_ImplGlfw_InitForOpenGL(glfwGetCurrentContext(), true);
		ImGui_ImplOpenGL3_Init("#version 330");

		// texture test
		testTex.loadFromFile("images/bird0_0.png");
	}

	virtual void onDetach() override
	{
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &vbo);
	}

	virtual void onUpdate() override
	{

	}

	virtual void onRender() override
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, testTex.getTextureID());

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(mainShader.getShaderID());
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// imgui test
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("ImGui Test");
		ImGui::Text("glfwGetTime(): %lf", glfwGetTime());
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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
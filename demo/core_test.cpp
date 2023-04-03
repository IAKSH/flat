#include "core/application.hpp"
#include "core/keyevent.hpp"
#include "core/winevent.hpp"
#include "utils/shader.hpp"
#include "utils/texture.hpp"
#include "utils/audio.hpp"
#include "utils/time.hpp"

#include <iostream>

#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const char* vshader =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec2 aTexCoord;\n"
"out vec2 aTexCoordOut;\n"
"uniform mat4 transform;\n"
"void main()\n"
"{\n"
"    gl_Position =  transform * vec4(aPos, 1.0f);\n"
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
	flat::utils::TimeRecorder recoreder;
	flat::utils::Timer timer;
	flat::utils::Texture testTex;
	flat::utils::Audio testAudio;
	GLuint vbo, vao, ebo;
	ALuint testAudioSourceID;

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

		// audio test
		testAudio.loadFromFile("sounds/demo_sounds_relaxed-vlog-night-street-131746.mp3");
		alGenSources(1, &testAudioSourceID);
		alSourcei(testAudioSourceID, AL_BUFFER, testAudio.getBufferID());
		alSourcef(testAudioSourceID, AL_GAIN, 0.25f);
		alSourcePlay(testAudioSourceID);

		// timer test
		timer.setInterval(flat::utils::Seconds(1));
		timer.detachRun([]() {std::clog << "Timer thread (id=" << std::this_thread::get_id() << ") running!\n"; });
	}

	virtual void onDetach() override
	{
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &vbo);
		alDeleteSources(1, &testAudioSourceID);
	}

	virtual void onUpdate() override
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(16));

		
	}

	virtual void onRender() override
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, testTex.getTextureID());

		glm::mat4 trans(1.0f);
		trans *= glm::translate(glm::mat4(1.0f), glm::vec3(sin(glfwGetTime()) / 2.0f, cos(glfwGetTime()) / 2.0f, 0.0f));
		trans *= glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 1.0f));
		trans *= glm::rotate(glm::mat4(1.0f), static_cast<float>(sin(glfwGetTime())), glm::vec3(cos(glfwGetTime()), 1.0f, 1.0f));

		unsigned int location = glGetUniformLocation(mainShader.getShaderID(), "transform");
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(trans));

		glBindVertexArray(vao);
		glUseProgram(mainShader.getShaderID());
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// imgui test
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("ImGui Test");
		ImGui::Text("glfwGetTime(): %lf", glfwGetTime());
		ImGui::Text("FPS: %f", 1000000.0f / recoreder.getSpanAsMicroSeconds().count());
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		recoreder.update();
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
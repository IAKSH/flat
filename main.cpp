#include "al.h"
#include "core/application.hpp"
#include "core/event_keyboard.hpp"
#include "core/event_window.hpp"
#include "utils/shader.hpp"
#include "utils/texture.hpp"
#include "utils/audio.hpp"
#include "utils/timer.hpp"
#include "utils/camera.hpp"
#include "utils/vao.hpp"
#include "utils/audio_source.hpp"

#include <array>
#include <memory>
#include <iostream>

#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

const char* vshader =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec4 aColor;\n"
"layout (location = 2) in vec2 aTexCoord;\n"
"out vec2 aTexCoordOut;\n"
"out vec4 aColorOut;\n"
"uniform mat4 transform;\n"
"uniform mat4 camTrans;\n"
"void main()\n"
"{\n"
"    gl_Position =  camTrans * transform * vec4(aPos, 1.0f);\n"
"    aTexCoordOut = vec2(aTexCoord.x, 1.0 - aTexCoord.y);\n"
"    aColorOut = aColor;\n"
"}\0";

const char* fshader =
"#version 330 core\n"
"out vec4 FragColor;\n"
"in vec2 aTexCoordOut;\n"
"in vec4 aColorOut;\n"
"uniform sampler2D texture0;\n"
"void main()\n"
"{\n"
"    vec4 texColor = texture(texture0,aTexCoordOut);\n"
"    FragColor = texColor * aColorOut;\n"
"}\n\0";

class MainLayer : public ni::core::Layer
{
private:
	ni::utils::Shader mainShader;
	ni::utils::TimeRecorder recoreder;
	ni::utils::Timer timer;
	ni::utils::Texture testTex;
	ni::utils::Audio testAudio;
	ni::utils::Camera2D cam;
	ni::utils::VertexArrayObj vao;
	ni::utils::AudioSource testAudioSource;

	float camDownVec{ 0.0f };
	float camLeftVec{ 0.0f };
	float camSensitivity{ 2.5f };

public:
	MainLayer()
		: Layer("MainLayer")
	{
	}

	~MainLayer() = default;

	virtual void onAttach() override
	{
		cam.setPositionX(-0.5f);
		//cam.setPositionZ(0.5f);

		mainShader.loadFromGLSL(vshader, fshader);
		glUniform1i(glGetUniformLocation(mainShader.getShaderID(), "texture0"), 0);

		// Set up vertex data and buffers
		std::array<float,36> vertices {
				1.0f,  1.0f,  0.0f, 1.0f, 1.0f, 1.0f, 0.1f, 1.0f, 1.0f,  // top right
				1.0f,  -1.0f, 0.0f,1.0f, 1.0f, 1.0f, 0.1f, 1.0f, 0.0f,  // bottom right
				-1.0f, -1.0f, 0.0f,1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,  // bottom left
				-1.0f, 1.0f,  0.0f,1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f   // top left
		};
		std::array<unsigned int, 6> indices {
			0, 1, 3,  // first Triangle
			1, 2, 3   // second Triangle
		};

		vao.create(ni::utils::GLBufferType::Static,vertices,indices);

		// imgui test
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		ImGuiIO& io = ImGui::GetIO();
		ImGui_ImplGlfw_InitForOpenGL(glfwGetCurrentContext(), true);
		ImGui_ImplOpenGL3_Init("#version 330");

		// texture test
		testTex.loadFromFile("images/floor.png");

		// audio test
		testAudio.loadFromFile("sounds/demo_sounds_relaxed-vlog-night-street-131746.mp3");
		alSourcei(testAudioSource.getSourceID(), AL_BUFFER, testAudio.getBufferID());
		alSourcef(testAudioSource.getSourceID(), AL_GAIN, 0.1f);
		alSourcei(testAudioSource.getSourceID(), AL_LOOPING, AL_TRUE);
		alSourcePlay(testAudioSource.getSourceID());

		// timer test
		timer.setInterval(ni::utils::Seconds(1));
		timer.detachRun([]() {std::clog << "Timer thread (id=" << std::this_thread::get_id() << ") running!\n"; });
	}

	virtual void onDetach() override
	{

	}

	virtual void onUpdate() override
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(3));

		//cam.move(cam.getVelocityX(), cam.getVelocityY());
		//cam.turn(camDownVec * camSensitivity, camLeftVec * camSensitivity);
		//cam.update();
		cam.setPositionX(cam.getPositionX() + cam.getVelocityX() * 2);
		cam.setPositionY(cam.getPositionY() + cam.getVelocityY() * 2);
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
		trans *= glm::scale(glm::mat4(1.0f), glm::vec3(200.0f, 100.0f, 1.0f));
		//trans *= glm::rotate(glm::mat4(1.0f), static_cast<float>(sin(glfwGetTime())), glm::vec3(cos(glfwGetTime()), 1.0f, 1.0f));

		unsigned int transLocation = glGetUniformLocation(mainShader.getShaderID(), "transform");
		glUniformMatrix4fv(transLocation, 1, GL_FALSE, glm::value_ptr(trans));

		unsigned int camTrans = glGetUniformLocation(mainShader.getShaderID(), "camTrans");
		glUniformMatrix4fv(camTrans, 1, GL_FALSE, glm::value_ptr(cam.getTranslateMatrix()));

		glBindVertexArray(vao.getVAO());
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
		ImGui::Text("cam.x: %f", cam.getPositionX());
		ImGui::Text("cam.y: %f", cam.getPositionY());
		ImGui::Text("cam.z: %f", cam.getPositionZ());
		//ImGui::Text("cam.pitch: %f", cam.getPitch());
		//ImGui::Text("cam.yaw: %f", cam.getYaw());
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		recoreder.update();
	}

	virtual void onEvent(ni::core::Event& e) override
	{
		if (auto ptr = dynamic_cast<ni::core::KeyPressEvent*>(&e); ptr && ptr->getKeyCode() == ni::core::KeyCode::W)
			cam.setVelocityY(0.1f);
		else if (auto ptr = dynamic_cast<ni::core::KeyPressEvent*>(&e); ptr && ptr->getKeyCode() == ni::core::KeyCode::S)
			cam.setVelocityY(-0.1f);
		else if (auto ptr = dynamic_cast<ni::core::KeyPressEvent*>(&e); ptr && ptr->getKeyCode() == ni::core::KeyCode::D)
			cam.setVelocityX(0.1f);
		else if (auto ptr = dynamic_cast<ni::core::KeyPressEvent*>(&e); ptr && ptr->getKeyCode() == ni::core::KeyCode::A)
			cam.setVelocityX(-0.1f);
		else if (auto ptr = dynamic_cast<ni::core::KeyPressEvent*>(&e); ptr && ptr->getKeyCode() == ni::core::KeyCode::Q)
			camDownVec = 1.0f;
		else if (auto ptr = dynamic_cast<ni::core::KeyPressEvent*>(&e); ptr && ptr->getKeyCode() == ni::core::KeyCode::E)
			camDownVec = -1.0f;
		else if (auto ptr = dynamic_cast<ni::core::KeyPressEvent*>(&e); ptr && ptr->getKeyCode() == ni::core::KeyCode::LEFT_SHIFT)
			camLeftVec = 1.0f;
		else if (auto ptr = dynamic_cast<ni::core::KeyPressEvent*>(&e); ptr && ptr->getKeyCode() == ni::core::KeyCode::LEFT_CONTROL)
			camLeftVec = -1.0f;
		else if (auto ptr = dynamic_cast<ni::core::KeyReleaseEvent*>(&e); ptr && ptr->getKeyCode() == ni::core::KeyCode::W)
			cam.setVelocityY(0.0f);
		else if (auto ptr = dynamic_cast<ni::core::KeyReleaseEvent*>(&e); ptr && ptr->getKeyCode() == ni::core::KeyCode::S)
			cam.setVelocityY(0.0f);
		else if (auto ptr = dynamic_cast<ni::core::KeyReleaseEvent*>(&e); ptr && ptr->getKeyCode() == ni::core::KeyCode::D)
			cam.setVelocityX(0.0f);
		else if (auto ptr = dynamic_cast<ni::core::KeyReleaseEvent*>(&e); ptr && ptr->getKeyCode() == ni::core::KeyCode::A)
			cam.setVelocityX(0.0f);
		else if (auto ptr = dynamic_cast<ni::core::KeyReleaseEvent*>(&e); ptr && ptr->getKeyCode() == ni::core::KeyCode::Q)
			camDownVec = 0.0f;
		else if (auto ptr = dynamic_cast<ni::core::KeyReleaseEvent*>(&e); ptr && ptr->getKeyCode() == ni::core::KeyCode::E)
			camDownVec = 0.0f;
		else if (auto ptr = dynamic_cast<ni::core::KeyReleaseEvent*>(&e); ptr && ptr->getKeyCode() == ni::core::KeyCode::LEFT_SHIFT)
			camLeftVec = 0.0f;
		else if (auto ptr = dynamic_cast<ni::core::KeyReleaseEvent*>(&e); ptr && ptr->getKeyCode() == ni::core::KeyCode::LEFT_CONTROL)
			camLeftVec = 0.0f;
		else if (auto ptr = dynamic_cast<ni::core::KeyPressEvent*>(&e); ptr && ptr->getKeyCode() == ni::core::KeyCode::ESCAPE)
			ni::core::Application::getInstance()->exit();
	}
};

int main()
{
	ni::core::Application app;
	app.pushLayer(std::make_unique<MainLayer>());
	app.run();
}
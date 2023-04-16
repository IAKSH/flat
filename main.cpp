#include "AL/al.h"
#include "core/application.hpp"
#include "core/event_keyboard.hpp"
#include "core/event_window.hpp"
#include "utils/shader.hpp"
#include "utils/texture.hpp"
#include "utils/audio.hpp"
#include "utils/timer.hpp"
#include "utils/camera.hpp"
#include "utils/rectangle_vao.hpp"
#include "utils/audio_source.hpp"
#include "utils/logger.hpp"
#include "utils/animation.hpp"
#include "utils/font.hpp"
#include "flat/collision_detect.hpp"
#include "flat/text_renderer.hpp"
#include "demo_obj.hpp"
#include "text.hpp"

#include <array>
#include <memory>
#include <iostream>
#include <string_view>

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
	ni::utils::Shader fontShader;
	ni::utils::TimeRecorder recorder;
	ni::utils::Timer timer;
	ni::utils::Texture testTex;
	ni::utils::Texture backgroundTex;
	ni::utils::Audio testAudio;
	ni::utils::AudioSource testSource;
	ni::utils::Camera2D cam;
	ni::utils::VertexBuffer<ni::utils::GLBufferType::Static> vertexBuffer;
	ni::utils::VertexBuffer<ni::utils::GLBufferType::Static> backGroundVertexBuffer;
	ni::utils::Font unifont;
	ni::flat::TextRenderer textRenderer;
	demo::Bird bird {mainShader,cam,testAudio};
	demo::Text text{textRenderer,ni::utils::MilliSeconds(50),U"家人们，谁懂啊，下头C++真的下头。"};

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
		cam.setPosX(-0.5f);

		mainShader.loadFromGLSL(vshader, fshader);
		glUniform1i(glGetUniformLocation(mainShader.getShaderID(), "texture0"), 0);
		fontShader.loadFromFile("../../font_vshader.glsl","../../font_fshader.glsl");
		glUniform1i(glGetUniformLocation(fontShader.getShaderID(), "texture0"), 0);
		
		// Set up vertex data and buffers
		std::array<float,36> vertices {
				1.0f,  1.0f,  0.0f, 1.0f, 1.0f, 1.0f, 0.1f, 1.0f, 1.0f,  // top right
				1.0f,  -1.0f, 0.0f,1.0f, 1.0f, 1.0f, 0.1f, 1.0f, 0.0f,  // bottom right
				-1.0f, -1.0f, 0.0f,1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,  // bottom left
				-1.0f, 1.0f,  0.0f,1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f   // top left
		};
		std::array<float,36> nonTransparentVertices {
				1.0f,  1.0f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  // top right
				1.0f,  -1.0f, 0.0f,1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,  // bottom right
				-1.0f, -1.0f, 0.0f,1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,  // bottom left
				-1.0f, 1.0f,  0.0f,1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f   // top left
		};
		std::array<unsigned int, 6> indices {
			0, 1, 3,  // first Triangle
			1, 2, 3   // second Triangle
		};

		//vertexBuffer.create(vertices,indices);
		//backGroundVertexBuffer.create(nonTransparentVertices,indices);

		// imgui test
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		ImGuiIO& io = ImGui::GetIO();
		ImGui_ImplGlfw_InitForOpenGL(glfwGetCurrentContext(), true);
		ImGui_ImplOpenGL3_Init("#version 330");

		// texture test
		testTex.loadFromFile("images/floor.png");
		backgroundTex.loadFromFile("images/strangeSky.png");

		// audio test
		testAudio.loadFromFile("sounds/demo_sounds_relaxed-vlog-night-street-131746_01.wav");
		alSourcei(testSource.getSourceID(),AL_BUFFER,testAudio.getBufferID());
		alSourcef(testSource.getSourceID(),AL_GAIN,0.25f);
		alSourcePlay(testSource.getSourceID());

		// timer test
		timer.setInterval(ni::utils::MilliSeconds(3));
		timer.detachRun([&]() 
		{
			//if(ni::flat::collisionCheckGJK(bird.getPositionX(),bird.getPositionY(),50.0f,50.0f,0.0f,0.0f,0.0f,100.0f,100.0f,glfwGetTime()))
			//	ni::utils::otherLogger()->warn("collision: bird at ({},{}) hit obj at ({},{})",bird.getPositionX(),bird.getPositionY(),0.0f,0.0f);
		});

		// font test
		unifont.loadTTF("fonts/unifont-15.0.01.ttf");

		bird.onAttach();
	}

	virtual void onDetach() override
	{
		bird.onDetach();
	}

	virtual void onUpdate() override
	{
		//std::this_thread::sleep_for(std::chrono::milliseconds(3));

		//cam.move(cam.getVelocityX(), cam.getVelocityY());
		//cam.turn(camDownVec * camSensitivity, camLeftVec * camSensitivity);
		//cam.update();
		cam.setPosX(cam.getPosX() + cam.getVelX() * 2);
		cam.setPosY(cam.getPosY() + cam.getVelY() * 2);

		bird.onUpdate();

		alListener3f(AL_POSITION,cam.getPosX(),cam.getPosY(),1.0f);
		alListener3f(AL_VELOCITY,cam.getVelX(),cam.getVelY(),cam.getVelZ());
	}

	virtual void onRender() override
	{
		glEnable(GL_DEPTH_TEST);
		//glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glActiveTexture(GL_TEXTURE0);

		// draw background
		{
			glUseProgram(mainShader.getShaderID());
			glBindTexture(GL_TEXTURE_2D, backgroundTex.getTextureID());

			glm::mat4 trans(1.0f);
			trans *= glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
			trans *= glm::scale(glm::mat4(1.0f), glm::vec3(800.0f, 600.0f, 1.0f));
			trans *= glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));

			unsigned int transLocation = glGetUniformLocation(mainShader.getShaderID(), "transform");
			glUniformMatrix4fv(transLocation, 1, GL_FALSE, glm::value_ptr(trans));
			unsigned int camTrans = glGetUniformLocation(mainShader.getShaderID(), "camTrans");
			glUniformMatrix4fv(camTrans, 1, GL_FALSE, glm::value_ptr(cam.getTranslateMatrix()));

			glBindVertexArray(backGroundVertexBuffer.getVAO());
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
		// draw floor
		{
			glUseProgram(mainShader.getShaderID());
			glBindTexture(GL_TEXTURE_2D, testTex.getTextureID());

			glm::mat4 trans(1.0f);
			trans *= glm::translate(glm::mat4(1.0f), glm::vec3(sin(glfwGetTime()) / 2.0f, cos(glfwGetTime()) / 2.0f, 0.1f));
			trans *= glm::scale(glm::mat4(1.0f), glm::vec3(100.0f, 100.0f, 1.0f));
			trans *= glm::rotate(glm::mat4(1.0f), static_cast<float>(sin(glfwGetTime())), glm::vec3(0.0f, 0.0f, 1.0f));

			unsigned int transLocation = glGetUniformLocation(mainShader.getShaderID(), "transform");
			glUniformMatrix4fv(transLocation, 1, GL_FALSE, glm::value_ptr(trans));
			unsigned int camTrans = glGetUniformLocation(mainShader.getShaderID(), "camTrans");
			glUniformMatrix4fv(camTrans, 1, GL_FALSE, glm::value_ptr(cam.getTranslateMatrix()));

			glBindVertexArray(vertexBuffer.getVAO());
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
		bird.onRender();
		// test: draw text
		{
			textRenderer.drawText(std::u32string_view(U"我测你们de码?！"),ni::flat::Point(400.0f,300.0f,0.9f),
				ni::flat::Color(1.0f,0.0f,0.0f,0.8f),ni::flat::Scale(abs(cos(glfwGetTime() * 0.1))),&unifont);

			textRenderer.drawText(std::u32string_view(U"WoDiaoNiMa"),ni::flat::Point(0.0f,300.0f,0.9f),
				ni::flat::Color(abs(cos(glfwGetTime() * 0.1)),0.0f,abs(sin(glfwGetTime() * 0.1)),0.8f),ni::flat::Scale(abs(sin(glfwGetTime() * 2.0f))));

			//textRenderer.drawText(std::u32string_view(U"傻逼鸟"),ni::flat::Point(bird.getPositionX() - 40.0f,bird.getPositionY() + 25.0f,0.9f),
			//	ni::flat::Color(1.0f,1.0f,abs(sin(glfwGetTime() * 0.1)),1.0f),ni::flat::Scale(0.5f),&cam);

			textRenderer.drawText(&cam);
			textRenderer.drawText(std::u32string_view(U"傻逼鸟"),ni::flat::Point(bird.getPosX() - 40.0f,bird.getPosY() + 25.0f,0.9f),
				ni::flat::Color(1.0f,1.0f,abs(sin(glfwGetTime() * 0.1)),1.0f),ni::flat::Scale(0.5f));
			
			text.tryToWrite();
		}

		// imgui test
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("ImGui Test");
		ImGui::Text("glfwGetTime(): %lf", glfwGetTime());
		ImGui::Text("FPS: %f", 1000000.0f / recorder.getSpanAsMicroSeconds().count());
		ImGui::Text("cam.x: %f", cam.getPosX());
		ImGui::Text("cam.y: %f", cam.getPosY());
		ImGui::Text("cam.z: %f", cam.getPosZ());
		//ImGui::Text("cam.pitch: %f", cam.getPitch());
		//ImGui::Text("cam.yaw: %f", cam.getYaw());
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		recorder.update();
	}

	virtual void onEvent(ni::core::Event& e) override
	{
		if(e.getType() == ni::core::EventType::KeyPress)
		{
			switch (static_cast<ni::core::KeyPressEvent&>(e).getKeyCode())
			{
				case ni::core::KeyCode::W:
					cam.setVelY(0.1f);
					break;
				case ni::core::KeyCode::S:
					cam.setVelY(-0.1f);
					break;
				case ni::core::KeyCode::D:
					cam.setVelX(0.1f);
					break;
				case ni::core::KeyCode::A:
					cam.setVelX(-0.1f);
					break;
				/*
				case ni::core::KeyCode::Q:
					camDownVec = 1.0f;
					break;
				case ni::core::KeyCode::E:
					camDownVec = -1.0f;
					break;
				case ni::core::KeyCode::LEFT_SHIFT:
					camLeftVec = 1.0f;
					break;
				case ni::core::KeyCode::LEFT_CONTROL:
					camLeftVec = -1.0f;
					break;
				*/
				case ni::core::KeyCode::ESCAPE:
					ni::core::Application::getInstance()->exit();
					break;
				default:
					break;
			}
		}
		else if (e.getType() == ni::core::EventType::KeyRelease)
		{
			switch (static_cast<ni::core::KeyReleaseEvent&>(e).getKeyCode())
			{
				case ni::core::KeyCode::W:
				case ni::core::KeyCode::S:
					cam.setVelY(0.0f);
					break;
				case ni::core::KeyCode::D:
				case ni::core::KeyCode::A:
					cam.setVelX(0.0f);
					break;
				case ni::core::KeyCode::Q:
				case ni::core::KeyCode::E:
					camDownVec = 0.0f;
					break;
				case ni::core::KeyCode::LEFT_SHIFT:
				case ni::core::KeyCode::LEFT_CONTROL:
					camLeftVec = 0.0f;
					break;
				default:
					break;
			}
		}

		bird.onEvent(e);
	}
};

int main()
{
	ni::core::Application app;
	app.pushLayer(std::make_unique<MainLayer>());
	app.run();
}
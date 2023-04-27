
#include "menu.hpp"
#include "../core/loggers.hpp"
#include "../utils/format.hpp"
#include "../utils/image.hpp"
#include "AL/al.h"
#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <string>
#include <sstream>
#include <string_view>

Flat::MenuLayer::MenuLayer()
    : Layer("menu"),shader(vshader,fshader),cam(800.0f,600.0f)
{
}

void Flat::MenuLayer::onAttach()
{
    // config camera
    cam.setPositionZ(600.0f);
    cam.setFov(60.0f);

    // load shader
    shader.activeTexture("texture0",0);

    // load textures
    ni::utils::Image wire("images/wire.png");
    ni::utils::Image bird("images/bird0_0.png");
    background = std::make_unique<Texture>(wire.getData(),0,0,wire.getWidth(),wire.getHeight());
    selectIcon = std::make_unique<Texture>(bird.getData(),0,0,bird.getWidth(),bird.getHeight());

    // load font
    unifont48.loadFromFile("fonts/unifont-15.0.01.ttf");
    unifont48.resize(48);
    unifont16.loadFromFile("fonts/unifont-15.0.01.ttf");
    unifont16.resize(16);

    // load bgm
    Sample bgmSample("sounds/single.wav");
    bgm = std::make_unique<Buffer<PCMFormat::MONO16>>(bgmSample.getPCM(),bgmSample.getSampleRate(),bgmSample.getPCMLen());
    alSourcei(bgmSource.getSourceID(),AL_BUFFER,bgm->getBufferID());
    alSourcePlay(bgmSource.getSourceID());

    // OpenGL
    glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glActiveTexture(GL_TEXTURE0);

    // imgui init
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplGlfw_InitForOpenGL(glfwGetCurrentContext(), true);
	ImGui_ImplOpenGL3_Init("#version 330");

    // move game title
    gameTitle.setPositionY(550.0f);
    gameTitle.setPositionZ(0.1f);
    info0.setPositionY(525.0f);
    info0.setPositionZ(0.1f);
    info1.setPositionY(500.0f);
    info1.setPositionZ(0.1f);
    fpsInfo.set(Point(0.0f,475.0f,0.1f));
    fpsInfo.set(Color(1.0f,0.3f,0.1f,1.0f));

    // move quit button
    startButton.active();
    startButton.setPositionX(175.0f);
    startButton.setPositionY(50.0f);
    startButton.setPositionZ(0.2f);

    // reset v-sync
    //glfwSwapInterval(3);

    // button
    startButton.onAttach();
}

void Flat::MenuLayer::onDetach()
{

}

void Flat::MenuLayer::onUpdate()
{
    std::u32string buffer = ni::utils::to_u32string(1000.0f / fpsRecoder.getSpanAsMilliSeconds().count());
    fpsInfo.set(buffer);

    vao.setColor(0,std::array<float,4>{sin(recoder.getSpanAsMilliSeconds().count()  / 5000.0f),0.0f,0.0f,0.25f});
    vao.setColor(1,std::array<float,4>{sin(recoder.getSpanAsMilliSeconds().count()  / 2000.0f),0.0f,0.0f,0.8f});
    vao.setColor(2,std::array<float,4>{sin(recoder.getSpanAsMilliSeconds().count()  / 4000.5f),0.0f,0.0f,0.75f});
    vao.setColor(3,std::array<float,4>{sin(recoder.getSpanAsMilliSeconds().count()  / 10000.0f),0.0f,0.0f,0.4f});

    // button
    startButton.onUpdate();

    // update fps recoder
    fpsRecoder.update();

    // camera update
    cam.rotate(camRotateSpeedUp * 4,camRotateSpeedRight * 4,camRollSpeed * 2.0f);
    cam.move(camMoveSpeedUp * 8,camMoveSpeedRight * 8,0.0f);
}

void Flat::MenuLayer::onRender()
{
    glClearColor(0.1f, 0.1f, 0.1f, 0.5f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.use();

    glm::mat4 trans(1.0f);
	trans *= glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	trans *= glm::scale(glm::mat4(1.0f), glm::vec3(400.0f, 300.0f, 1.0f));
	trans *= glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
    shader.setUniform("transform",trans);
    shader.setUniform("camTrans",cam.getMatrix());

    glBindTexture(GL_TEXTURE_2D,background->getTextureID());
    glBindVertexArray(vao.getVAO());
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // imgui test
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGui::Begin("ImGui Test");
	ImGui::Text("glfwGetTime(): %lf", glfwGetTime());
	//ImGui::Text("FPS: %f", 1000000.0f / recorder.getSpanAsMicroSeconds().count());
	ImGui::Text("cam.x: %f", cam.getPositionX());
	ImGui::Text("cam.y: %f", cam.getPositionY());
	ImGui::Text("cam.z: %f", cam.getPositionZ());
    ImGui::Text("cam.yaw: %f", cam.getYaw());
	ImGui::Text("cam.pitch: %f", cam.getPitch());
    ImGui::Text("cam.roll: %f", cam.getRoll());
	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


    gameTitle.onRender();
    info0.onRender();
    info1.onRender();
    startButton.onRender();
    fpsInfo.onRender();
    //texRen.drawText(ni::utils::to_u32string(1000.0f / fpsRecoder.getSpanAsMilliSeconds().count()),Point(0.0f,400.0f,0.9f),
	//			Color(1.0f,1.0f,1.0f,1.0f),ni::utils::Scale(1.0f),&unifont16);
}

void Flat::MenuLayer::onEvent(Event& e)
{
    if(e.getType() == ni::core::EventType::KeyPress)
    {
    	switch (static_cast<ni::core::KeyPressEvent&>(e).getKeyCode())
    	{
    		case ni::core::KeyCode::ESCAPE:
    			ni::core::Application::getInstance().exit();
    			break;

            case ni::core::KeyCode::UP:
                camRotateSpeedUp = 0.1f;
                break;

            case ni::core::KeyCode::DOWN:
                camRotateSpeedUp = -0.1f;
                break;

            case ni::core::KeyCode::LEFT:
                camRotateSpeedRight = -0.1f;
                break;

            case ni::core::KeyCode::RIGHT:
                camRotateSpeedRight = 0.1f;
                break;

            case ni::core::KeyCode::Q:
                camRollSpeed = 0.1f;
                break;

            case ni::core::KeyCode::E:
                camRollSpeed = -0.1f;
                break;

            case ni::core::KeyCode::W:
                camMoveSpeedUp = 0.1f;
                break;

            case ni::core::KeyCode::S:
                camMoveSpeedUp = -0.1f;
                break;

            case ni::core::KeyCode::A:
                camMoveSpeedRight = -0.1f;
                break;

            case ni::core::KeyCode::D:
                camMoveSpeedRight = 0.1f;
                break;

            default:
                break;
        }
    }
    else if(e.getType() == ni::core::EventType::KeyRelease)
    {
        switch (static_cast<ni::core::KeyPressEvent&>(e).getKeyCode())
        {
            case ni::core::KeyCode::UP:
            case ni::core::KeyCode::DOWN:
                camRotateSpeedUp = 0.0f;
                break;

            case ni::core::KeyCode::LEFT:
            case ni::core::KeyCode::RIGHT:
                camRotateSpeedRight = 0.0f;
                break;

            case ni::core::KeyCode::Q:
            case ni::core::KeyCode::E:
                camRollSpeed = 0.0f;
                break;

            case ni::core::KeyCode::W:
            case ni::core::KeyCode::S:
                camMoveSpeedUp = 0.0f;
                break;

            case ni::core::KeyCode::A:
            case ni::core::KeyCode::D:
                camMoveSpeedRight = 0.0f;
                break;

            default:
                break;
        }
    }

    startButton.onEvent(e);
}

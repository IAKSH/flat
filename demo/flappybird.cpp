#include <memory>
#include <thread>
#include <iostream>
#include <utility>

#include "audio_alsoft.hpp"
#include "keyboard_glfw.hpp"
#include "mouse_glfw.hpp"
#include "renderer_glcore.hpp"
#include "window_glfw.hpp"
#include "gameplay.hpp"

static flat::Window<flat::imp::window::glfw::Window>&& win = flat::imp::window::glfw::Window();
static flat::Renderer<flat::imp::renderer::glcore::Renderer>&& ren = flat::imp::renderer::glcore::Renderer();
static flat::KeyboardSource<flat::imp::keyboard::glfw::KeyboardSource>&& keyboard = flat::imp::keyboard::glfw::KeyboardSource();
static flat::MouseSource<flat::imp::mouse::glfw::MouseSource>&& mouse = flat::imp::mouse::glfw::MouseSource();
static flat::AudioMixer<flat::imp::audio::alsoft::AudioMixer>&& mixer = flat::imp::audio::alsoft::AudioMixer();

static std::unique_ptr<flat::Texture> birdTex0 = ren.genTexture("images/bird0_0.png");
static std::unique_ptr<flat::Texture> birdTex1 = ren.genTexture("images/bird0_1.png");
static std::unique_ptr<flat::Texture> birdTex2 = ren.genTexture("images/bird0_2.png");
static std::unique_ptr<flat::Texture> pipeTexDown = ren.genTexture("images/pipe_down.png");
static std::unique_ptr<flat::Texture> pipeTexUp = ren.genTexture("images/pipe_up.png");

static std::unique_ptr<flat::Font> unifont = ren.genFont("fonts/unifont-15.0.01.ttf");

static flat::Animation birdAnimation(250, { birdTex0.get(), birdTex1.get(), birdTex2.get() });
static flat::Animation pipeAnimation(1000, { pipeTexUp.get() });

class Bird : public flat::GameObject<Bird>
{
private:
	float velocityY;

public:
	Bird()
		: velocityY(0.0f)
	{
		bindAnimation("fly", birdAnimation);
		switchAnimationTo("fly");

		setPosX(-0.8f);
		setWidth(0.09f);
		setHeight(0.1f);
	}

	~Bird() = default;
	void imp_onTick()
	{
		if (keyboard.checkKey(GLFW_KEY_SPACE))
			velocityY = 0.05f;

		setPosY(getPosY() + velocityY);
		if (velocityY > -0.075f)
			velocityY -= 0.005f;

		ren << flat::Color(1.0f, 1.0f, 1.0f, 1.0f) << flat::TextureOffset(0.0f, 0.0f, 1.0f, 1.0f) << getCurrentTexture() << flat::Rectangle(getPosX(), getPosY(), 0.0f, getWidth(), getHeight(), getRotate());
	}
};

class Pipe : public flat::GameObject<Pipe>
{
public:
	Pipe()
	{
		bindAnimation("up", pipeAnimation);
		switchAnimationTo("up");
		setHeight(0.5f);
		setWidth(0.1f);
	}

	~Pipe() = default;

	void imp_onTick()
	{
		if (keyboard.checkKey(GLFW_KEY_A))
			setPosX(getPosX() - 0.01f);
		if (keyboard.checkKey(GLFW_KEY_D))
			setPosX(getPosX() + 0.01f);

		ren << flat::Color(1.0f, 1.0f, 1.0f, 1.0f) << flat::TextureOffset(0.0f, 0.0f, 1.0f, 1.0f) << getCurrentTexture() << flat::Rectangle(getPosX(), getPosY(), 0.0f, getWidth(), getHeight(), getRotate());
	}
};

int main()
{
	auto source = mixer.genAudioSource();
	auto mp3 = mixer.genAudio("sounds/demo_sounds_relaxed-vlog-night-street-131746.mp3");

	(*source)[flat::AudioAttribType::looping](true);
	(*source)[flat::AudioAttribType::gain](0.2f);
	mixer << flat::AudioAttrib(flat::AudioAttribType::gain, 0.75f) << (*source)(*mp3);

	flat::GameObject<Bird>&& bird = Bird();
	flat::GameObject<Pipe>&& pipe = Pipe();

	while (true)
	{
		if (keyboard.checkKey(GLFW_KEY_ESCAPE))
			break;
		if (mouse.checkMouseLeft())
			mixer << flat::StopFlag(*source);
		if (mouse.checkMouseRight())
			mixer << flat::ResumeFlag(*source);

		bird.onTick();
		pipe.onTick();

		// DEBUG: hit check
		if (bird.collisionCheck(pipe))
		{
			std::cout << "Hit!\n";
		}
		// end

		// DEBUG: draw text
		ren << flat::Color(sin(glfwGetTime()), 1.0f, 1.0f, 1.0f) << flat::TextureOffset(0.0f, 0.0f, 1.0f, 1.0f) << (*unifont)('H') << flat::Rectangle(0.0f, 0.0f, 0.0f, 0.05f, 0.05f, 0.0f);
		ren << flat::Color(sin(glfwGetTime()), 1.0f, 1.0f, 1.0f) << flat::TextureOffset(0.0f, 0.0f, 1.0f, 1.0f) << (*unifont)('E') << flat::Rectangle(0.15f, 0.0f, 0.0f, 0.05f, 0.05f, 0.0f);
		ren << flat::Color(sin(glfwGetTime()), 1.0f, 1.0f, 1.0f) << flat::TextureOffset(0.0f, 0.0f, 1.0f, 1.0f) << (*unifont)('L') << flat::Rectangle(0.3f, 0.0f, 0.0f, 0.05f, 0.05f, 0.0f);
		ren << flat::Color(sin(glfwGetTime()), 1.0f, 1.0f, 1.0f) << flat::TextureOffset(0.0f, 0.0f, 1.0f, 1.0f) << (*unifont)('L') << flat::Rectangle(0.45f, 0.0f, 0.0f, 0.05f, 0.05f, 0.0f);
		ren << flat::Color(sin(glfwGetTime()), 1.0f, 1.0f, 1.0f) << flat::TextureOffset(0.0f, 0.0f, 1.0f, 1.0f) << (*unifont)('O') << flat::Rectangle(0.6f, 0.0f, 0.0f, 0.05f, 0.05f, 0.0f);
		// end

		std::this_thread::sleep_until(std::chrono::steady_clock::now() + std::chrono::milliseconds(12));

		win.updateWindow();
	}

	return 0;
}
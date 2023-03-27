#include <memory>
#include <thread>
#include <iostream>
#include <random>

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
static std::unique_ptr<flat::Texture> strangeSkyTex = ren.genTexture("images/strangeSky.png");
static std::unique_ptr<flat::Texture> emptyManStandTex0 = ren.genTexture("images/empty_man_stand_0.png");
static std::unique_ptr<flat::Texture> emptyManStandTex1 = ren.genTexture("images/empty_man_stand_1.png");

static std::unique_ptr<flat::Font> unifont = ren.genFont("fonts/unifont-15.0.01.ttf");

static flat::Animation birdAnimation(250, { birdTex0.get(), birdTex1.get(), birdTex2.get() });
static flat::Animation pipeAnimation(1000, { pipeTexUp.get() });
static flat::Animation strangeSkyAnimation(1000, { strangeSkyTex.get() });
static flat::Animation emptyManStandAnimation(250, { emptyManStandTex0.get(),emptyManStandTex1.get() });

class Man : public flat::GameObject<Man>
{
public:
	Man()
	{

		bindAnimation("stand", emptyManStandAnimation);
		switchAnimationTo("stand");

		setPosX(100.0f);
		setPosY(100.0f);
		setWidth(20.0f);
		setHeight(20.0f);
	}

	~Man() = default;
	void imp_onTick()
	{
		if (keyboard.checkKey(GLFW_KEY_D))
			setPosX(getPosX() + 1.01f);
		if (keyboard.checkKey(GLFW_KEY_A))
			setPosX(getPosX() - 1.0f);
		if (keyboard.checkKey(GLFW_KEY_W))
			setPosY(getPosY() + 1.0f);
		if (keyboard.checkKey(GLFW_KEY_S))
			setPosY(getPosY() - 1.0f);

		ren << flat::Color(1.0f, 1.0f, 1.0f, 0.8f) << flat::TextureOffset(0.0f, 0.0f, 1.0f, 1.0f) << getCurrentTexture() << flat::Rectangle(getPosX(), getPosY(), 0.0f, getWidth(), getHeight(), getRotate());
	}
};

class Man2 : public flat::GameObject<Man2>
{
private:
	std::chrono::steady_clock::time_point lastMove;
	int maxMoveIntervalMS;
	std::random_device rd;
	std::mt19937 gen;
	std::uniform_int_distribution<> intervalDis;
	std::uniform_int_distribution<> moveDis;

public:
	Man2()
		: lastMove(std::chrono::steady_clock::now()), maxMoveIntervalMS(10), gen(rd()), intervalDis(maxMoveIntervalMS / 2, maxMoveIntervalMS), moveDis(-1, 1)
	{
		bindAnimation("stand", emptyManStandAnimation);
		switchAnimationTo("stand");

		setPosX(200.0f + abs(moveDis(gen)) * 250.0f);
		setPosY(200.0f + abs(moveDis(gen)) * 250.0f);

		setWidth(20.0f);
		setHeight(20.0f);
	}

	~Man2() = default;
	void imp_onTick()
	{
		if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - lastMove).count() >= maxMoveIntervalMS)
		{
			setPosX(getPosX() + (moveDis(gen)));
			setPosY(getPosY() + (moveDis(gen)));
			lastMove = std::chrono::steady_clock::now();
		}

		ren << flat::Color(sin(moveDis(gen) * 10), cos(moveDis(gen) * 10), sin(moveDis(gen) * 10), 0.75f) << flat::TextureOffset(0.0f, 0.0f, 1.0f, 1.0f) << getCurrentTexture() << flat::Rectangle(getPosX(), getPosY(), 0.0f, getWidth(), getHeight(), getRotate());
	}
};

class Background : public flat::GameObject<Background>
{
private:
	std::chrono::steady_clock::time_point lastMove;
	int maxMoveIntervalMS;
	std::random_device rd;
	std::mt19937 gen;
	std::uniform_int_distribution<> intervalDis;
	std::uniform_int_distribution<> moveDis;

public:
	Background()
		: lastMove(std::chrono::steady_clock::now()), maxMoveIntervalMS(6000), gen(rd()), intervalDis(maxMoveIntervalMS / 2, maxMoveIntervalMS), moveDis(0,1)
	{
		bindAnimation("strangeSky", strangeSkyAnimation);
		switchAnimationTo("strangeSky");
		setHeight(600.0f);
		setWidth(800.0f);
	}

	~Background() = default;

	void imp_onTick()
	{
		if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - lastMove).count() >= intervalDis(gen))
		{
			setPosX(moveDis(gen));
			setPosY(moveDis(gen));
			lastMove = std::chrono::steady_clock::now();
		}

		ren << flat::Color(1.0f, 1.0f, 1.0f, 1.0f) << flat::TextureOffset(0.0f, 0.0f, 1.0f, 1.0f) << getCurrentTexture() << flat::Rectangle(getPosX(), getPosY(), 0.0f, getWidth(), getHeight(), getRotate());
		// DEBUG: draw text
		//ren << flat::Color(sin(glfwGetTime()), 1.0f, 1.0f, 1.0f) << flat::TextureOffset(0.0f, 0.0f, 1.0f, 1.0f) << (*unifont)('H') << flat::Rectangle(0.0f, 0.0f, 0.0f, 0.025f, 0.025f, 0.0f);
		//ren << flat::Color(sin(glfwGetTime()), 1.0f, 1.0f, 1.0f) << flat::TextureOffset(0.0f, 0.0f, 1.0f, 1.0f) << (*unifont)('E') << flat::Rectangle(0.075f, 0.0f, 0.0f, 0.025f, 0.025f, 0.0f);
		//ren << flat::Color(sin(glfwGetTime()), 1.0f, 1.0f, 1.0f) << flat::TextureOffset(0.0f, 0.0f, 1.0f, 1.0f) << (*unifont)('L') << flat::Rectangle(0.15f, 0.0f, 0.0f, 0.025f, 0.025f, 0.0f);
		//ren << flat::Color(sin(glfwGetTime()), 1.0f, 1.0f, 1.0f) << flat::TextureOffset(0.0f, 0.0f, 1.0f, 1.0f) << (*unifont)('L') << flat::Rectangle(0.225f, 0.0f, 0.0f, 0.025f, 0.025f, 0.0f);
		//ren << flat::Color(sin(glfwGetTime()), 1.0f, 1.0f, 1.0f) << flat::TextureOffset(0.0f, 0.0f, 1.0f, 1.0f) << (*unifont)('O') << flat::Rectangle(0.3f, 0.0f, 0.0f, 0.025f, 0.025f, 0.0f);
		// end
	}
};

int main()
{
	auto source = mixer.genAudioSource();
	auto mp3 = mixer.genAudio("sounds/demo_sounds_relaxed-vlog-night-street-131746.mp3");

	(*source)[flat::AudioAttribType::looping](true);
	(*source)[flat::AudioAttribType::gain](0.2f);
	mixer << flat::AudioAttrib(flat::AudioAttribType::gain, 0.75f) << (*source)(*mp3);

	flat::GameObject<Man>&& man = Man();
	flat::GameObject<Background>&& background = Background();

	auto otherMen = std::make_unique<Man2[]>(8);

	while (true)
	{
		if (keyboard.checkKey(GLFW_KEY_ESCAPE))
			break;
		if (mouse.checkMouseLeft())
			mixer << flat::StopFlag(*source);
		if (mouse.checkMouseRight())
			mixer << flat::ResumeFlag(*source);

		background.onTick();
		man.onTick();
		for (int i = 0; i < 8; i++)
			otherMen[i].onTick();

		//pipe.onTick();

		//DEBUG: hit check
		//for(int i = 0;i < 1024;i++)
		//	if (man.collisionCheck(otherMen[i]))
		//		std::cout << "Hit!\n";
		//end

		std::this_thread::sleep_until(std::chrono::steady_clock::now() + std::chrono::milliseconds(12));

		win.updateWindow();
	}

	return 0;
}
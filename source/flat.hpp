#pragma once

#include <array>

#include "sound.hpp"
#include "draw.hpp"

namespace flat
{
	class GameObject : public SoundSource, public Drawmeta
	{
	private:
		uint32_t id;

	protected:
		GameObject();
		~GameObject();
		uint32_t getId();
		void setId(uint32_t n);

		virtual void onTick();
		virtual void onCreate();
		virtual void onDestory();
	};

	class Camera : public Listener, public Painter
	{
	public:
		Camera();
		~Camera();
		void draw(GameObject &go);
	};

	class GamePlay
	{
	private:
		std::array<bool,GLFW_KEY_LAST> keys;
		double mouseX, mouseY;
		bool mouseRightClick;
		bool mouseMiddleClick;
		bool mouseLeftClick;
		void updateTick();
		void updateInput();

	protected:
		Camera camera;
		void updateFrame();
		virtual void customUpdateTick();
		virtual void customUpdateInput();

	public:
		GamePlay();
		~GamePlay();
		void update();
		void destroyGLFW();
		const double &getMousePosX();
		const double &getMousePosY();
		const bool &checkMouseLeftClick();
		const bool &checkMouseMiddleClick();
		const bool &checkMouseRightClick();
		const bool &checkKey(int key);
		bool runing;
	};
}
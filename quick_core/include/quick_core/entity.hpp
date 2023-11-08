#pragma once
#include <unordered_map>
#include <functional>
#include <stdexcept>
#include <format>
#include <string>
#include <vector>
#include <quick_gl/shader.hpp>

namespace quick3d::core
{
	template <typename FakeEntity>
	class __EntityManager
	{
	private:
		std::unordered_map<std::string, FakeEntity*> entities;

	public:
		__EntityManager() = default;
		__EntityManager(__EntityManager&) = delete;
		~__EntityManager() noexcept
		{
			for (auto& set : entities)
				delete set.second;
		}

		template <typename T, typename... Args>
		requires std::is_base_of<FakeEntity, T>::value
		void add_entity(std::string_view name, Args&&... args) noexcept(false)
		{
			std::string _name(name);
			if (entities.count(_name) > 0)
				throw std::invalid_argument(std::format("entities¡¯ naming conflict (name: {})", name));

			entities[_name] = new T(*this, std::forward<Args>(args)...);
		}

		FakeEntity* get_entity(std::string_view name) noexcept(false)
		{
			return entities.at(std::string(name));
		}

		void remove_entity(std::string_view name) noexcept(false)
		{
			std::string _name(name);
			delete entities.at(_name);
			entities.erase(_name);
		}

		void foreach_on_tick(float delta_ms) noexcept(false)
		{
			for (auto& set : entities)
				set.second->on_tick(delta_ms);
		}

		void foreach_on_draw(float delta_ms) noexcept(false)
		{
			for (auto& set : entities)
				set.second->on_draw(delta_ms);
		}

		void foreach_on_draw(float delta_ms, gl::Program& program) noexcept(false)
		{
			for (auto& set : entities)
				set.second->on_darw_with_shader(delta_ms, program);
		}

		void foreach(std::function<void(std::string,FakeEntity*)> callback) noexcept(false)
		{
			for (auto& set : entities)
				callback(set.first, set.second);
		}
	};

	class System
	{
	protected:
		bool running;

	public:
		System() noexcept;
		virtual void on_tick(float delta_ms) noexcept(false) = 0;
		bool is_running() noexcept;
	};

	class Component
	{
	public:
		virtual void on_tick(float delta_ms) noexcept(false) = 0;
	};

	class Entity
	{
	protected:
		__EntityManager<Entity>& entity_manager;

	public:
		Entity(__EntityManager<Entity>& manager) noexcept;
		virtual void on_tick(float delta_ms) noexcept(false) = 0;
		virtual void on_draw(float delta_ms) noexcept(false) = 0;
		virtual void on_darw_with_shader(float delta_ms, quick3d::gl::Program& program) noexcept(false) = 0;
	};

	using EntityManager = __EntityManager<Entity>;
}
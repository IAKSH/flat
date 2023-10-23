#pragma once
#include <unordered_map>
#include <stdexcept>
#include <format>
#include <string>
#include <vector>

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
				throw std::invalid_argument(std::format("entities’ naming conflict (name: {})", name));

			auto ptr{ new T(*this,std::forward<Args>(args)...) };
			entities[_name] = ptr;
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

	// TODO: 缺少一种从Component访问所在Entity，以及其他Entity数据的方式
	// TODO: 缺少一种同Entity中各Component相互访问的方式
	// 简而言之，需要建立一个（或多个）观察者模式，让Components，Entities能够相互访问。
	// 但是按照经验而言，似乎类似Qt的那种插槽与回调式的设计更好 （好像不尽然，因为那种插槽架构依赖预处理器，以及可能需要考虑单例模式）
	// 还有，肯定不能用消息队列了，至少不是多周期（帧）的消息队列
	// 
	// 这会涉及到一个，由谁来管理数据的问题
	// 我的意见是让需要数据的人拥有数据，但是不要定死，毕竟这样做肯定会缺少一些资源复用的优化
	// 剩下的就不是quick3d::core需要考虑的了

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
	};

	using EntityManager = __EntityManager<Entity>;
}
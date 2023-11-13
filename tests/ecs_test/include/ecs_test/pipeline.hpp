#pragma once

#include <vector>
#include <memory>
#include <string>
#include <format>
#include <stdexcept>

namespace quick3d::test
{
	template <typename FakePass>
	class __Pipeline
	{
	private:
		// ����Passֻ�ڹ���ʱ���ң�Ȼ�󱣴���ҵ���ָ�룬����������ҵ�ʱ�临�Ӷȴ�һ��Ҳ��̫����ν
		std::vector<std::unique_ptr<std::pair<std::string, std::unique_ptr<FakePass>>>> passes;

	public:
		__Pipeline() = default;
		__Pipeline(__Pipeline&) = delete;
		~__Pipeline() = default;

		template <typename T, typename... Args>
		requires std::derived_from<T, FakePass>
		void add_pass(std::string_view name, Args&&... args) noexcept(false)
		{
			passes.push_back(
				std::make_unique<std::pair<std::string, std::unique_ptr<FakePass>>>(name, std::make_unique<T>(*this, std::forward<Args>(args)...)));
		}

		void exec(float delta) noexcept(false)
		{
			for (auto& pair : passes)
				pair->second->draw(delta);
		}

		FakePass* get_pass(std::string_view name) noexcept(false)
		{
			std::pair<int, float> a;
			for (auto& pair : passes)
			{
				if (pair->first == name)
					return pair->second.get();
			}
			throw std::runtime_error(std::format("can't find pass \"{}\" from pipeline", name));
		}
	};

	class Pass
	{
	private:
		__Pipeline<Pass>& pipeline;

	public:
		Pass(__Pipeline<Pass>& pipeline) noexcept;
		Pass(Pass&) = delete;
		~Pass() = default;
		virtual void draw(float delta) noexcept(false) = 0;
	};

	using Pipeline = __Pipeline<Pass>;
}
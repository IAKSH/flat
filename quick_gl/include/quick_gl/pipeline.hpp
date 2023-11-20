#pragma once

#include <vector>
#include <memory>
#include <string>
#include <stdexcept>

namespace quick3d::gl
{
	template <typename FakePass>
	class __Pipeline
	{
	private:
		std::vector<std::unique_ptr<FakePass>> passes;

	public:
		__Pipeline() = default;
		__Pipeline(__Pipeline&) = delete;
		~__Pipeline() = default;

		template <typename T, typename... Args>
		requires std::derived_from<T, FakePass>
		T* add_pass(Args&&... args) noexcept(false)
		{
			std::unique_ptr<FakePass> pass{ std::make_unique<T>(std::forward<Args>(args)...) };
			T* pass_ptr{ reinterpret_cast<T*>(pass.get()) };
			passes.push_back(std::move(pass));
			return pass_ptr;
		}

		void exec() noexcept(false)
		{
			for (auto& pair : passes)
				pair->exec();
		}
	};

	class Pass
	{
	public:
		Pass() = default;
		Pass(Pass&) = delete;
		~Pass() = default;
		virtual void exec() noexcept(false) = 0;
	};

	using Pipeline = __Pipeline<Pass>;
}
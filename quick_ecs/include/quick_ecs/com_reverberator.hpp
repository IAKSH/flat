#pragma once

#include <quick_ecs/sys_sfx.hpp>

namespace quick3d::ecs
{
	// Reverberator 混响器
	// 实际上就是一个 Source 和可选的 Buffer。不包括 Listner，因为由 sys_sfx 管理
	// 使用 Reverberator 即可完成音频播放，Reverberator 会尽可能将数据全局唯一地存储（到 sys_sfx）
	// 可能通过继承来扩展出特化的混响器

	class Reverberator : public Component
	{
	protected:
		virtual void on_create() noexcept(false) override;
		virtual void on_destroy() noexcept(false) override;

	public:
		Reverberator() noexcept;
		Reverberator(Reverberator&) = delete;
		~Reverberator() noexcept;

		virtual void on_attach() noexcept(false) override;
		virtual void on_disattach() noexcept(false) override;
		virtual void on_tick(float delta_ms) noexcept(false) override;
	};
}
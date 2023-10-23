#pragma once

#include <quick_core/com_renderer.hpp>

namespace quick3d::test
{
	// 继承出来的具体Entity的Renderer类，Type Object
	// 这里是Renderer继承树的叶，有关GPU的部分，到此为止了
	// 至于从Entity操控Renderer的过程，由你自己在这里实现API的导出
	// 最简单的方式（虽然不是很优雅），就是直接导出shader program，在外部（entity中）设置uniform
	// 但是通常来说，都是用UBO/SSBO的，这种情况就还是在该类中进行，只导出部分控制API
	// TODO: 关于UBO和SSBO的绑定问题，这俩的绑定点会冲突，可能需要在quick3d::gl中对其进行一定的封装
	class YaeRenderer : public core::InstanceModelRenderer
	{
	private:
		inline static struct ModelData
		{
			glm::mat4 model[10];
		} model_data;
		gl::Buffer ssbo_model;

		void setup_model_data() noexcept(false);
		void load_shader_program() noexcept(false);
		void load_model() noexcept(false);
		void modify_renderer() noexcept;

	public:
		YaeRenderer() noexcept(false);
		YaeRenderer(YaeRenderer&) = delete;
		~YaeRenderer() noexcept;
		void set_instance_count(int instance) noexcept;
	};

	class YaeEntity : public core::Entity
	{
	private:
		YaeRenderer ren;

	public:
		YaeEntity(core::EntityManager& manager) noexcept;
		YaeEntity(YaeEntity&) = delete;
		~YaeEntity() = default;
		void set_instance_count(int instance) noexcept;
		virtual void on_tick(float delta_ms) noexcept(false) override final;
	};
}
#pragma once

#include <quick_core/com_renderer.hpp>

namespace quick3d::test
{
	// �̳г����ľ���Entity��Renderer�࣬Type Object
	// ������Renderer�̳�����Ҷ���й�GPU�Ĳ��֣�����Ϊֹ��
	// ���ڴ�Entity�ٿ�Renderer�Ĺ��̣������Լ�������ʵ��API�ĵ���
	// ��򵥵ķ�ʽ����Ȼ���Ǻ����ţ�������ֱ�ӵ���shader program�����ⲿ��entity�У�����uniform
	// ����ͨ����˵��������UBO/SSBO�ģ���������ͻ����ڸ����н��У�ֻ�������ֿ���API
	// TODO: ����UBO��SSBO�İ����⣬�����İ󶨵���ͻ��������Ҫ��quick3d::gl�ж������һ���ķ�װ
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
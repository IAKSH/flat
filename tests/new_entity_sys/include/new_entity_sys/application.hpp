#pragma once

#include <quick_gl/window.hpp>
#include <quick_gl/pipeline.hpp>
#include <quick_gl/shader.hpp>
#include <quick_gl/buffer.hpp>
#include <quick_gl/model.hpp>
#include <quick_gl/camera.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace quick3d::test
{
	class TestPass : public gl::Pass
	{
	private:
		struct FinalBonesMatricesUBO
		{
			glm::mat4 mats[1000];
		};
		gl::Buffer final_bones_matrices_ubo;

		gl::Camera& camera;
		gl::Program program;
		gl::Program ani_program;
		std::unique_ptr<gl::Mesh> cube_mesh;
		std::unique_ptr<gl::Model> character_model;
		std::unique_ptr<gl::Animator> character_animator;
		std::unique_ptr<gl::Animation> dance_animation;

		void intialize_shader() noexcept;
		void load_character_model() noexcept(false);
		void load_character_animation() noexcept(false);
		void load_cube_mesh() noexcept(false);

	public:
		TestPass(quick3d::gl::GLSLManager& glsl_manager, gl::Camera& camera) noexcept(false);
		TestPass(TestPass&) = delete;
		~TestPass() = default;
		virtual void exec() noexcept(false) override final;
	};

	class Layer
	{
	public:
		virtual void exec() noexcept(false) = 0;
	};

	// ���𴴽����ڣ��Լ�����
	// �Լ�����������루���ܣ�����
	//                 gl::Window�������ص�API�ģ�Ӧ�ÿ����ɴ�ʵ����Ϸ�ľ����߼������룬��Ⱦ�ķ��루����layer
	class WindowLayer : public Layer
	{
	protected:
		gl::Window window;

		// ���ã���Ҫ��һ�ַ�ʽ
		void correct_gl_viewport() noexcept;

	public:
		WindowLayer(std::string_view name,int w,int h) noexcept;
		WindowLayer(WindowLayer&) = delete;
		~WindowLayer() = default;

		gl::Window& get_window() noexcept;
		virtual void exec() noexcept override final;
	};

	class OESLayer : public Layer
	{
	private:
		gl::Window& window;
		gl::Pipeline pipeline;
		gl::GLSLManager glsl_manager;
		gl::Camera camera;
		double last_recored_time;
		double delta_sec;

		void initialize() noexcept;
		void setup_pipeline() noexcept(false);
		void setup_camera() noexcept;
		void load_glsl() noexcept(false);
		void record_delta_time() noexcept;

	public:
		OESLayer(gl::Window& window) noexcept(false);
		OESLayer(OESLayer&) = delete;
		~OESLayer() = default;

		virtual void exec() noexcept override final;
	};

	// Ҳ����ҪΪImGui�����quick3d::gl::Contextһ���Ķ���
	// �Ѻ�˳�ʼ���������ȥ
	class ImGuiWindowLayer : public WindowLayer
	{
	private:
		ImGuiContext* context;
		void setup_imgui_context();

	public:
		ImGuiWindowLayer(std::string_view name, int w, int h) noexcept;
		ImGuiWindowLayer(ImGuiWindowLayer&) = delete;
		~ImGuiWindowLayer() = default;

		ImGuiContext* get_imgui_context() noexcept;
	};
	
	class ImGuiLayer : public Layer
	{
	private:
		ImGuiContext* imgui_context;
		gl::Window& window;
		std::string_view title;

		void destroy_imgui() noexcept;
		void begin_imgui() noexcept;
		void draw_imgui() noexcept;
		void end_imgui() noexcept;

	public:
		ImGuiLayer(ImGuiWindowLayer& window_layer, std::string_view title) noexcept;
		ImGuiLayer(ImGuiLayer&) = delete;
		~ImGuiLayer() noexcept;

		virtual void exec() noexcept override final;
	};

	class WindowUpdateLayer : public Layer
	{
	private:
		std::vector<gl::Window*> windows;

	public:
		WindowUpdateLayer() = default;
		WindowUpdateLayer(WindowUpdateLayer&) = delete;
		~WindowUpdateLayer() = default;

		void add_window(gl::Window& window) noexcept;
		virtual void exec() noexcept override final;
	};

	class Application
	{
	private:
		std::vector<std::unique_ptr<Layer>> layers;
		
	public:
		Application() = default;
		Application(Application&) = delete;
		~Application() = default;

		template <typename T, typename... Args>
		requires std::derived_from<T, Layer>
		T* add_layer(Args&&... args) noexcept(false)
		{
			std::unique_ptr<Layer> layer{ std::make_unique<T>(std::forward<Args>(args)...) };
			T* layer_ptr{ reinterpret_cast<T*>(layer.get()) };
			layers.push_back(std::move(layer));
			return layer_ptr;
		}

		void exec() noexcept;
	};
}
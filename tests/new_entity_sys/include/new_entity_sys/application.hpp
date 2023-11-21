#pragma once

#include <quick_gl/window.hpp>
#include <quick_gl/pipeline.hpp>
#include <quick_gl/shader.hpp>
#include <quick_gl/buffer.hpp>
#include <quick_gl/mesh.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace quick3d::test
{
	class TestPass : public gl::Pass
	{
	private:
		gl::Program program;
		std::unique_ptr<gl::Mesh> mesh;

	public:
		TestPass(quick3d::gl::GLSLManager& glsl_manager) noexcept(false);
		TestPass(TestPass&) = delete;
		~TestPass() = default;
		virtual void exec() noexcept(false) override final;
	};

	class Layer
	{
	public:
		virtual void exec() noexcept(false) = 0;
	};

	// 负责创建窗口（以及其后端
	// 以及键盘鼠标输入（可能，待定
	//                 gl::Window是有做回调API的，应该可以由此实现游戏的具体逻辑与输入，渲染的分离（三个layer
	class WindowLayer : public Layer
	{
	protected:
		gl::Window window;

		// 不好，需要换一种方式
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
		double last_recored_time;
		double delta_sec;

		void initialize() noexcept;
		void setup_pipeline() noexcept(false);
		void load_glsl() noexcept(false);
		void record_delta_time() noexcept;

	public:
		OESLayer(gl::Window& window) noexcept(false);
		OESLayer(OESLayer&) = delete;
		~OESLayer() = default;

		virtual void exec() noexcept override final;
	};

	// 也许需要为ImGui搞个和quick3d::gl::Context一样的东西
	// 把后端初始化给分离出去
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
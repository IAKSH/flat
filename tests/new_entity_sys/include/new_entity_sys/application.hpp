#pragma once

#include <quick_gl/window.hpp>
#include <quick_gl/pipeline.hpp>
#include <quick_gl/shader.hpp>
#include <quick_gl/buffer.hpp>
#include <quick_gl/vao.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace quick3d::test
{
	inline static constexpr std::array<float, 20> QUAD_VERTICES
	{
		// Positions       // Texture Coords
		-1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
	};

	class TestPass : public gl::Pass
	{
	private:
		quick3d::gl::Program program;
		quick3d::gl::Buffer vbo;
		quick3d::gl::VertexArray vao;

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

	class OESLayer : public Layer
	{
	private:
		gl::Window window;
		gl::Pipeline pipeline;
		gl::GLSLManager glsl_manager;
		double last_recored_time;
		double delta_sec;

		void initialize() noexcept;
		void setup_pipeline() noexcept(false);
		void load_glsl() noexcept(false);
		void record_delta_time() noexcept;

	public:
		OESLayer(std::string_view title, uint32_t window_w, uint32_t window_h) noexcept(false);
		OESLayer() noexcept;
		OESLayer(OESLayer&) = delete;
		~OESLayer() = default;

		void exec() noexcept;
		gl::Window& get_window() noexcept;
	};

	class DebugImGuiLayer : public Layer
	{
	private:
		ImGuiIO* io;

		void initialize_imgui() noexcept;
		void begin_imgui() noexcept;
		void draw_imgui() noexcept;
		void flush_imgui() noexcept;
		void destroy_imgui() noexcept;

	public:
		DebugImGuiLayer() noexcept;
		DebugImGuiLayer(DebugImGuiLayer&) = delete;
		~DebugImGuiLayer() noexcept;

		void exec() noexcept;
	};

	class WindowUpdateLayer : public Layer
	{
	private:
		std::vector<gl::Window*> windows;

	public:
		WindowUpdateLayer() noexcept;
		WindowUpdateLayer(WindowUpdateLayer&) = delete;
		~WindowUpdateLayer() = default;

		void add_context(gl::Window& window) noexcept;
		void exec() noexcept;
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
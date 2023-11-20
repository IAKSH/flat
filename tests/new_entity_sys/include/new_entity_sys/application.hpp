#pragma once

#include <quick_gl/context.hpp>
#include <quick_gl/pipeline.hpp>
#include <quick_gl/shader.hpp>
#include <quick_gl/buffer.hpp>
#include <quick_gl/vao.hpp>

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

	class Application
	{
	private:
		gl::Context context;
		gl::Pipeline pipeline;
		gl::GLSLManager glsl_manager;
		double last_recored_time;
		double delta_sec;

		void initialize() noexcept;
		void setup_pipeline() noexcept(false);
		void load_glsl() noexcept(false);
		void record_delta_time() noexcept;
		void do_tick() noexcept(false);

	public:
		Application(std::string_view title, uint32_t window_w, uint32_t window_h) noexcept;
		Application(Application&) = delete;
		~Application() = default;

		void run() noexcept;
	};
}
#pragma once

#include <quick_gl/shader.hpp>
#include <quick_gl/texture.hpp>
#include <quick_gl/frame.hpp>
#include <quick_gl/cubemap.hpp>
#include <quick_gl/vao.hpp>
#include <quick_core/sys_gfx.hpp>
#include <ecs_test/pipeline.hpp>

namespace quick3d::test
{
	inline static constexpr std::string_view POINT_SHADOW_GLSL_VS_PATH = "../../../../tests/ecs_test/glsl/point_shadow_vs.glsl";
	inline static constexpr std::string_view POINT_SHADOW_GLSL_GS_PATH = "../../../../tests/ecs_test/glsl/point_shadow_gs.glsl";
	inline static constexpr std::string_view POINT_SHADOW_GLSL_FS_PATH = "../../../../tests/ecs_test/glsl/point_shadow_fs.glsl";
	inline static constexpr std::string_view DIRECT_SHADOW_GLSL_VS_PATH = "../../../../tests/ecs_test/glsl/direct_shadow_vs.glsl";
	inline static constexpr std::string_view DIRECT_SHADOW_GLSL_FS_PATH = "../../../../tests/ecs_test/glsl/direct_shadow_fs.glsl";
	inline static constexpr std::string_view POST_GLSL_VS_PATH = "../../../../tests/ecs_test/glsl/post_vs.glsl";
	inline static constexpr std::string_view POST_GLSL_FS_PATH = "../../../../tests/ecs_test/glsl/post_fs.glsl";
	inline static constexpr std::string_view BLUR_GLSL_VS_PATH = "../../../../tests/ecs_test/glsl/blur_vs.glsl";
	inline static constexpr std::string_view BLUR_GLSL_FS_PATH = "../../../../tests/ecs_test/glsl/blur_fs.glsl";
	inline static constexpr std::string_view DEBUG_VIEW_GLSL_VS_PATH = "../../../../tests/ecs_test/glsl/debug_view_vs.glsl";
	inline static constexpr std::string_view DEBUG_VIEW_GLSL_FS_PATH = "../../../../tests/ecs_test/glsl/debug_view_fs.glsl";
	inline static constexpr int SCREEN_WIDTH{ 853 };
	inline static constexpr int SCREEN_HEIGHT{ 600 };
	inline static constexpr float SHADOW_WIDTH{ 1024 };
	inline static constexpr float SHADOW_HEIGHT{ 1024 };

	inline static constexpr std::array<float, 20> QUAD_VERTICES
	{
		// Positions        // Texture Coords
		-1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
	};

	static struct DemoSettings
	{
		int yae_instance{ 1 };
		int box_instance{ 1 };
		int light_ball_instance{ 1 };
		bool enable_bilnn_phong{ true };
		bool enable_exposure{ true };
		bool enable_bloom{ true };
		bool enable_point_shadow{ false };
		bool enable_direct_shadow{ true };
		float gamma{ 2.2f };
		float hdr_exposure{ 1.0f };
		glm::vec3 sun_light_ambient{ 1.0f, 1.0f, 1.0f };
		glm::vec3 sun_light_direction{ -10.0f, -10.0f, -10.0f };
	};

	class DirectShadowPass : public Pass
	{
	private:
		quick3d::core::GFXSystem& gfx;
		quick3d::core::EntityManager& entity_manager;
		DemoSettings& settings;

		quick3d::gl::Texture tex;
		quick3d::gl::DepthFramebuffer frame;
		quick3d::gl::Program program;
		glm::mat4 lightProjection;
		glm::mat4 lightView;
		glm::mat4 lightSpaceMatrix;
		glm::vec3 light_pos;
		float near_plane;
		float far_plane;

	public:
		DirectShadowPass(Pipeline& pipeline, quick3d::core::GFXSystem& gfx,
			quick3d::core::EntityManager& entity_manager, DemoSettings& settings) noexcept(false);
		DirectShadowPass(DirectShadowPass&) = delete;
		~DirectShadowPass() = default;

		virtual void draw(float delta) noexcept(false) override final;
		quick3d::gl::Texture& get_tex() noexcept;
	};

	class PointShadowPass : public Pass
	{
	private:
		quick3d::core::EntityManager& entity_manager;
		DemoSettings& settings;

		quick3d::gl::DepthCubeMap cubemap;
		quick3d::gl::DepthFramebuffer frame;
		quick3d::gl::Program program;
		float near_plane;
		float far_plane;
		glm::vec3 light_pos;
		glm::mat4 shadow_proj;
		std::array<glm::mat4, 6> shadow_transforms;

	public:
		PointShadowPass(Pipeline& pipeline, quick3d::core::EntityManager& entity_manager, DemoSettings& settings) noexcept(false);
		PointShadowPass(PointShadowPass&) = delete;
		~PointShadowPass() = default;

		virtual void draw(float delta) noexcept(false) override final;
		quick3d::gl::DepthCubeMap& get_cubemap() noexcept;
	};

	class RawScenePass : public Pass
	{
	private:
		quick3d::core::EntityManager& entity_manager;

		quick3d::gl::Texture blur_tex;
		quick3d::gl::Texture raw_tex;
		quick3d::gl::ColorFramebuffer frame;

		DirectShadowPass* direct_shadow_pass;
		PointShadowPass* point_shadow_pass;

	public:
		RawScenePass(Pipeline& pipeline, quick3d::core::EntityManager& entity_manager) noexcept(false);
		RawScenePass(RawScenePass&) = delete;
		~RawScenePass() = default;

		virtual void draw(float delta) noexcept(false) override final;
		quick3d::gl::Texture& get_blur_tex() noexcept;
		quick3d::gl::Texture& get_raw_tex() noexcept;
	};

	class BloomPass : public Pass
	{
	private:
		quick3d::gl::Buffer vbo;
		quick3d::gl::VertexArray vao;
		quick3d::gl::Program blur_program;
		std::array<quick3d::gl::Texture, 2> blur_pingpong_texs;
		std::array<quick3d::gl::ColorFramebuffer, 2> blur_pingpong_frames;
		bool horizontal;

		RawScenePass* raw_scene_pass;

	public:
		BloomPass(Pipeline& pipeline) noexcept(false);
		BloomPass(BloomPass&) = delete;
		~BloomPass() = default;

		virtual void draw(float delta) noexcept(false) override final;
		std::array<quick3d::gl::Texture, 2>& get_blur_pingpong_texs() noexcept;
		bool get_horizontal() noexcept;
	};

	class HDRBlendPass : public Pass
	{
	private:
		DemoSettings& settings;

		quick3d::gl::Buffer vbo;
		quick3d::gl::VertexArray vao;
		quick3d::gl::Program program;

		RawScenePass* raw_scene_pass;
		BloomPass* bloom_pass;

	public:
		HDRBlendPass(Pipeline& pipeline, DemoSettings& settings) noexcept(false);
		HDRBlendPass(HDRBlendPass&) = delete;
		~HDRBlendPass() = default;

		virtual void draw(float delta) noexcept(false) override final;
	};

	class BloomDebugPass : public Pass
	{
	private:
		quick3d::gl::Buffer vbo;
		quick3d::gl::VertexArray vao;
		quick3d::gl::Program program;

		BloomPass* bloom_pass;
		RawScenePass* raw_scene_pass;

	public:
		BloomDebugPass(Pipeline& pipeline) noexcept(false);
		BloomDebugPass(BloomDebugPass&) = delete;
		~BloomDebugPass() = default;

		virtual void draw(float delta) noexcept(false) override final;
	};

	class RawDebugPass : public Pass
	{
	private:
		quick3d::gl::Buffer vbo;
		quick3d::gl::VertexArray vao;
		quick3d::gl::Program program;

		RawScenePass* raw_scene_pass;

	public:
		RawDebugPass(Pipeline& pipeline) noexcept(false);
		RawDebugPass(RawDebugPass&) = delete;
		~RawDebugPass() = default;

		virtual void draw(float delta) noexcept(false) override final;
	};

	class DirectShadowDebugPass : public Pass
	{
	private:
		quick3d::gl::Buffer vbo;
		quick3d::gl::VertexArray vao;
		quick3d::gl::Program program;

		DirectShadowPass* direct_shadow_pass;

	public:
		DirectShadowDebugPass(Pipeline& pipeline) noexcept(false);
		DirectShadowDebugPass(DirectShadowDebugPass&) = delete;
		~DirectShadowDebugPass() = default;

		virtual void draw(float delta) noexcept(false) override final;
	};
}
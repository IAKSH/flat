#include <ecs_test/my_passes.hpp>

quick3d::test::DirectShadowPass::DirectShadowPass(Pipeline& pipeline, quick3d::core::GFXSystem& gfx, quick3d::core::EntityManager& entity_manager, DemoSettings& settings) noexcept(false)
	: tex(GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, true),
	frame(tex),
	program(
		(quick3d::gl::GLSLReader(DIRECT_SHADOW_GLSL_VS_PATH)),
		(quick3d::gl::GLSLReader(DIRECT_SHADOW_GLSL_FS_PATH))
	),
	near_plane(1.0f),
	far_plane(25.0f),
	gfx(gfx),
	settings(settings),
	entity_manager(entity_manager),
	Pass(pipeline)
{
}

void quick3d::test::DirectShadowPass::draw(float delta) noexcept(false)
{
	glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
	glBindFramebuffer(GL_FRAMEBUFFER, frame.get_fbo_id());
	glClear(GL_DEPTH_BUFFER_BIT);

	light_pos = -settings.sun_light_direction;
	// 这个投影有问题
	lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
	lightView = glm::lookAt(light_pos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	lightSpaceMatrix = lightProjection * lightView;
	gfx.set_lightspace_matrix(lightSpaceMatrix);
	program.set_uniform("lightSpaceMatrix", lightSpaceMatrix);
	entity_manager.foreach([&](std::string name, quick3d::core::Entity* entity)
		{
			if (name != "light_ball" && name != "skybox")
				entity->on_darw_with_shader(delta, program);
		});
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

quick3d::gl::Texture& quick3d::test::DirectShadowPass::get_tex() noexcept
{
	return tex;
}

quick3d::test::PointShadowPass::PointShadowPass(Pipeline& pipeline, quick3d::core::EntityManager& entity_manager, DemoSettings& settings) noexcept(false)
	: cubemap(SHADOW_WIDTH, SHADOW_HEIGHT),
	frame(cubemap),
	program(
		(quick3d::gl::GLSLReader(POINT_SHADOW_GLSL_VS_PATH)),
		(quick3d::gl::GLSLReader(POINT_SHADOW_GLSL_GS_PATH)),
		(quick3d::gl::GLSLReader(POINT_SHADOW_GLSL_FS_PATH))
	),
	shadow_proj(glm::perspective(glm::radians(90.0f), SHADOW_WIDTH / SHADOW_HEIGHT, near_plane, far_plane)),
	near_plane(1.0f),
	far_plane(25.0f),
	entity_manager(entity_manager),
	settings(settings),
	Pass(pipeline)
{
}

void quick3d::test::PointShadowPass::draw(float delta) noexcept(false)
{
	light_pos = -settings.sun_light_direction;
	shadow_transforms[0] = shadow_proj * glm::lookAt(light_pos, light_pos + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f));
	shadow_transforms[1] = shadow_proj * glm::lookAt(light_pos, light_pos + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f));
	shadow_transforms[2] = shadow_proj * glm::lookAt(light_pos, light_pos + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	shadow_transforms[3] = shadow_proj * glm::lookAt(light_pos, light_pos + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
	shadow_transforms[4] = shadow_proj * glm::lookAt(light_pos, light_pos + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f));
	shadow_transforms[5] = shadow_proj * glm::lookAt(light_pos, light_pos + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f));
	for (unsigned int i = 0; i < 6; ++i)
		program.set_uniform(std::format("shadowMatrices[{}]", i), shadow_transforms[i]);
	program.set_uniform("far_plane", far_plane);
	program.set_uniform("lightPos", light_pos);

	glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
	glBindFramebuffer(GL_FRAMEBUFFER, frame.get_fbo_id());
	glClear(GL_DEPTH_BUFFER_BIT);
	entity_manager.foreach([&](std::string name, quick3d::core::Entity* entity)
		{
			if (name != "light_ball" && name != "skybox")
				entity->on_darw_with_shader(delta, program);
		});
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

quick3d::gl::DepthCubeMap& quick3d::test::PointShadowPass::get_cubemap() noexcept
{
	return cubemap;
}

quick3d::test::RawScenePass::RawScenePass(Pipeline& pipeline, quick3d::core::EntityManager& entity_manager) noexcept(false)
	: raw_tex(GL_RGB16F, SCREEN_WIDTH, SCREEN_HEIGHT, true),
	blur_tex(GL_RGB16F, SCREEN_WIDTH, SCREEN_HEIGHT, true),
	frame(SCREEN_WIDTH, SCREEN_HEIGHT),
	entity_manager(entity_manager),
	outline_program(
		(quick3d::gl::GLSLReader(OUTLINE_GLSL_VS_PATH)),
		(quick3d::gl::GLSLReader(OUTLINE_GLSL_FS_PATH))
	),
	Pass(pipeline)
{
	// 或许需要修改，不使用dynamic cast
	// 虽然这个过程应该只会进行一次
	// 所以，问题不大？
	direct_shadow_pass = dynamic_cast<DirectShadowPass*>(pipeline.get_pass("direct_shadow_pass"));
	point_shadow_pass = dynamic_cast<PointShadowPass*>(pipeline.get_pass("point_shadow_pass"));

	frame.bind_texture_to_fbo(GL_COLOR_ATTACHMENT0, raw_tex.get_tex_id());
	frame.bind_texture_to_fbo(GL_COLOR_ATTACHMENT1, blur_tex.get_tex_id());
	frame.set_draw_targets({ GL_COLOR_ATTACHMENT0,GL_COLOR_ATTACHMENT1 });
}

void quick3d::test::RawScenePass::draw(float delta) noexcept(false)
{
	glBindFramebuffer(GL_FRAMEBUFFER, frame.get_fbo_id());
	glStencilMask(0xFF);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_REPLACE, GL_REPLACE);

	entity_manager.foreach([&](std::string_view name,quick3d::core::Entity* entity)
	{
		// 绘制物体并写入模板缓冲
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		if(name == "skybox")
			glStencilMask(0x00);
		else
			glStencilMask(0xFF);
		glEnable(GL_DEPTH_TEST);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, direct_shadow_pass->get_tex().get_tex_id());
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_CUBE_MAP, point_shadow_pass->get_cubemap().get_cubemap_id());
		entity->on_draw(delta);

		// 根据模板缓冲进行描边
		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		glStencilMask(0x00);
		glDisable(GL_DEPTH_TEST);
		entity->on_darw_with_shader(delta, outline_program);

		glStencilMask(0xFF);
		glClear(GL_STENCIL_BUFFER_BIT);
	});

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_STENCIL_TEST);
}

quick3d::gl::Texture& quick3d::test::RawScenePass::get_blur_tex() noexcept
{
	return blur_tex;
}

quick3d::gl::Texture& quick3d::test::RawScenePass::get_raw_tex() noexcept
{
	return raw_tex;
}

quick3d::test::BloomPass::BloomPass(Pipeline& pipeline) noexcept(false)
	: vbo(GL_ARRAY_BUFFER, GL_STATIC_DRAW, sizeof(QUAD_VERTICES)),
	bloom_program(
		(quick3d::gl::GLSLReader(BLOOM_GLSL_VS_PATH)),
		(quick3d::gl::GLSLReader(BLOOM_GLSL_FS_PATH))
	),
	bloom_tex(GL_RGB16F, SCREEN_WIDTH, SCREEN_HEIGHT, true),
	bloom_frame(SCREEN_WIDTH, SCREEN_HEIGHT),
	Pass(pipeline)
{
	raw_scene_pass = dynamic_cast<RawScenePass*>(pipeline.get_pass("raw_scene_pass"));

	vbo.write_buffer_data(QUAD_VERTICES);
	vao.add_attrib(vbo, 0, 3, 5, 0);
	vao.add_attrib(vbo, 1, 2, 5, 3);

	bloom_frame.bind_texture_to_fbo(GL_COLOR_ATTACHMENT0, bloom_tex.get_tex_id());
}

void quick3d::test::BloomPass::draw(float delta) noexcept(false)
{
	glBindFramebuffer(GL_FRAMEBUFFER, bloom_frame.get_fbo_id());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, raw_scene_pass->get_blur_tex().get_tex_id());
	vao.draw(bloom_program, GL_TRIANGLE_STRIP, 0, QUAD_VERTICES.size());
}

quick3d::gl::Texture& quick3d::test::BloomPass::get_bloom_tex() noexcept
{
	return bloom_tex;
}

quick3d::test::HDRBlendPass::HDRBlendPass(Pipeline& pipeline, DemoSettings& settings) noexcept(false)
	: vbo(GL_ARRAY_BUFFER, GL_STATIC_DRAW, sizeof(QUAD_VERTICES)),
	program(
		(quick3d::gl::GLSLReader(POST_GLSL_VS_PATH)),
		(quick3d::gl::GLSLReader(POST_GLSL_FS_PATH))
	),
	settings(settings),
	Pass(pipeline)
{
	fxaa_pass = dynamic_cast<FXAAPass*>(pipeline.get_pass("fxaa_pass"));
	bloom_pass = dynamic_cast<BloomPass*>(pipeline.get_pass("bloom_pass"));

	vbo.write_buffer_data(QUAD_VERTICES);
	vao.add_attrib(vbo, 0, 3, 5, 0);
	vao.add_attrib(vbo, 1, 2, 5, 3);

	program.set_uniform("sceneTex", 0);
	program.set_uniform("bloomTex", 1);
}

void quick3d::test::HDRBlendPass::draw(float delta) noexcept(false)
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, fxaa_pass->get_tex().get_tex_id());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, bloom_pass->get_bloom_tex().get_tex_id());
	program.set_uniform("exposure", settings.hdr_exposure);
	program.set_uniform("enable_exposure", static_cast<int>(settings.enable_exposure));
	program.set_uniform("enableBloom", static_cast<int>(settings.enable_bloom));
	vao.draw(program, GL_TRIANGLE_STRIP, 0, QUAD_VERTICES.size());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 0);
}

quick3d::test::BloomDebugPass::BloomDebugPass(Pipeline& pipeline) noexcept(false)
	: vbo(GL_ARRAY_BUFFER, GL_STATIC_DRAW, sizeof(QUAD_VERTICES)),
	program(
		(quick3d::gl::GLSLReader(DEBUG_VIEW_GLSL_VS_PATH)),
		(quick3d::gl::GLSLReader(DEBUG_VIEW_GLSL_FS_PATH))
	),
	Pass(pipeline)
{
	raw_scene_pass = dynamic_cast<RawScenePass*>(pipeline.get_pass("raw_scene_pass"));
	bloom_pass = dynamic_cast<BloomPass*>(pipeline.get_pass("bloom_pass"));

	vbo.write_buffer_data(QUAD_VERTICES);
	vao.add_attrib(vbo, 0, 3, 5, 0);
	vao.add_attrib(vbo, 1, 2, 5, 3);
}

void quick3d::test::BloomDebugPass::draw(float delta) noexcept(false)
{
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_DEPTH_BUFFER_BIT);
	glActiveTexture(GL_TEXTURE0);

	glBindTexture(GL_TEXTURE_2D, bloom_pass->get_bloom_tex().get_tex_id());
	glViewport(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT);
	vao.draw(program, GL_TRIANGLE_STRIP, 0, QUAD_VERTICES.size());

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

quick3d::test::RawDebugPass::RawDebugPass(Pipeline& pipeline) noexcept(false)
	: vbo(GL_ARRAY_BUFFER, GL_STATIC_DRAW, sizeof(QUAD_VERTICES)),
	program(
		(quick3d::gl::GLSLReader(DEBUG_VIEW_GLSL_VS_PATH)),
		(quick3d::gl::GLSLReader(DEBUG_VIEW_GLSL_FS_PATH))
	),
	Pass(pipeline)
{
	raw_scene_pass = dynamic_cast<RawScenePass*>(pipeline.get_pass("raw_scene_pass"));

	vbo.write_buffer_data(QUAD_VERTICES);
	vao.add_attrib(vbo, 0, 3, 5, 0);
	vao.add_attrib(vbo, 1, 2, 5, 3);
}

void quick3d::test::RawDebugPass::draw(float delta) noexcept(false)
{
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_DEPTH_BUFFER_BIT);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, raw_scene_pass->get_raw_tex().get_tex_id());
	glViewport(0, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT);
	vao.draw(program, GL_TRIANGLE_STRIP, 0, QUAD_VERTICES.size());
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

quick3d::test::DirectShadowDebugPass::DirectShadowDebugPass(Pipeline& pipeline) noexcept(false)
	: vbo(GL_ARRAY_BUFFER, GL_STATIC_DRAW, sizeof(QUAD_VERTICES)),
	program(
		(quick3d::gl::GLSLReader(DEBUG_VIEW_GLSL_VS_PATH)),
		(quick3d::gl::GLSLReader(DEBUG_VIEW_GLSL_FS_PATH))
	),
	Pass(pipeline)
{
	direct_shadow_pass = dynamic_cast<DirectShadowPass*>(pipeline.get_pass("direct_shadow_pass"));

	vbo.write_buffer_data(QUAD_VERTICES);
	vao.add_attrib(vbo, 0, 3, 5, 0);
	vao.add_attrib(vbo, 1, 2, 5, 3);
}

void quick3d::test::DirectShadowDebugPass::draw(float delta) noexcept(false)
{
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_DEPTH_BUFFER_BIT);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, direct_shadow_pass->get_tex().get_tex_id());
	glViewport(SCREEN_WIDTH, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	vao.draw(program, GL_TRIANGLE_STRIP, 0, QUAD_VERTICES.size());
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

quick3d::test::FXAAPass::FXAAPass(Pipeline& pipeline) noexcept
	: vbo(GL_ARRAY_BUFFER, GL_STATIC_DRAW, sizeof(QUAD_VERTICES)),
	program(
		(quick3d::gl::GLSLReader(FXAA_GLSL_VS_PATH)),
		(quick3d::gl::GLSLReader(FXAA_GLSL_FS_PATH))
	),
	tex(GL_RGB16F, SCREEN_WIDTH, SCREEN_HEIGHT, true),
	frame(SCREEN_WIDTH, SCREEN_HEIGHT),
	Pass(pipeline)
{
	raw_scene_pass = dynamic_cast<RawScenePass*>(pipeline.get_pass("raw_scene_pass"));

	frame.bind_texture_to_fbo(GL_COLOR_ATTACHMENT0, tex.get_tex_id());

	vbo.write_buffer_data(QUAD_VERTICES);
	vao.add_attrib(vbo, 0, 3, 5, 0);
	vao.add_attrib(vbo, 1, 2, 5, 3);

	program.set_uniform("resolution", glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT));
}

void quick3d::test::FXAAPass::draw(float delta) noexcept(false)
{
	glBindFramebuffer(GL_FRAMEBUFFER, frame.get_fbo_id());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, raw_scene_pass->get_raw_tex().get_tex_id());
	vao.draw(program, GL_TRIANGLE_STRIP, 0, QUAD_VERTICES.size());
	glBindTexture(GL_TEXTURE_2D, 0);
}

quick3d::gl::Texture& quick3d::test::FXAAPass::get_tex() noexcept
{
	return tex;
}

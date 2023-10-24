#include <ecs_test/skybox.hpp>
#include <array>

static constexpr std::string_view GLSL_FOLDER = "../../../../tests/ecs_test/glsl";
static constexpr std::string_view IMAGE_FOLDER = "../../../../tests/outer_glsl/image";

constexpr std::array<float, 108> skybox_vertices{
	// right
	-1.0f, 1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,

		// left
		-1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,

		// top
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		// bottom
		-1.0f, -1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,

		// front
		-1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,

		// back
		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 1.0f
};

void quick3d::test::SkyboxRenderer::setup_phone_ambient_value() noexcept
{
	phone_ambient = glm::vec3(1.0f, 1.0f, 1.0f);
}

void quick3d::test::SkyboxRenderer::load_shader_program() noexcept(false)
{
	program = new gl::Program(
		quick3d::gl::GLSLReader(std::format("{}/{}", GLSL_FOLDER, "skybox_vs.glsl")).get_glsl(),
		quick3d::gl::GLSLReader(std::format("{}/{}", GLSL_FOLDER, "skybox_fs.glsl")).get_glsl()
	);
	program->bind_uniform_block("CameraMatrix", 0);
}

void quick3d::test::SkyboxRenderer::load_cubemap() noexcept(false)
{
	std::array<std::string, 6> skybox_texture_pathes
	{
		std::format("{}/{}", IMAGE_FOLDER, "right.jpg"),
			std::format("{}/{}", IMAGE_FOLDER, "left.jpg"),
			std::format("{}/{}", IMAGE_FOLDER, "top.jpg"),
			std::format("{}/{}", IMAGE_FOLDER, "bottom.jpg"),
			std::format("{}/{}", IMAGE_FOLDER, "front.jpg"),
			std::format("{}/{}", IMAGE_FOLDER, "back.jpg")
	};
	cubemap = new quick3d::gl::CubeMap(GL_RGBA, 2048, 2048);
	for (int i = 0; i < 6; i++)
		cubemap->generate_texture(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, quick3d::gl::Image(skybox_texture_pathes[i], false));
}

void quick3d::test::SkyboxRenderer::load_vbo_vao() noexcept
{
	vbo = new quick3d::gl::Buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW, skybox_vertices.size() * sizeof(float));
	vbo->write_buffer_data(skybox_vertices);
	vao = new quick3d::gl::VertexArray();
	vao->add_attrib(*vbo, 0, 3, 3, 0);
}

quick3d::test::SkyboxRenderer::SkyboxRenderer() noexcept(false)
{
	load_shader_program();
	load_cubemap();
	load_vbo_vao();
}

quick3d::test::SkyboxRenderer::~SkyboxRenderer() noexcept
{
	delete program;
	delete cubemap;
	delete vao;
	delete vbo;
}

void quick3d::test::SkyboxRenderer::bind_camera(gl::FPSCamera* cam) noexcept
{
	camera = cam;
}

void quick3d::test::SkyboxEntity::try_load_renderer() noexcept(false)
{
	if (!ren)
		ren = std::make_shared<SkyboxRenderer>();
}

quick3d::test::SkyboxEntity::SkyboxEntity(core::EntityManager& manager) noexcept(false)
	: Entity(manager)
{
	try_load_renderer();
}

void quick3d::test::SkyboxEntity::bind_camera(gl::FPSCamera& camera) noexcept
{
	ren->bind_camera(&camera);
}

void quick3d::test::SkyboxEntity::on_tick(float delta_ms) noexcept(false)
{
	ren->on_tick(delta_ms);
}

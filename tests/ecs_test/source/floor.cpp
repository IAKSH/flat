#include <ecs_test/floor.hpp>
#include <array>

static constexpr std::string_view GLSL_FOLDER = "../../../../tests/ecs_test/glsl";
static constexpr std::string_view IMAGE_FOLDER = "../../../../tests/ecs_test/image";

static constexpr std::array<GLfloat, 32> FLOOR_VERTICES
{
	// Positions          // Normals           // Texture Coords
	 1.0f,  0.0f,  1.0f,   0.0f,  1.0f,  0.0f,   1.0f,  1.0f,   // Top Right
	 1.0f,  0.0f, -1.0f,   0.0f,  1.0f,  0.0f,   1.0f,  0.0f,   // Bottom Right
	-1.0f,  0.0f, -1.0f,   0.0f,  1.0f,  0.0f,   0.0f,  0.0f,   // Bottom Left
	-1.0f,  0.0f,  1.0f,   0.0f,  1.0f,  0.0f,   0.0f,  1.0f    // Top Left 
};

static constexpr std::array<unsigned int, 6> FLOOR_INDICES
{
	0,1,2,
	2,3,0
};

void quick3d::test::FloorRenderer::setup_model_ssbo() noexcept
{
	ssbo_model.dma_do([](void* data)
	{
		constexpr float MODEL_SCALE_FACTOR{ 10.0f };
		auto model{ glm::scale(glm::mat4(1.0f),glm::vec3(MODEL_SCALE_FACTOR,MODEL_SCALE_FACTOR,MODEL_SCALE_FACTOR)) };
		auto ptr{ reinterpret_cast<ModelData*>(data) };
		ptr->model[0] = model;
	});
}

void quick3d::test::FloorRenderer::load_shader_program() noexcept(false)
{
	program = new gl::Program(
		gl::GLSLReader(std::format("{}/{}", GLSL_FOLDER, "floor_vs.glsl")),
		gl::GLSLReader(std::format("{}/{}", GLSL_FOLDER, "floor_fs.glsl"))
	);
	program->bind_uniform_block("GFXGlobalUBO", 0);
	program->bind_uniform_block("PhoneDirectLighting", 2);

	program->set_uniform("material.diffuse", 0);
	program->set_uniform("material.specular", 1);
	program->set_uniform("material.depth_map", 2);
	program->set_uniform("material.shininess", 128.0f);

	program->set_uniform("texcoords_scale", 10.0f);
	program->set_uniform("useBlinnPhong", 1);
}

void quick3d::test::FloorRenderer::load_texture() noexcept(false)
{
	textures.push_back(new gl::Texture(GL_SRGB8_ALPHA8, gl::Image(std::format("{}/{}", IMAGE_FOLDER, "floor.png"))));
}

void quick3d::test::FloorRenderer::load_vbo_vao() noexcept
{
	vbo = new gl::Buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW, sizeof(FLOOR_VERTICES));
	vbo->write_buffer_data(FLOOR_VERTICES);
	ebo.write_buffer_data(FLOOR_INDICES);
	vao = new gl::VertexArray();
	vao->bind_ebo(ebo);
	vao->add_attrib(*vbo, 0, 3, 8, 0);
	vao->add_attrib(*vbo, 1, 3, 8, 3);
	vao->add_attrib(*vbo, 2, 2, 8, 6);
}

void quick3d::test::FloorRenderer::draw_indexed_vao() noexcept
{
	draw_indexed_vao(*program);
}

void quick3d::test::FloorRenderer::draw_indexed_vao(gl::Program& program) noexcept
{
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	for (int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, textures[i]->get_tex_id());
	}

	vao->draw(program, GL_TRIANGLES, 0, FLOOR_INDICES.size());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

quick3d::test::FloorRenderer::FloorRenderer() noexcept(false)
	: ebo(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW, sizeof(FLOOR_INDICES)),
		ssbo_model(GL_SHADER_STORAGE_BUFFER, GL_STATIC_DRAW, sizeof(ModelData))
{
	load_shader_program();
	load_texture();
	load_vbo_vao();
	setup_model_ssbo();
}

quick3d::test::FloorRenderer::~FloorRenderer() noexcept
{
	delete program;
	delete vao;
	delete vbo;
	
	for (auto ptr : textures)
		delete ptr;
}

void quick3d::test::FloorRenderer::model_move(const glm::vec3& vec) noexcept
{
	ssbo_model.dma_do([&](void* data)
	{
		auto ptr{ reinterpret_cast<ModelData*>(data) };
		ptr->model[0] = glm::translate(ptr->model[0], vec);
	});
}

void quick3d::test::FloorRenderer::model_rotate(float r, const glm::vec3& axis) noexcept
{
	ssbo_model.dma_do([&](void* data)
	{
		auto ptr{ reinterpret_cast<ModelData*>(data) };
		ptr->model[0] = glm::rotate(ptr->model[0], r, axis);
	});
}

void quick3d::test::FloorRenderer::switch_blinn_phong_lighting(bool b) noexcept
{
	program->set_uniform("useBlinnPhong", static_cast<int>(b));
}

void quick3d::test::FloorRenderer::on_tick(float delta_ms) noexcept(false)
{
	glDisable(GL_CULL_FACE);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, ssbo_model.get_buffer_id());
	draw_indexed_vao();
	glEnable(GL_CULL_FACE);
}

void quick3d::test::FloorRenderer::on_tick(float delta_ms, gl::Program& program) noexcept(false)
{
	glDisable(GL_CULL_FACE);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, ssbo_model.get_buffer_id());
	draw_indexed_vao(program);
	glEnable(GL_CULL_FACE);
}

void quick3d::test::FloorEntity::try_load_renderer() noexcept(false)
{
	if (!ren)
		ren = std::make_shared<FloorRenderer>();
}

quick3d::test::FloorEntity::FloorEntity(core::EntityManager& manager) noexcept(false)
	: Entity(manager)
{
	try_load_renderer();
}

void quick3d::test::FloorEntity::switch_blinn_phong_lighting(bool b) noexcept
{
	ren->switch_blinn_phong_lighting(b);
}

void quick3d::test::FloorEntity::move(const glm::vec3& vec) noexcept
{
	ren->model_move(vec);
}

void quick3d::test::FloorEntity::rotate(float r, const glm::vec3& axis) noexcept
{
	ren->model_rotate(r, axis);
}

void quick3d::test::FloorEntity::on_tick(float delta_ms) noexcept(false)
{
	
}

void quick3d::test::FloorEntity::on_draw(float delta_ms) noexcept(false)
{
	ren->on_tick(delta_ms);
}

void quick3d::test::FloorEntity::on_darw_with_shader(float delta_ms, gl::Program& program) noexcept(false)
{
	ren->on_tick(delta_ms, program);
}

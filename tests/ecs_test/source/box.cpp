#include <ecs_test/box.hpp>
#include <array>

static constexpr std::string_view GLSL_FOLDER = "../../../../tests/ecs_test/glsl";
static constexpr std::string_view IMAGE_FOLDER = "../../../../tests/fine_light/image";

static constexpr std::array<float, 288> box_vertices
{
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

void quick3d::test::BoxRenderer::setup_model_data(std::size_t index) noexcept
{
    ssbo_model.dma_do([&](void* data)
    {
        auto ptr{ reinterpret_cast<ModelData*>(data) };
        auto scale{ glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f)) };
        ptr->model[index] = glm::translate(scale, glm::vec3(position_dis(gen), position_dis(gen) + 20.0f, position_dis(gen)));
    });

    model_rotate_attribs[index].rotate_axis = glm::vec3(rotation_dis(gen), rotation_dis(gen), rotation_dis(gen));
    model_rotate_attribs[index].rotate_speed = static_cast<float>(rotation_dis(gen)) * 10.0f;
}

void quick3d::test::BoxRenderer::rotate_model(float delta_ms) noexcept
{
    ssbo_model.dma_do([&](void* data)
    {
        auto ptr{ reinterpret_cast<ModelData*>(data) };
        for (std::size_t i = 0; i < instance_count; i++)
        {
            float& rotate_speed{ model_rotate_attribs[i].rotate_speed };
            glm::vec3& rotate_axis{ model_rotate_attribs[i].rotate_axis };
            ptr->model[i] = glm::rotate(ptr->model[i], delta_ms * rotate_speed / 10000.0f, rotate_axis);
        }
    });
}

void quick3d::test::BoxRenderer::load_shader_program() noexcept(false)
{
    program = new quick3d::gl::Program(
        quick3d::gl::GLSLReader(std::format("{}/{}", GLSL_FOLDER, "object_vs.glsl")).get_glsl(),
        quick3d::gl::GLSLReader(std::format("{}/{}", GLSL_FOLDER, "object_fs.glsl")).get_glsl()
    );
    program->bind_uniform_block("GFXGlobalUBO", 0);
    program->bind_uniform_block("PhoneDirectLighting", 2);

    program->set_uniform("material.diffuse", 0);
    program->set_uniform("material.specular", 1);
    program->set_uniform("material.shininess", 128.0f);
    program->set_uniform("material.texcoords_scale", 1.0f);

    program->set_uniform("useBlinnPhong", 1);
}

void quick3d::test::BoxRenderer::load_texture() noexcept(false)
{
    textures.push_back(new gl::Texture(GL_SRGB8_ALPHA8, gl::Image(std::format("{}/{}", IMAGE_FOLDER, "container2.png"))));
    textures.push_back(new gl::Texture(GL_SRGB8_ALPHA8, gl::Image(std::format("{}/{}", IMAGE_FOLDER, "container2_specular.png"))));
}

void quick3d::test::BoxRenderer::load_vbo_vao() noexcept
{
    vbo = new gl::Buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW, sizeof(box_vertices));
    vbo->write_buffer_data(box_vertices);

    vao = new gl::VertexArray();
    vao->add_attrib(*vbo, 0, 3, 8, 0);
    vao->add_attrib(*vbo, 1, 3, 8, 3);
    vao->add_attrib(*vbo, 2, 2, 8, 6);
}

void quick3d::test::BoxRenderer::switch_blinn_phong_lighting(bool b) noexcept
{
    program->set_uniform("useBlinnPhong", static_cast<int>(b));
}

quick3d::test::BoxRenderer::BoxRenderer() noexcept(false)
	: gen(rd()), position_dis(-20.0f, 20.0f), rotation_dis(0.0, 1.0),
		ssbo_model(GL_SHADER_STORAGE_BUFFER, GL_DYNAMIC_DRAW, sizeof(ModelData))
{
    load_shader_program();
    load_texture();
    load_vbo_vao();
    setup_model_data(0);
}

quick3d::test::BoxRenderer::~BoxRenderer() noexcept
{
	delete program;
	delete vao;
	delete vbo;

	for (auto tex : textures)
		delete tex;
}

void quick3d::test::BoxRenderer::set_instance_count(int instance) noexcept
{
    for (std::size_t i = instance_count; i < instance; i++)
        setup_model_data(i);
	instance_count = instance;
}

void quick3d::test::BoxRenderer::on_tick(float delta_ms) noexcept(false)
{
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, ssbo_model.get_buffer_id());
    glDisable(GL_CULL_FACE);
    draw_vao();
    glEnable(GL_CULL_FACE);
}

void quick3d::test::BoxRenderer::on_tick(float delta_ms, gl::Program& program) noexcept(false)
{
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, ssbo_model.get_buffer_id());
    glDisable(GL_CULL_FACE);
    draw_vao(program);
    glEnable(GL_CULL_FACE);
}

void quick3d::test::BoxEntity::try_load_renderer() noexcept(false)
{
    if (!ren)
        ren = std::make_shared<BoxRenderer>();
}

void quick3d::test::BoxEntity::set_instance_count(int instance) noexcept
{
    ren->set_instance_count(instance);
}

void quick3d::test::BoxEntity::switch_blinn_phong_lighting(bool b) noexcept
{
    ren->switch_blinn_phong_lighting(b);
}

void quick3d::test::BoxEntity::on_tick(float delta_ms) noexcept(false)
{
    ren->rotate_model(delta_ms);
}

void quick3d::test::BoxEntity::on_draw(float delta_ms) noexcept(false)
{
    ren->on_tick(delta_ms);
}

void quick3d::test::BoxEntity::on_darw_with_shader(float delta_ms, gl::Program& program) noexcept(false)
{
    ren->on_tick(delta_ms, program);
}

quick3d::test::BoxEntity::BoxEntity(core::EntityManager& manager) noexcept(false)
    : Entity(manager)
{
    try_load_renderer();
}

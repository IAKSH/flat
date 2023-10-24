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
        auto scale{ glm::scale(glm::mat4(1.0f), glm::vec3(0.0005f, 0.0005f, 0.0005f)) };
        ptr->model[index] = glm::translate(scale, glm::vec3(position_dis(gen), position_dis(gen), position_dis(gen)));
    });

    model_rotate_attribs[index].rotate_axis = glm::vec3(rotation_dis(gen), rotation_dis(gen), rotation_dis(gen));
    model_rotate_attribs[index].rotate_speed = static_cast<float>(rotation_dis(gen));
}

void quick3d::test::BoxRenderer::rotate_model() noexcept
{
    ssbo_model.dma_do([&](void* data)
    {
        auto ptr{ reinterpret_cast<ModelData*>(data) };
        for (std::size_t i = 0; i < instance_count; i++)
        {
            float& rotate_speed{ model_rotate_attribs[i].rotate_speed };
            glm::vec3& rotate_axis{ model_rotate_attribs[i].rotate_axis };
            ptr->model[i] = glm::rotate(ptr->model[i], static_cast<float>(glfwGetTime() * rotate_speed) / 1000.0f, rotate_axis);
        }
    });
}

void quick3d::test::BoxRenderer::load_shader_program() noexcept(false)
{
    program = new quick3d::gl::Program(
        quick3d::gl::GLSLReader(std::format("{}/{}", GLSL_FOLDER, "box_vs.glsl")).get_glsl(),
        quick3d::gl::GLSLReader(std::format("{}/{}", GLSL_FOLDER, "box_fs.glsl")).get_glsl()
    );
    program->bind_uniform_block("CameraMatrix", 0);
    program->bind_uniform_block("PhoneDirectLighting", 2);

    program->set_uniform("material.diffuse", 0);
    program->set_uniform("material.specular", 1);
    program->set_uniform("material.shininess", 32.0f);

    // 也许不应该放在这里
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 4, ssbo_model.get_buffer_id());
}

void quick3d::test::BoxRenderer::load_texture() noexcept(false)
{
    textures.push_back(new gl::Texture(GL_RGBA, gl::Image(std::format("{}/{}", IMAGE_FOLDER, "container2.png"))));
    textures.push_back(new gl::Texture(GL_RGBA, gl::Image(std::format("{}/{}", IMAGE_FOLDER, "container2_specular.png"))));
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

quick3d::test::BoxRenderer::BoxRenderer() noexcept(false)
	: gen(rd()), position_dis(-10.0f, 10.0f), rotation_dis(0.0, 1.0),
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
    rotate_model();
    glDisable(GL_CULL_FACE);
    draw_vao();
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

void quick3d::test::BoxEntity::on_tick(float delta_ms) noexcept(false)
{
    ren->on_tick(delta_ms);
}

quick3d::test::BoxEntity::BoxEntity(core::EntityManager& manager) noexcept(false)
    : Entity(manager)
{
    try_load_renderer();
}

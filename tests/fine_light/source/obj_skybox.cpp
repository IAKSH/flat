#include <array>
#include <format>
#include <quick_gl/image.hpp>
#include <fine_light/obj_skybox.hpp>

static constexpr std::string_view GLSL_FOLDER = "../../../../../tests/fine_light/glsl";
static constexpr std::string_view IMAGE_FOLDER = "../../../../../tests/fine_light/image";

static constexpr std::array<float,108> skybox_vertices
{
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

constexpr std::string_view skybox_vs_glsl{
R"(
#version 330 core
layout (location = 0) in vec3 aPos;
out vec3 texCoord;
uniform mat4 projection;
uniform mat4 view;
void main()
{
    texCoord = aPos;
    gl_Position = projection * view * vec4(aPos,1.0);
}
)"};

constexpr std::string_view skybox_fs_glsl{
R"(
#version 330 core
out vec4 fragColor;
in vec3 texCoord;
uniform samplerCube skybox_cubemap;
void main()
{
    fragColor = vec4(0.1f,0.1f,0.1f,1.0f) * texture(skybox_cubemap,texCoord);
}
)"};

static constexpr std::array<std::string_view, 6> skybox_texture_names
{
    "right.jpg",
    "left.jpg",
    "top.jpg",
    "bottom.jpg",
    "front.jpg",
    "back.jpg"
};

quick3d::test::fine_light::Skybox::Skybox() noexcept(false)
{
    on_load();
    on_create();
}

quick3d::test::fine_light::Skybox::~Skybox() noexcept(false)
{
    on_destroy();
}

void quick3d::test::fine_light::Skybox::try_load_program(std::string_view vs,std::string_view fs) noexcept(false)
{
    if(!program)
        program = std::make_shared<gl::Program>(vs,fs);
}

void quick3d::test::fine_light::Skybox::try_setup_vao() noexcept
{
    if(!vbo)
        vbo = std::make_unique<gl::VBO>(skybox_vertices);
    if(!vao)
    {
        vao = std::make_unique<gl::VAO>(*vbo);
        vao->enable_attrib(0,3,3,0);
    }
}

void quick3d::test::fine_light::Skybox::try_load_cubemap(std::string_view folder,
    const std::array<std::string_view, 6>& names,GLenum format,uint32_t w,uint32_t h) noexcept(false)
{
    if(!cubemap)
    {
        cubemap = std::make_shared<gl::CubeMap>(format,w,h);

        for(int i = 0;i < 6;i++)
        cubemap->generate_texture(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
            gl::Image(std::format("{}/{}",folder,names[i]),false));
    }
}

void quick3d::test::fine_light::Skybox::on_tick(double delta_time) noexcept(false)
{
}

void quick3d::test::fine_light::Skybox::on_draw(const gl::FPSCamera& camera) noexcept(false)
{
    bool depth_test_enabled;
    if(depth_test_enabled = glIsEnabled(GL_DEPTH_TEST);depth_test_enabled)
        glDisable(GL_DEPTH_TEST);

    program->set_uniform("projection", camera.get_projection_matrix());
    program->set_uniform("view", glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f) + camera.get_front_vec(), camera.get_up_vec()));
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap->get_cubemap_id());
    vao->draw(*program, GL_TRIANGLES, 0, 36);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    if(depth_test_enabled)
        glEnable(GL_DEPTH_TEST);
}

void quick3d::test::fine_light::Skybox::on_create() noexcept(false)
{
}

void quick3d::test::fine_light::Skybox::on_destroy() noexcept(false)
{
}

void quick3d::test::fine_light::Skybox::on_load() noexcept(false)
{
    try_load_program(skybox_vs_glsl,skybox_fs_glsl);
    try_load_cubemap(IMAGE_FOLDER,skybox_texture_names,GL_RGBA,2048,2048);
    try_setup_vao();
}

void quick3d::test::fine_light::Skybox::on_unload() noexcept(false)
{
}
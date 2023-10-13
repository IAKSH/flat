#include <array>
#include <random>
#include <quick_gl/image.hpp>
#include <fine_light/obj_container.hpp>

static constexpr std::array<float, 288> container_vertices
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

quick3d::test::fine_light::Container::Container(std::string_view vs,std::string_view fs,
            std::string_view diffuse_tex_folder,std::string_view specular_tex_folder,GLenum color_format) noexcept(false)
{
    try_load_program(vs,fs);
    try_load_texture(diffuse_tex_folder,specular_tex_folder,color_format);
    try_setup_vao();
    on_create();
}

void quick3d::test::fine_light::Container::try_load_program(std::string_view vs,std::string_view fs) noexcept(false)
{
    if(!program)
        program = std::make_shared<gl::Program>(vs,fs);
}

void quick3d::test::fine_light::Container::try_load_texture(std::string_view diffuse_tex_folder,
    std::string_view specular_tex_folder, GLenum color_format) noexcept(false)
{
    if(!texture_diffuse)
        texture_diffuse = std::make_shared<gl::Texture>(color_format,
            gl::Image(std::format("{}/{}",diffuse_tex_folder,"container2.png")));
    if(!texture_specular)
        texture_specular = std::make_shared<gl::Texture>(color_format,
            gl::Image(std::format("{}/{}",specular_tex_folder,"container2_specular.png")));
}

void quick3d::test::fine_light::Container::try_setup_vao() noexcept
{
    if(!vbo)
        vbo = std::make_shared<gl::VBO>(container_vertices);
    if(!vao)
    {
        vao = std::make_shared<gl::VAO>(*vbo);
        vao->enable_attrib(0,3,8,0);
	    vao->enable_attrib(1,3,8,3);
	    vao->enable_attrib(2,2,8,6);
    }
}

void quick3d::test::fine_light::Container::on_tick(double delta_time) noexcept(false)
{
}

void quick3d::test::fine_light::Container::on_draw(const gl::FPSCamera& camera) noexcept(false)
{
    program->set_uniform("view", camera.get_view_matrix());
	program->set_uniform("projection", camera.get_projection_matrix());
	program->set_uniform("model",
        glm::translate(glm::mat4(1.0f), position) *
        glm::rotate(glm::mat4(1.0f),static_cast<float>(glfwGetTime() * rotate_speed),rotate_axis)        
        );
	program->set_uniform("viewPos", camera.get_position());
	program->set_uniform("material.diffuse", 0);
	program->set_uniform("material.specular", 1);
	program->set_uniform("material.shininess", 32.0f);
	program->set_uniform("light.ambient", glm::vec3(0.6f, 0.6f, 0.6f));
	program->set_uniform("light.diffuse", glm::vec3(1.0f,1.0f,1.0f));
	program->set_uniform("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
	program->set_uniform("light.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,texture_diffuse->get_tex_id());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D,texture_specular->get_tex_id());
	vao->draw(*program, GL_TRIANGLES, 0, 36);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D,0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,0);
}

void quick3d::test::fine_light::Container::on_create() noexcept(false)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> position_dis(-50.0, 50.0);
    std::uniform_real_distribution<double> rotation_dis(0.0, 1.0);

    position = glm::vec3(position_dis(gen),position_dis(gen),position_dis(gen));
    rotate_axis = glm::vec3(rotation_dis(gen),rotation_dis(gen),rotation_dis(gen));
    rotate_speed = static_cast<float>(rotation_dis(gen));
}

void quick3d::test::fine_light::Container::on_destroy() noexcept(false)
{
}

void quick3d::test::fine_light::Container::on_load() noexcept(false)
{
}

void quick3d::test::fine_light::Container::on_unload() noexcept(false)
{
}
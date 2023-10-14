#include <array>
#include <random>
#include <thread>
#include <quick_gl/image.hpp>
#include <fine_light/obj_container.hpp>

static constexpr std::string_view GLSL_FOLDER = "../../../../../tests/fine_light/glsl";
static constexpr std::string_view IMAGE_FOLDER = "../../../../../tests/fine_light/image";

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

quick3d::test::fine_light::Container::Container() noexcept(false)
{
    on_load();
    on_create();
}

quick3d::test::fine_light::Container::~Container() noexcept(false)
{
    on_destroy();
}

void quick3d::test::fine_light::Container::try_load_program(std::string_view vs,std::string_view fs) noexcept(false)
{
    if(!program)
    {
        program = std::make_shared<gl::Program>(vs,fs);

	    program->set_uniform("material.diffuse", 0);
	    program->set_uniform("material.specular", 1);
	    program->set_uniform("material.shininess", 32.0f);
	    program->set_uniform("directLight.ambient", glm::vec3(0.05f, 0.05f, 0.05f));
	    program->set_uniform("directLight.diffuse", glm::vec3(0.0f,0.0f,1.0f));
	    program->set_uniform("directLight.specular", glm::vec3(0.5f,0.5f,0.5f));
	    program->set_uniform("directLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
        program->set_uniform("pointLight.ambient", glm::vec3(0.05f, 0.05f, 0.05f));
        program->set_uniform("pointLight.diffuse", glm::vec3(0.6f, 1.0f, 0.6f));
        program->set_uniform("pointLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        program->set_uniform("pointLight.constant", 1.0f);
        program->set_uniform("pointLight.linear", 0.045f);
        program->set_uniform("pointLight.quadratic", 0.0075f);
        program->set_uniform("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
        program->set_uniform("spotLight.outerCutOff", glm::cos(glm::radians(17.5f)));
        program->set_uniform("spotLight.ambient", glm::vec3(0.05f, 0.05f, 0.05f));
        program->set_uniform("spotLight.diffuse", glm::vec3(1.0f, 0.0f, 0.0f));
        program->set_uniform("spotLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        program->set_uniform("spotLight.constant", 1.0f);
        program->set_uniform("spotLight.linear", 0.007f);
        program->set_uniform("spotLight.quadratic", 0.0002f);

        for(int i = 0;i < 250;i++)
        {
            program->set_uniform(std::format("pointLights[{}].ambient",i), glm::vec3(0.1f,0.1f,0.1f));
            program->set_uniform(std::format("pointLights[{}].specular",i), glm::vec3(1.0f,1.1f,1.1f));
            program->set_uniform(std::format("pointLights[{}].constant",i), 1.0f);
            program->set_uniform(std::format("pointLights[{}].linear",i), 0.22f);
            program->set_uniform(std::format("pointLights[{}].quadratic",i), 0.20f);
        }
    }
}

void quick3d::test::fine_light::Container::try_load_texture(std::string_view diffuse_tex_path,
    std::string_view specular_tex_path, GLenum color_format) noexcept(false)
{
    if(!texture_diffuse)
        texture_diffuse = std::make_shared<gl::Texture>(color_format,gl::Image(diffuse_tex_path));
    if(!texture_specular)
        texture_specular = std::make_shared<gl::Texture>(color_format,gl::Image(specular_tex_path));
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
    program->set_uniform("pointLight.position", camera.get_position());
    program->set_uniform("spotLight.position", camera.get_position());
    program->set_uniform("spotLight.direction", camera.get_front_vec());

    // too slow!
    for(int i = 0;i < light_balls.size();i++)
    {
        program->set_uniform(std::format("pointLights[{}].position",i),light_balls[i]->get_position());
        program->set_uniform(std::format("pointLights[{}].diffuse",i),light_balls[i]->get_light_color());
    }

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
    std::uniform_real_distribution<double> position_dis(-15.0, 15.0);
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
    try_load_program(
        gl::GLSLReader(std::format("{}/{}",GLSL_FOLDER,"container_direct_light_vs.glsl")).get_glsl(),
        gl::GLSLReader(std::format("{}/{}",GLSL_FOLDER,"container_direct_light_fs.glsl")).get_glsl()
    );
    try_load_texture(
        std::format("{}/{}",IMAGE_FOLDER,"container2.png"),
        std::format("{}/{}",IMAGE_FOLDER,"container2_specular.png"),
        GL_RGBA
    );
    try_setup_vao();
}

void quick3d::test::fine_light::Container::on_unload() noexcept(false)
{
}

void quick3d::test::fine_light::Container::add_light_ball(LightBall* light_ball) noexcept
{
    light_balls.push_back(light_ball);
}
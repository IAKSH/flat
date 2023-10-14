#include <random>
#include <fine_light/obj_light_ball.hpp>

static constexpr std::string_view GLSL_FOLDER = "../../../../../tests/fine_light/glsl";
static constexpr std::string_view MODEL_FOLDER = "../../../../../tests/fine_light/model";

quick3d::test::fine_light::LightBall::LightBall() noexcept(false)
{
    on_load();
    on_create();
}

quick3d::test::fine_light::LightBall::~LightBall() noexcept(false)
{
    on_destroy();
}

void quick3d::test::fine_light::LightBall::try_load_program(std::string_view vs,std::string_view fs) noexcept(false)
{
    if(!program)
        program = std::make_shared<gl::Program>(vs,fs);
}


void quick3d::test::fine_light::LightBall::try_load_model(std::string_view path) noexcept(false)
{
    if(!model)
        model = std::make_shared<gl::Model>(path);
}

void quick3d::test::fine_light::LightBall::on_create() noexcept(false)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> position_dis(-25.0, 25.0);
    std::uniform_real_distribution<double> light_color_dis(0.0, 1.0);

    position = glm::vec3(position_dis(gen),position_dis(gen),position_dis(gen));
    light_color = glm::vec3(light_color_dis(gen),light_color_dis(gen),light_color_dis(gen));
}

void quick3d::test::fine_light::LightBall::on_destroy() noexcept(false)
{
}

void quick3d::test::fine_light::LightBall::on_tick(double delta_time) noexcept(false)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<double> dis(-1.0f, 1.0f);

    // update move direction
    move_direction += 0.01f * glm::vec3(dis(gen),dis(gen),dis(gen));
    move_direction = glm::normalize(move_direction);

    // move
    position += 0.01f * move_direction;
}

void quick3d::test::fine_light::LightBall::on_draw(const gl::FPSCamera& camera) noexcept(false)
{
    program->set_uniform("view", camera.get_view_matrix());
	program->set_uniform("projection", camera.get_projection_matrix());
	program->set_uniform("model", glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f),glm::vec3(0.2f,0.2f,0.2f)));
    program->set_uniform("lightColor", light_color);
    model->draw_model(*program);
}

void quick3d::test::fine_light::LightBall::on_load() noexcept(false)
{
    try_load_program(
        gl::GLSLReader(std::format("{}/{}",GLSL_FOLDER,"light_ball_vs.glsl")).get_glsl(),
        gl::GLSLReader(std::format("{}/{}",GLSL_FOLDER,"light_ball_fs.glsl")).get_glsl()
    );
    try_load_model(std::format("{}/{}",MODEL_FOLDER,"ball/ball.obj"));
}

void quick3d::test::fine_light::LightBall::on_unload() noexcept(false)
{
}

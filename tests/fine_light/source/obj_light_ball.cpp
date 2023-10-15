#include <random>
#include <fine_light/obj_light_ball.hpp>

static constexpr std::string_view GLSL_FOLDER = "../../../../tests/fine_light/glsl";
static constexpr std::string_view MODEL_FOLDER = "../../../../tests/fine_light/model";

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

void quick3d::test::fine_light::LightBall::try_load_instance_vbo() noexcept
{
    if(!instance_vbo)
        instance_vbo = std::make_shared<gl::VBO>();
}

void quick3d::test::fine_light::LightBall::update_instance_vbo() noexcept
{
    instance_vbo->write_to_buffer(reinterpret_cast<float*>(datas.data()),sizeof(datas),GL_STREAM_DRAW);
    for(const auto& mesh : *(model->get_meshes()))
    {
        mesh->bind_instance_array(instance_vbo->get_buffer_id(),6,3,sizeof(Data),0,1);
        mesh->bind_instance_array(instance_vbo->get_buffer_id(),7,16,sizeof(glm::mat4),3 * sizeof(float),1);
    }
}

void quick3d::test::fine_light::LightBall::on_create() noexcept(false)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> position_dis(-25.0, 25.0);
    std::uniform_real_distribution<double> direction_dis(-1.0, 1.0);
    std::uniform_real_distribution<double> light_color_dis(-1.0, 1.0);

    for(auto& data : datas)
    {
        data.position = glm::vec3(position_dis(gen),position_dis(gen),position_dis(gen));
        data.move_direction = glm::vec3(direction_dis(gen),direction_dis(gen),direction_dis(gen));
        data.light_color = glm::vec3(light_color_dis(gen),light_color_dis(gen),light_color_dis(gen));
    }
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
    for(auto& data : datas)
    {
        data.move_direction += 0.1f * glm::vec3(dis(gen),dis(gen),dis(gen));
        data.move_direction = glm::normalize(data.move_direction);

        // move
        data.position += 0.05f * data.move_direction;

        int positive;
        positive = data.position.x > 0 ? 1 : -1;;
        if(abs(data.position.x) > 10.0f)
            data.position.x = positive * 10.f;

        positive = data.position.y > 0 ? 1 : -1;;
        if(abs(data.position.y) > 10.0f)
            data.position.y = positive * 10.0f;

        positive = data.position.z > 0 ? 1 : -1;;
        if(abs(data.position.z) > 10.0f)
            data.position.z = positive * 10.0f;
    }

    // update model matrix
    for(auto& data : datas)
        data.model = glm::translate(glm::mat4(1.0f),data.position) *
            glm::scale(glm::mat4(1.0f),glm::vec3(0.01f,0.01f,0.01f));
}

void quick3d::test::fine_light::LightBall::on_draw(const gl::FPSCamera& camera) noexcept(false)
{
    update_instance_vbo();

    program->set_uniform("view", camera.get_view_matrix());
	program->set_uniform("projection", camera.get_projection_matrix());

    model->draw_model(*program,INSTANCE_COUNT);
}

void quick3d::test::fine_light::LightBall::on_load() noexcept(false)
{
    try_load_program(
        gl::GLSLReader(std::format("{}/{}",GLSL_FOLDER,"light_ball_vs.glsl")).get_glsl(),
        gl::GLSLReader(std::format("{}/{}",GLSL_FOLDER,"light_ball_fs.glsl")).get_glsl()
    );
    try_load_model(std::format("{}/{}",MODEL_FOLDER,"ball/ball.obj"));
    try_load_instance_vbo();
}

void quick3d::test::fine_light::LightBall::on_unload() noexcept(false)
{
}
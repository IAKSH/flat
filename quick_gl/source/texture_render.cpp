#include <format>
#include <quick_gl/texture_render.hpp>

constexpr std::array<float, 20> rect_vertices
{
	1.0f, 1.0f, 0.0f, 1.0f, 1.0f,  // top right
	1.0f, -1.0f, 0.0f, 1.0f, 0.0f,  // bottom right
	-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,  // bottom left
	-1.0f, 1.0f, 0.0f, 0.0f, 1.0f   // top left
};

constexpr std::array<unsigned int, 6> rect_indices
{
	0, 1, 3,
	1, 2, 3
};

constexpr std::string_view vertex_shader_glsl
{
	R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

void main()
{
	gl_Position = vec4(aPos, 1.0);
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}
	)"
};

constexpr std::string_view fragment_shader_glsl
{
	R"(
#version 330 core

out vec4 FragColor;
in vec2 TexCoord;

uniform sampler2D texture;

void main()
{
	FragColor = texture(texture, TexCoord);
}
	)"
};

quick3d::gl::TextureRenderer::TextureRenderer(GLint w,GLint h) noexcept(false)
	: width(w),height(h)
{
	setup_program();
	setup_vao();
	setup_fbo_without_texture();
}

void quick3d::gl::TextureRenderer::setup_program() noexcept(false)
{
    program = std::make_unique<Program>(vertex_shader_glsl, fragment_shader_glsl);
}

void quick3d::gl::TextureRenderer::setup_vao() noexcept
{
	vbo = std::make_unique<VBO>(rect_vertices);
	ebo = std::make_unique<EBO>(rect_indices);
	vao = std::make_unique<VAO>(*vbo, *ebo);

	vao->enable_attrib(0, 3, 5, 0);
	vao->enable_attrib(1, 2, 5, 3);

	glUseProgram(program->get_program_id());
	program->set_uniform("texture", 0);
	glActiveTexture(GL_TEXTURE0);
	glUseProgram(0);
}

void quick3d::gl::TextureRenderer::setup_fbo_without_texture() noexcept(false)
{
	fbo = std::make_unique<Framebuffer>(width, height);
}

void quick3d::gl::TextureRenderer::draw_to_texture(const Texture& output_texture, unsigned char* img_data, GLint img_channels, GLint img_width, GLint img_height) noexcept(false)
{
	draw_to_texture(output_texture.get_tex_id(), img_data, img_channels, img_width, img_height);
}

void quick3d::gl::TextureRenderer::draw_to_texture(GLuint output_texture_id, unsigned char* img_data, GLint img_channels, GLint img_width, GLint img_height) noexcept(false)
{
    // prepare texture
    GLuint input_texture_id;
    glGenTextures(1, &input_texture_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, input_texture_id);

    GLenum img_format;
    switch (img_channels)
    {
    case 1: img_format = GL_R;      break;
    case 3: img_format = GL_RGB;    break;
    case 4: img_format = GL_RGBA;   break;
    default:
        throw std::runtime_error(std::format("draw_to_texture() unsupported channel count (img_channels={})", img_channels));
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img_width, img_height, 0, img_format, GL_UNSIGNED_BYTE, img_data);
    glGenerateMipmap(GL_TEXTURE_2D);

    // bind output_texture_to fbo
    fbo->bind_texture_to_fbo(GL_TEXTURE_2D, output_texture_id);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo->get_fbo_id());
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        throw std::runtime_error("framebuffer not complete");

    // set viewport
    GLint former_viewport_data[4];
    glGetIntegerv(GL_VIEWPORT, former_viewport_data);
    glViewport(0, 0, width, height);

    // draw
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    //glBindTexture(GL_TEXTURE_2D, input_texture_id);
    //vao->draw(*program, GL_TRIANGLES, 0, 6);
    glUseProgram(program->get_program_id());
    glBindVertexArray(vao->get_vao_id());
    glBindBuffer(GL_ARRAY_BUFFER, vbo->get_buffer_id());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo->get_buffer_id());
    glBindTexture(GL_TEXTURE_2D, input_texture_id);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // reset viewport
    glViewport(former_viewport_data[0], former_viewport_data[1], former_viewport_data[2], former_viewport_data[3]);

    // clean up ogl state
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    // delete input texture
    glDeleteTextures(1, &input_texture_id);
}

void quick3d::gl::TextureRenderer::draw_to_cubemap(const CubeMap& output_cubemap, GLenum location, unsigned char* img_data, GLint img_channels, GLint img_width, GLint img_height) noexcept(false)
{
	draw_to_cubemap(output_cubemap.get_cubemap_id(), location, img_data, img_channels, img_width, img_height);
}

void quick3d::gl::TextureRenderer::draw_to_cubemap(GLuint output_cubemap_id, GLenum location, unsigned char* img_data, GLint img_channels, GLint img_width, GLint img_height) noexcept(false)
{
    // prepare texture
    GLuint input_texture_id;
    glGenTextures(1, &input_texture_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, input_texture_id);

    GLenum img_format;
    switch (img_channels)
    {
    case 1: img_format = GL_R;      break;
    case 3: img_format = GL_RGB;    break;
    case 4: img_format = GL_RGBA;   break;
    default:
        throw std::runtime_error(std::format("draw_to_texture() unsupported channel count (img_channels={})", img_channels));
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img_width, img_height, 0, img_format, GL_UNSIGNED_BYTE, img_data);
    glGenerateMipmap(GL_TEXTURE_2D);

    // bind output_texture_to fbo
    fbo->bind_texture_to_fbo(location, output_cubemap_id);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo->get_fbo_id());
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        throw std::runtime_error("framebuffer not complete");

    // set viewport
    GLint former_viewport_data[4];
    glGetIntegerv(GL_VIEWPORT, former_viewport_data);
    glViewport(0, 0, width, height);

    // draw
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    //glBindTexture(GL_TEXTURE_2D, input_texture_id);
    //vao->draw(*program, GL_TRIANGLES, 0, 6);
    glUseProgram(program->get_program_id());
    glBindVertexArray(vao->get_vao_id());
    glBindBuffer(GL_ARRAY_BUFFER, vbo->get_buffer_id());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo->get_buffer_id());
    glBindTexture(GL_TEXTURE_2D, input_texture_id);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // reset viewport
    glViewport(former_viewport_data[0], former_viewport_data[1], former_viewport_data[2], former_viewport_data[3]);

    // clean up ogl state
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    // delete input texture
    glDeleteTextures(1, &input_texture_id);
}
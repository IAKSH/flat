#pragma once

#include "../core/layer.hpp"
#include "../utils/shader.hpp"
#include "../utils/camera.hpp"
#include "../utils/font.hpp"
#include "../utils/vao.hpp"
#include "../flat/text_renderer.hpp"

namespace Flat
{
    using ni::core::Event;
    using ni::utils::Shader;
    using ni::utils::Camera2D;
    using ni::utils::Font;
    using ni::utils::Texture;
    using ni::utils::VertexArrayObj;
    using ni::utils::GLBufferType;
    using ni::flat::TextRenderer;

    inline static const char* vshader =
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "layout (location = 1) in vec4 aColor;\n"
        "layout (location = 2) in vec2 aTexCoord;\n"
        "out vec2 aTexCoordOut;\n"
        "out vec4 aColorOut;\n"
        "uniform mat4 transform;\n"
        "uniform mat4 camTrans;\n"
        "void main()\n"
        "{\n"
        "    gl_Position =  camTrans * transform * vec4(aPos, 1.0f);\n"
        "    aTexCoordOut = vec2(aTexCoord.x, 1.0 - aTexCoord.y);\n"
        "    aColorOut = aColor;\n"
        "}\0";

    inline static const char* fshader =
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "in vec2 aTexCoordOut;\n"
        "in vec4 aColorOut;\n"
        "uniform sampler2D texture0;\n"
        "void main()\n"
        "{\n"
        "    vec4 texColor = texture(texture0,aTexCoordOut);\n"
        "    FragColor = texColor * aColorOut;\n"
        "}\n\0";

    inline static std::array<float,36> vertices
    {
		1.0f,  1.0f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  // top right
		1.0f,  -1.0f, 0.0f,1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,  // bottom right
		-1.0f, -1.0f, 0.0f,1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,  // bottom left
		-1.0f, 1.0f,  0.0f,1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f   // top left
	};

	inline static std::array<unsigned int, 6> indices
    {
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};

    class MenuLayer : public ni::core::Layer
    {
    private:
        Shader shader;
        TextRenderer texRen;
        Camera2D cam;
        Texture background;
        Texture selectIcon;
        VertexArrayObj<ni::utils::GLBufferType::Static> vao;

    public:
        MenuLayer();
        ~MenuLayer() = default;

        virtual void onAttach() override;
        virtual void onDetach() override;
        virtual void onUpdate() override;
        virtual void onRender() override;
        virtual void onEvent(Event& e) override;
    };
}
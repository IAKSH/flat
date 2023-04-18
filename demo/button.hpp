#pragma once
#include "../utils/gameobj.hpp"
#include "../utils/texture.hpp"
#include "../utils/rectangle_vao.hpp"
#include "../flat/text_renderer.hpp"
#include "../flat/shader.hpp"
#include <functional>
#include <string>
#include <string_view>

namespace Flat
{
    using ni::utils::VertexBuffer;
    using ni::utils::GLBufferType;
    using ni::utils::Texture;
    using ni::utils::Font;
    using ni::utils::Camera2D;
    using ni::flat::Shader;
    using ni::flat::UniformArg;
    using ni::flat::TextRenderer;

    class Button : public ni::utils::GameObject
    {
    private:
        float width,height;
        bool actived;
        Shader& shader;
        TextRenderer& ren;
        Camera2D& cam;
        Font& font;
        VertexBuffer<GLBufferType::Static> vao;
        std::function<void(void)> callback;
        std::u32string str;
        inline static Texture blackTex;

    public:
        Button(const float& w,const float h,Shader& shader,TextRenderer& texRen,Camera2D& cam,Font& font,std::u32string_view str,std::function<void(void)> callback);
        ~Button() = default;
        virtual void onAttach() override;
        virtual void onDetach() override;
        virtual void onUpdate() override;
        virtual void onRender() override;
        virtual void onEvent(ni::core::Event& e) override;

        void active() {actived = true;}
        void inactive() {actived = false;}
    };
}
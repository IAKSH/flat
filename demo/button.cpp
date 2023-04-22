#include "button.hpp"
#include "../core/event_keyboard.hpp"
#include <string_view>

Flat::Button::Button(const float& w,const float h,ShaderProgram& shader,TextRenderer& texRen,Camera2D& cam,Font& font,std::u32string_view str,std::function<void(void)> callback)
    : width(w),height(h),shader(shader),ren(texRen),font(font),cam(cam),callback(callback)
{
    text.set(str);
}

void Flat::Button::onAttach()
{
    for(int i = 0;i < 4;i++)
        vao.set(i,ni::utils::Color(03.0f,0.3f,0.1f,0.55f));

    if(!blackTex.getTextureID())
        blackTex.loadFromFile("images/black.png");

    text.set(Color(1.0f,1.0f,1.0f,0.5f));
}

void Flat::Button::onDetach()
{

}

void Flat::Button::onUpdate()
{
    text.set(Point(getPosX() - width,getPosY() - height / 4.0f,getPosZ() + 0.01f));
}

void Flat::Button::onRender()
{
    shader.use();

    glm::mat4 trans(1.0f);
	trans *= glm::translate(glm::mat4(1.0f),glm::vec3(getPosX() - 400.0f,getPosY() - 300.0f,getPosZ()));
	trans *= glm::scale(glm::mat4(1.0f),glm::vec3(width,height,0.9f));
	trans *= glm::rotate(glm::mat4(1.0f),0.0f, glm::vec3(0.0f,0.0f,1.0f));
    shader.setUniform("camTrans",cam.getTranslateMatrix());
    shader.setUniform("transform",trans);

    glBindTexture(GL_TEXTURE_2D,blackTex.getTextureID());
    glBindVertexArray(vao.getVAO());
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    text.onRender();
}

void Flat::Button::onEvent(ni::core::Event& e)
{
    if(actived)
    {
        if(e.getType() == ni::core::EventType::KeyPress
            && static_cast<ni::core::KeyPressEvent&>(e).getKeyCode() == ni::core::KeyCode::Z)
            callback();
    }
}

Flat::BlinkingButton::BlinkingButton(const float& w,const float h,ShaderProgram& shader,TextRenderer& texRen,Camera2D& cam,Font& font,const MilliSeconds& interval,std::u32string_view str,std::function<void(void)> callback)
    : Button(w,h,shader,texRen,cam,font,str,callback),interval(interval)
{
}

void Flat::BlinkingButton::onUpdate()
{
    text.set(Point(getPosX() - width,getPosY() - height / 2.0f,getPosZ() + 0.01f));
    if(recoder.getSpanAsMilliSeconds() >= interval)
    {
        Color& color = text.get<Color&>();
        auto& red = static_cast<ni::utils::Red&>(color);
        auto& green = static_cast<ni::utils::Green&>(color);
        auto& blue = static_cast<ni::utils::Blue&>(color);
        auto& aplha = static_cast<ni::utils::Alpha&>(color);

        aplha = aplha == 0.0f ? 0.55f:0.0f;
        recoder.update();
    }
}

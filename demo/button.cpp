#include "button.hpp"
#include "../core/event_keyboard.hpp"
#include <array>
#include <string_view>

Flat::Button::Button(const float& w,const float h,ShaderProgram& shader,TextRenderer& texRen,Camera2D& cam,Font& font,std::u32string_view str,std::function<void(void)> callback)
    : width(w),height(h),shader(shader),ren(texRen),font(font),cam(cam),callback(callback)
{
    text.set(str);
}

void Flat::Button::onAttach()
{
    for(int i = 0;i < 4;i++)
        vao.setColor(i,std::array<float,4>{03.0f,0.3f,0.1f,0.55f});

    if(!blackTex)
    {
        ni::utils::Image img("images/black.png");
        blackTex = std::make_unique<Texture>(img.getData(),0,0,img.getWidth(),img.getHeight());
    }

    text.set(Color(1.0f,1.0f,1.0f,0.5f));
}

void Flat::Button::onDetach()
{

}

void Flat::Button::onUpdate()
{
    text.set(Point(getPositionX() - width,getPositionY() - height / 4.0f,getPositionZ() + 0.01f));
}

void Flat::Button::onRender()
{
    shader.use();

    glm::mat4 trans(1.0f);
	trans *= glm::translate(glm::mat4(1.0f),glm::vec3(getPositionX() - 400.0f,getPositionY() - 300.0f,getPositionZ()));
	trans *= glm::scale(glm::mat4(1.0f),glm::vec3(width,height,0.9f));
	trans *= glm::rotate(glm::mat4(1.0f),0.0f, glm::vec3(0.0f,0.0f,1.0f));
    shader.setUniform("camTrans",cam.getTranslateMatrix());
    shader.setUniform("transform",trans);

    glBindTexture(GL_TEXTURE_2D,blackTex->getTextureID());
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
    text.set(Point(getPositionX() - width,getPositionY() - height / 2.0f,getPositionZ() + 0.01f));
    if(recoder.getSpanAsMilliSeconds() >= interval)
    {
        Color& color = text.get<Color&>();
        color.getAlpha() == 0.0f ? color.setAlpha(0.5f) : color.setAlpha(0.0f);

        recoder.update();
    }
}

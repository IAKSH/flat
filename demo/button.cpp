#include "button.hpp"

#include "../core/event_keyboard.hpp"
#include <string_view>

Flat::Button::Button(const float& w,const float h,Shader& shader,TextRenderer& texRen,Camera2D& cam,Font& font,std::u32string_view str,std::function<void(void)> callback)
    : width(w),height(h),shader(shader),ren(texRen),font(font),str(str),cam(cam),callback(callback)
{
}

void Flat::Button::onAttach()
{
    for(int i = 0;i < 4;i++)
        vao.set(i,ni::utils::Color(0.0f,0.0f,0.0f,0.1f));

    if(!blackTex.getTextureID())
        blackTex.loadFromFile("images/black.png");
}

void Flat::Button::onDetach()
{

}

void Flat::Button::onUpdate()
{
    
}

void Flat::Button::onRender()
{
    glUseProgram(shader);

    glm::mat4 trans(1.0f);
	trans *= glm::translate(glm::mat4(1.0f),glm::vec3(getPosX(),getPosY(),getPosZ()));
	trans *= glm::scale(glm::mat4(1.0f),glm::vec3(width,height,1.0f));
	trans *= glm::rotate(glm::mat4(1.0f),0.0f, glm::vec3(0.0f,0.0f,1.0f));
    shader["transform"] = UniformArg(trans);

    glBindTexture(GL_TEXTURE_2D,blackTex.getTextureID());
    glBindVertexArray(vao.getVAO());
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    ren.drawText(ni::utils::Color(1.0f,1.0f,1.0f,1.0f),ni::utils::Point(getPosX(),getPosY(),getPosZ() + 0.01f),ni::utils::Scale(1.0f),&font,&cam,std::u32string_view(str));
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

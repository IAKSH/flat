#include "../renderer.hpp"

#include <cstdint>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace glcore
{
    class Texture : public dggen::Texture {
    private:
        const uint32_t textureId;

    public:
        Texture(uint32_t id) : textureId(id){};
        virtual ~Texture() override;
        uint32_t const getTextureId() { return textureId; }
    };

    class Font : public dggen::Font {
    private:
        // TODO:...

    public:
        Font();
        virtual ~Font() override;
        virtual dggen::Font& operator()(const dggen::Font& font) override;
    };

    class Renderer : public dggen::Renderer<Renderer> {
    private:
        uint32_t vao,vbo,ebo,shaderProgram;
        void makeDrawMeta();
        void makeShaderProgram(uint32_t vshader,uint32_t fshader);
        void checkVertexShader(uint32_t vshader);
        void checkFragmentShader(uint32_t fshader);
        uint32_t compileVertexShader();
        uint32_t compileFragmentShader();
        void writeTransformUniform(const glm::mat4& trans);
        void writeColorUniform(const glm::vec4 color);
        void writeTextCoordsUniform(const glm::vec2 coord1,const glm::vec2 coord2,const glm::vec2 coord3,const glm::vec2 coord4);

    public:
        Renderer();
        ~Renderer();
        void imp_setColor(dggen::Color&& color);
        void imp_bindTexture(dggen::Texture&& texture);
        void imp_drawRectangle(dggen::Rectangle&& rectangle);
        void imp_drawText(dggen::Texture&& text);
        void imp_flush();
        const dggen::Texture& imp_genTexture(std::string_view path);
        const dggen::Font& imp_genFont(std::string_view path);
    };
}  // namespace glcore
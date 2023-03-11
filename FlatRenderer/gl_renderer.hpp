#include "renderer.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace flat::glcore
{
    class Rectangle : public flat::Rectangle
    {
    private:
        uint32_t vao,vbo,ebo;
        void releaseRectangle();

    public:
        Rectangle();
        ~Rectangle();
    };

    class Triangle : public flat::Triangle
    {
    private:
        uint32_t vao,vbo,ebo;
        void releaseRectangle();

    public:
        Triangle();
        ~Triangle();
    };

    class Shader
    {
    private:
        uint32_t shaderId;
        uint32_t compileVShader(std::string_view source);
        uint32_t compileFShader(std::string_view source);
        void checkVShader(uint32_t vshaderId);
        void checkFShader(uint32_t fshaderId);
        void linkShader(uint32_t vshaderId,uint32_t fshaderId);
        void releaseShader();

    public:
        Shader();
        ~Shader();
        void useShader();
        void compileShader(std::string_view vsource,std::string_view fsource);
        void writeUniformMat4(std::string_view uniform,const glm::mat4& mat);
    };

    class Texture : flat::Texture
    {
    private:
        uint32_t textureId;
        void releaseTexture();
        void checkTexture();

    public:
        Texture();
        virtual ~Texture() override;
        virtual void initTexture() override;
        virtual void loadTextureFromFile(std::string_view path) override;
        virtual uint32_t const getTextureId() override; 
    };

    class Renderer : public flat::Renderer
    {
    private:
        Shader universalShader;
        void initUniversalShader();

    public:
        Renderer();
        virtual ~Renderer() override;
        virtual void initRenderer() override;
        virtual void bindTexture(uint32_t texPortId,flat::Texture& texture) override;
        virtual void cleanScreen(const flat::RGBAColor& color) override;
        virtual void drawPixel(const flat::Pixel& pixel) override;
        virtual void drawRectangle(const flat::Rectangle& rectangle) override;
        virtual void drawTriangle(const flat::Triangle& triangle) override;
        virtual void makeupTriangle(flat::Triangle* triangle) override;
        virtual void makeupRectangle(flat::Rectangle* rectangle) override;
    };
}
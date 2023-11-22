#pragma once

#include <format>
#include <vector>
#include <memory>
#include <string>
#include <string_view>
#include <glad/gles2.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <quick_gl/texture.hpp>
#include <quick_gl/image.hpp>
#include <quick_gl/buffer.hpp>

namespace quick3d::gl
{
    // 用户不应该直接拿VAO绘图，应该使用Mesh
    // 从模型中加载的Mesh或是预制的基础Mesh
    // 但是为了扩展性，说不定以后还是有要在其他地方手搓VAO
    // 所以这个类就暂时不合并进Mesh了
    class VertexArray
    {
    private:
        GLuint vao_id;
        bool has_ebo;

        void create_vao() noexcept;
        void delete_vao() noexcept;

    public:
        VertexArray() noexcept;
        VertexArray(VertexArray&) = delete;
        ~VertexArray() noexcept;

        GLuint get_vao_id() const noexcept;
        void bind_ebo(GLuint ebo_id) noexcept;
        void draw(GLuint program_id, GLenum primitive, GLint first, GLsizei vertex_count, GLsizei instance = 0) noexcept;
        // TODO: 需要开放更多API，比如参数的具体类型，主要是确定VAO属性的大小，详见glVertexAttribPointer的参数列表
        // 也许可以用模板实现
        void add_attrib(GLenum buffer_target, uint32_t buffer_id,
            uint32_t index, uint32_t len, uint32_t vertex_len, uint32_t offset, bool normalized = false) noexcept(false);

        template <typename T>
        requires requires(T t)
        {
            {t.get_buffer_id()} -> std::same_as<GLuint>;
            {t.get_buffer_target()} -> std::same_as<GLenum>;
        }
        void bind_ebo(const T& t) noexcept(false)
        {
            if (t.get_buffer_target() != GL_ELEMENT_ARRAY_BUFFER)
                throw std::runtime_error("invalid buffer target for vao::bind_ebo()");
            bind_ebo(t.get_buffer_id());
        }

        template <typename T>
        requires requires(T t)
        {
            {t.get_buffer_id()} -> std::same_as<GLuint>;
            {t.get_buffer_target()} -> std::same_as<GLenum>;
        }
        void add_attrib(T& t, uint32_t index, uint32_t len, uint32_t vertex_len, uint32_t offset, bool normalized = false) noexcept(false)
        {
            add_attrib(t.get_buffer_target(), t.get_buffer_id(), index, len, vertex_len, offset, normalized);
        }

        template <typename T>
        requires requires(T t)
        {
            {t.get_program_id()} -> std::same_as<GLuint>;
        }
        void draw(const T& t, GLenum primitive, GLint first, GLsizei vertex_count, GLsizei instance = 0) noexcept
        {
            draw(t.get_program_id(), primitive, first, vertex_count, instance);
        }
    };

    inline static constexpr uint32_t MAX_BONE_INFLUENCE{ 4 };
    
    // TODO: 可能需要加入顶点颜色...
    struct MeshVertexPack
    {
        // 顶点坐标
        glm::vec3 position;
        // 法向量，主要用于计算光照
        glm::vec3 normal;
        // 纹理坐标映射
        glm::vec2 uv;
        // 切向量，主要用于法线贴图
        glm::vec3 tangent;
        // 副切向量，用于和切向量构成一个坐标系，主要用于法线贴图
        glm::vec3 bitangent;
        // 影响该节点的骨骼ID，用于骨骼动画
        int bone_ids[MAX_BONE_INFLUENCE];
        // 骨骼对该顶点的影响权重，用于骨骼动画
        float weights[MAX_BONE_INFLUENCE];
    };

    struct MeshTexturePack
    {
        std::unique_ptr<Texture> texture;
        std::string type;
        std::string path;
        MeshTexturePack(std::string_view file_name, std::string_view directory, std::string_view type) noexcept(false);
    };

    // TODO: 需要把预制Mesh变成预制Model
    // 目前这个Mesh是给Model用的，Mesh并没有textures的所有权，也不负责释放，textures是随Model释放的
    // 然而对于预制Mesh，目前是没有所在的Model的
    // 
    // 除此之外，还需要把操作textures的API移动到Model中，让Model负责textures的管理
    class Mesh
    {
    private:
        std::vector<MeshTexturePack*> textures;
        std::unique_ptr<Buffer> vbo;
        std::unique_ptr<Buffer> ebo;
        std::size_t indices_len;
        VertexArray vao;

        GLenum primitive_type;

        void setup_vao(std::vector<MeshVertexPack>& vertices,
            std::vector<unsigned int>& indices) noexcept;

    public:
        Mesh(std::vector<MeshTexturePack*>& textures,
            std::vector<MeshVertexPack>& vertices,
            std::vector<unsigned int>& indices,
            GLenum primivite_type = GL_TRIANGLES) noexcept;

        Mesh(Mesh&) = delete;
        ~Mesh() = default;

        VertexArray& get_vao() noexcept;
        Buffer& get_vbo() noexcept;
        Buffer& get_ebo() noexcept;
        std::vector<MeshTexturePack*>& get_textures() noexcept;
        void set_indices_size(std::size_t indices_len) noexcept;

        template <typename T>
        requires requires(T t)
        {
            {t.get_program_id()} -> std::same_as<GLuint>;
            {t.set_uniform(std::declval<std::string_view>(),
                std::declval<int>())} -> std::same_as<void>;
        }
        void draw_mesh(const T& t, GLenum primitive = GL_NONE, uint32_t instance = 0) noexcept
        {
            glUseProgram(t.get_program_id());

            unsigned int diffuse_nr = 1;
            unsigned int specular_nr = 1;
            unsigned int normal_nr = 1;
            unsigned int height_nr = 1;

            for(uint32_t i = 0;i < textures.size();i++)
            {
                glActiveTexture(GL_TEXTURE0 + i);

                std::string name = textures[i]->type;
                if(name == "texture_diffuse")
                    name += std::to_string(diffuse_nr++);
                else if(name == "texture_specular")
                    name += std::to_string(specular_nr++);
                else if(name == "texture_normal")
                    name += std::to_string(normal_nr++);
                else if(name == "texture_height")
                    name += std::to_string(height_nr++);

                glUniform1i(glGetUniformLocation(t.get_program_id(),name.data()), i);
                glBindTexture(GL_TEXTURE_2D,textures[i]->texture->get_tex_id());
            }

            if (primitive == GL_NONE)
                vao.draw(t, primitive_type, 0, static_cast<GLsizei>(indices_len), instance);
            else
                vao.draw(t, primitive, 0, static_cast<GLsizei>(indices_len), instance);

            for (int i = 0; i < textures.size(); i++)
            {
                glActiveTexture(GL_TEXTURE0 + i);
                glBindTexture(GL_TEXTURE_2D, 0);
            }

            glActiveTexture(GL_TEXTURE0);
            glUseProgram(0);
        }
    };

    // TODO: 考虑直接换到Model去
    // 那样的话，就只拿Model绘图了，无论什么，都是Model
    // 或者允许用户自己拿Mesh组Model
    // 有了更多的理由，见Mesh类上的TODO
    std::unique_ptr<Mesh> gen_square_mesh() noexcept;// 有bug，只画得出来一个三角形
    std::unique_ptr<Mesh> gen_round_mesh(int segments = 100) noexcept;
    std::unique_ptr<Mesh> gen_triangle_mesh() noexcept;
    std::unique_ptr<Mesh> gen_line_mesh() noexcept;
    std::unique_ptr<Mesh> gen_point_mesh() noexcept;
    std::unique_ptr<Mesh> gen_ball_mesh(int segments = 100, int stacks = 50) noexcept;
    std::unique_ptr<Mesh> gen_cube_mesh() noexcept;
}
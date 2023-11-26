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

// TODO: ���ļ�������Ҫ����model.hpp

namespace quick3d::gl
{
    // �û���Ӧ��ֱ����VAO��ͼ��Ӧ��ʹ��Mesh
    // ��ģ���м��ص�Mesh����Ԥ�ƵĻ���Mesh
    // ����Ϊ����չ�ԣ�˵�����Ժ�����Ҫ�������ط��ִ�VAO
    // ������������ʱ���ϲ���Mesh��
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
        // TODO: ��Ҫ���Ÿ���API����������ľ������ͣ���Ҫ��ȷ��VAO���ԵĴ�С�����glVertexAttribPointer�Ĳ����б�
        // Ҳ��������ģ��ʵ��
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
    
    // TODO: ������Ҫ���붥����ɫ...
    struct MeshVertexPack
    {
        // ��������
        glm::vec3 position;
        // ����������Ҫ���ڼ������
        glm::vec3 normal;
        // ��������ӳ��
        glm::vec2 uv;
        // ����������Ҫ���ڷ�����ͼ
        glm::vec3 tangent;
        // �������������ں�����������һ������ϵ����Ҫ���ڷ�����ͼ
        glm::vec3 bitangent;
        // Ӱ��ýڵ�Ĺ���ID�����ڹ�������
        int bone_ids[MAX_BONE_INFLUENCE];
        // �����Ըö����Ӱ��Ȩ�أ����ڹ�������
        float weights[MAX_BONE_INFLUENCE];
    };

    struct MeshTexturePack
    {
        std::unique_ptr<Texture> texture;
        std::string type;
        std::string path;
        MeshTexturePack(std::string_view file_name, std::string_view directory, std::string_view type) noexcept(false);
    };

    // TODO: ��Ҫ��Ԥ��Mesh���Ԥ��Model
    // Ŀǰ���Mesh�Ǹ�Model�õģ�Mesh��û��textures������Ȩ��Ҳ�������ͷţ�textures����Model�ͷŵ�
    // Ȼ������Ԥ��Mesh��Ŀǰ��û�����ڵ�Model��
    // 
    // ����֮�⣬����Ҫ�Ѳ���textures��API�ƶ���Model�У���Model����textures�Ĺ���
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

    // TODO: ����ֱ�ӻ���Modelȥ
    // �����Ļ�����ֻ��Model��ͼ�ˣ�����ʲô������Model
    // ���������û��Լ���Mesh��Model
    // ���˸�������ɣ���Mesh���ϵ�TODO
    std::unique_ptr<Mesh> gen_square_mesh() noexcept;// ��bug��ֻ���ó���һ��������
    std::unique_ptr<Mesh> gen_round_mesh(int segments = 100) noexcept;
    std::unique_ptr<Mesh> gen_triangle_mesh() noexcept;
    std::unique_ptr<Mesh> gen_line_mesh() noexcept;
    std::unique_ptr<Mesh> gen_point_mesh() noexcept;
    std::unique_ptr<Mesh> gen_ball_mesh(int segments = 100, int stacks = 50) noexcept;
    std::unique_ptr<Mesh> gen_cube_mesh() noexcept;
}
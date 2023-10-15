#pragma once

#include <format>
#include <vector>
#include <memory>
#include <string>
#include <string_view>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <quick_gl/texture.hpp>
#include <quick_gl/image.hpp>

// TODO: 需要大改
// 具体见vertex.hpp

namespace quick3d::gl
{
    constexpr uint32_t MAX_BONE_INFLUENCE{ 4 };

    struct MeshVertexPack
    {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 tex_coords;
        glm::vec3 tangent;
        glm::vec3 bitangent;
        int bone_ids[MAX_BONE_INFLUENCE];
        float weights[MAX_BONE_INFLUENCE];
    };

    struct MeshTexturePack
    {
        std::unique_ptr<Texture> texture;
        std::string type;
        std::string path;

        MeshTexturePack(std::string_view file_name,std::string_view directory,std::string_view type)
            : texture(std::make_unique<Texture>(GL_RGBA,Image(std::format("{}/{}",directory,file_name),false))),
                type(type),path(std::format("{}/{}",directory,file_name))
        {
        }
    };

    class Mesh
    {
    private:
        std::vector<unsigned int> indices;
        std::vector<MeshVertexPack> vertices;
        std::vector<MeshTexturePack*> textures;
        GLuint vao_id,vbo_id,ebo_id;

        void setup_vao() noexcept;
        void delete_vao() noexcept;

    public:
        Mesh(std::vector<MeshTexturePack*> textures,
            std::vector<MeshVertexPack> vertices,
            std::vector<unsigned int> indices) noexcept;

        Mesh(Mesh&) = delete;

        ~Mesh() noexcept;

        void bind_instance_array(GLuint instance_vbo_id, GLuint index, GLuint len,
            GLuint vertex_size, GLuint offset_size, GLuint divisor) const noexcept;

        template <typename T>
        requires requires(T t)
        {
            {t.get_program_id()} -> std::same_as<GLuint>;
            {t.set_uniform(std::declval<std::string_view>(),
                std::declval<int>())} -> std::same_as<void>;
        }
        void draw_mesh(const T& t,uint32_t instance = 0) noexcept
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

            glBindVertexArray(vao_id);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_id);

            if(!instance)
                glDrawElements(GL_TRIANGLES,static_cast<GLsizei>(indices.size()),GL_UNSIGNED_INT,0);
            else
                glDrawElementsInstanced(GL_TRIANGLES,static_cast<GLsizei>(indices.size()),GL_UNSIGNED_INT,0,instance);

            glBindVertexArray(0);
            glActiveTexture(GL_TEXTURE0);
            glUseProgram(0);
        }
    };
}
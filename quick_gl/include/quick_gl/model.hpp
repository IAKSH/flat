#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <quick_gl/mesh.hpp>

namespace quick3d::gl
{
    class Model
    {
    private:
        std::vector<std::unique_ptr<MeshTexturePack>> textures_loaded;
        std::vector<std::unique_ptr<Mesh>> meshes;
        const std::string directory;

        void load_model(std::string_view path) noexcept(false);
        void process_node(aiNode* node,const aiScene* scene) noexcept;
        void process_mesh(aiMesh* mesh,const aiScene* scene) noexcept;

        // this will return the vector of MeshTexturesPack's ptr, this bare ptr is for Mesh to use
        // the unique_ptr of MeshTexturesPack will be push to textures_loaded automaticly
        std::vector<MeshTexturePack*> load_material_textures(aiMaterial* mat,aiTextureType type,
            std::string_view type_name) noexcept;

    public:
        Model(std::string_view path) noexcept(false);

        Model(Model&) = delete;

        ~Model() = default;

        template <typename T>
        requires requires(T t)
        {
            {t.get_program_id()} -> std::same_as<GLuint>;
            {t.set_uniform(std::declval<std::string_view>(),
                std::declval<int>())} -> std::same_as<void>;
        }
        void draw_model(const T& t,uint32_t instance = 0) noexcept
        {
            for(const auto& mesh : meshes)
                mesh->draw_mesh(t,instance);
        }
    };
}
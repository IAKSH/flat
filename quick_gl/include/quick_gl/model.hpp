#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <quick_gl/mesh.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <map>

namespace quick3d::gl
{
    struct BoneInfo
    {
        int id;
        glm::mat4 offset;
    };

    struct KeyPosition
    {
        glm::vec3 position;
        float time_stamp;
    };

    struct KeyRotation
    {
        glm::quat orientation;
        float time_stamp;
    };

    struct KeyScale
    {
        glm::vec3 scale;
        float time_stamp;
    };

    class Bone
    {
    private:
        std::vector<KeyPosition> positions;
        std::vector<KeyRotation> rotations;
        std::vector<KeyScale> scales;
        int num_positions;
        int num_rotations;
        int num_scalings;
        glm::mat4 local_transform;
        std::string name;
        int id;

        float get_scale_factor(float last_time_stamp, float next_time_stamp, float animation_time) noexcept;
        glm::mat4 interpolate_position(float animation_time) noexcept;
        glm::mat4 interpolate_rotation(float animation_time) noexcept;
        glm::mat4 interpolate_scaling(float animation_time) noexcept;

    public:
        Bone(const std::string_view name, int ID, const aiNodeAnim* channel) noexcept;
        ~Bone() = default;

        void update(float animation_time) noexcept;
        const glm::mat4& get_local_transform() const noexcept;
        std::string_view get_bone_name() const noexcept;
        int get_bone_id() const noexcept;
        int get_position_index(float animation_time) const noexcept;
        int get_rotation_index(float animation_time) const noexcept;
        int get_scale_index(float animation_time) const noexcept;
    };

    class Model
    {
    private:
        std::vector<std::unique_ptr<MeshTexturePack>> textures_loaded;
        std::vector<std::unique_ptr<Mesh>> meshes;
        std::map<std::string, BoneInfo> bones;
        int bone_count;
        const std::string directory;

        void load_model(std::string_view path) noexcept(false);
        void process_node(aiNode* node,const aiScene* scene) noexcept;
        void process_mesh(aiMesh* mesh,const aiScene* scene) noexcept;
        void extract_vertices_bone_weight(std::vector<MeshVertexPack>& vertices, aiMesh* mesh, const aiScene* scene) noexcept;

        // this will return the vector of MeshTexturesPack's ptr, this bare ptr is for Mesh to use
        // the unique_ptr of MeshTexturesPack will be push to textures_loaded automaticly
        std::vector<MeshTexturePack*> load_material_textures(aiMaterial* mat,aiTextureType type,
            std::string_view type_name) noexcept;

    public:
        Model(std::string_view path) noexcept(false);
        Model(Model&) = delete;
        ~Model() = default;

        const std::vector<std::unique_ptr<Mesh>>& get_meshes() const noexcept;
        std::map<std::string, BoneInfo>& get_bones() noexcept;
        int& get_bone_count() noexcept;

        template <typename T>
        requires requires(T t)
        {
            {t.get_program_id()} -> std::same_as<GLuint>;
            {t.set_uniform(std::declval<std::string_view>(),
                std::declval<int>())} -> std::same_as<void>;
        }
        void draw_model(const T& t,uint32_t instance = 0) noexcept
        {
            for (const auto& mesh : meshes)
                mesh->draw_mesh(t, GL_TRIANGLES, instance);
        }
    };

    struct AssimpAnimationNode
    {
        glm::mat4 transformation;
        std::string name;
        int children_count;
        std::vector<AssimpAnimationNode> childrens;
    };

    class Animation
    {
    private:
        float duration;
        int tps;
        std::vector<Bone> bones;
        AssimpAnimationNode root_node;
        std::map<std::string, BoneInfo> bone_info_map;

        void read_missing_bones(const aiAnimation* animation, Model& model) noexcept;
        void read_heirarchy_data(AssimpAnimationNode& dest, const aiNode* src) noexcept(false);

    public:
        Animation() = default;
        Animation(std::string_view path, Model& model) noexcept(false);
        Animation(Animation&) = delete;
        ~Animation() = default;

        Bone* find_bone(std::string_view name) noexcept;
        float get_tps() const noexcept;
        float get_duration() const noexcept;
        const AssimpAnimationNode& get_root_node() const noexcept;
        const std::map<std::string, BoneInfo>& get_bone_id_map() const noexcept;
    };

    class Animator
    {
    private:
        std::vector<glm::mat4> final_bone_matrices;
        Animation* current_animation;
        float current_time;
        float delta_time;

    public:
        Animator(Animation* animation) noexcept;
        void update_animation(float dt) noexcept;
        void play_animation(Animation* animation) noexcept;
        void calculate_bone_transform(const AssimpAnimationNode* node, glm::mat4 parent_transform) noexcept;
        const std::vector<glm::mat4>& get_final_bone_matrices() noexcept;
    };
}
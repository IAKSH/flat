#include <format>
#include <stdexcept>
#include <quick_gl/model.hpp>

auto aiMatrix2glm(const aiMatrix4x4& from)
{
    glm::mat4 to;
    //the a,b,c,d in assimp is the row ; the 1,2,3,4 is the column
    to[0][0] = from.a1; to[1][0] = from.a2; to[2][0] = from.a3; to[3][0] = from.a4;
    to[0][1] = from.b1; to[1][1] = from.b2; to[2][1] = from.b3; to[3][1] = from.b4;
    to[0][2] = from.c1; to[1][2] = from.c2; to[2][2] = from.c3; to[3][2] = from.c4;
    to[0][3] = from.d1; to[1][3] = from.d2; to[2][3] = from.d3; to[3][3] = from.d4;
    return to;
};

auto aiVec3D2glm(const aiVector3D& vec)
{
    return glm::vec3(vec.x, vec.y, vec.z);
}

auto aiQuat2glm(const aiQuaternion& pOrientation)
{
    return glm::quat(pOrientation.w, pOrientation.x, pOrientation.y, pOrientation.z);
}

quick3d::gl::Model::Model(std::string_view path) noexcept(false)
    : directory(path.substr(0, path.find_last_of('/'))), bone_count(0)
{
    load_model(path);
}

const std::vector<std::unique_ptr<quick3d::gl::Mesh>>& quick3d::gl::Model::get_meshes() const noexcept
{
    return meshes;
}

std::map<std::string, quick3d::gl::BoneInfo>& quick3d::gl::Model::get_bones() noexcept
{
    return bones;
}

int& quick3d::gl::Model::get_bone_count() noexcept
{
    return bone_count;
}

void quick3d::gl::Model::load_model(std::string_view path) noexcept(false)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(std::string(path), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace); 

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        throw std::runtime_error(std::format("Error from ASSIMP: {}",importer.GetErrorString()));

    process_node(scene->mRootNode,scene);
}

void quick3d::gl::Model::process_node(aiNode* node,const aiScene* scene) noexcept
{
    for(uint32_t i = 0;i < node->mNumMeshes;i++)
    {
        aiMesh* mesh{ scene->mMeshes[node->mMeshes[i]] };
        process_mesh(mesh, scene);
    }
    
    for(uint32_t i = 0;i < node->mNumChildren;i++)
        process_node(node->mChildren[i],scene);
}

void quick3d::gl::Model::process_mesh(aiMesh* mesh,const aiScene* scene) noexcept
{
    std::vector<unsigned int> indices;
    std::vector<MeshVertexPack> vertices;
    std::vector<MeshTexturePack*> textures;

    for(uint32_t i = 0;i < mesh->mNumVertices;i++)
    {
        MeshVertexPack vertex;
        for (int i = 0; i < MAX_BONE_INFLUENCE; i++)
        {
            vertex.bone_ids[i] = -1;
            vertex.weights[i] = 0.0f;
        }

        glm::vec3 vector;
        
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.position = vector;
        // normals
        if (mesh->HasNormals())
        {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.normal = vector;
        }
        // texture coordinates
        if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.uv = vec;
            if (mesh->mTangents)
            {
                // tangent
                vector.x = mesh->mTangents[i].x;
                vector.y = mesh->mTangents[i].y;
                vector.z = mesh->mTangents[i].z;
                vertex.tangent = vector;
            }
            if (mesh->mBitangents)
            {
                // bitangent
                vector.x = mesh->mBitangents[i].x;
                vector.y = mesh->mBitangents[i].y;
                vector.z = mesh->mBitangents[i].z;
                vertex.bitangent = vector;
            }
        }
        else
            vertex.uv = glm::vec2(0.0f, 0.0f);

        vertices.push_back(vertex);
    }

    for(uint32_t i = 0;i < mesh->mNumFaces;i++)
    {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0;j < face.mNumIndices;j++)
            indices.push_back(face.mIndices[j]);
    }

    aiMaterial* material{ scene->mMaterials[mesh->mMaterialIndex] };

    std::vector<MeshTexturePack*> diffuse_maps{ load_material_textures(material, aiTextureType_DIFFUSE, "texture_diffuse") };
    std::vector<MeshTexturePack*> specular_maps{ load_material_textures(material, aiTextureType_SPECULAR, "texture_specular") };
    std::vector<MeshTexturePack*> normal_maps{ load_material_textures(material, aiTextureType_HEIGHT, "texture_normal") };
    std::vector<MeshTexturePack*> height_maps{ load_material_textures(material, aiTextureType_AMBIENT, "texture_height") };

    textures.insert(std::end(textures),std::begin(diffuse_maps),std::end(diffuse_maps));
    textures.insert(std::end(textures),std::begin(specular_maps),std::end(specular_maps));
    textures.insert(std::end(textures),std::begin(normal_maps),std::end(normal_maps));
    textures.insert(std::end(textures),std::begin(height_maps),std::end(height_maps));

    extract_vertices_bone_weight(vertices, mesh, scene);
    meshes.push_back(std::make_unique<Mesh>(textures, vertices, indices));
}

void quick3d::gl::Model::extract_vertices_bone_weight(std::vector<MeshVertexPack>& vertices, aiMesh* mesh, const aiScene* scene) noexcept
{
    for (int bone_index = 0; bone_index < mesh->mNumBones; ++bone_index)
    {
        int bone_id = -1;
        std::string bone_name = mesh->mBones[bone_index]->mName.C_Str();
        if (bones.find(bone_name) == bones.end())
        {
            BoneInfo newBoneInfo;
            newBoneInfo.id = bone_count;
            newBoneInfo.offset = aiMatrix2glm(mesh->mBones[bone_index]->mOffsetMatrix);
            bones[bone_name] = newBoneInfo;
            bone_id = bone_count;
            bone_count++;
        }
        else
        {
            bone_id = bones[bone_name].id;
        }
        assert(bone_id != -1);
        auto weights = mesh->mBones[bone_index]->mWeights;
        int num_weights = mesh->mBones[bone_index]->mNumWeights;

        for (int weight_index = 0; weight_index < num_weights; ++weight_index)
        {
            int vertex_id = weights[weight_index].mVertexId;
            float weight = weights[weight_index].mWeight;
            assert(vertex_id <= vertices.size());

            for (int i = 0; i < MAX_BONE_INFLUENCE; ++i)
            {
                auto& vertex{ vertices[vertex_id] };
                if (vertex.bone_ids[i] < 0)
                {
                    vertex.weights[i] = weight;
                    vertex.bone_ids[i] = bone_id;
                    break;
                }
            }
        }
    }
}

std::vector<quick3d::gl::MeshTexturePack*> quick3d::gl::Model::load_material_textures(aiMaterial* mat,
    aiTextureType type,std::string_view type_name) noexcept
{
    std::vector<MeshTexturePack*> textures;
    for(uint32_t i = 0;i < mat->GetTextureCount(type);i++)
    {
        aiString str;
        mat->GetTexture(type,i,&str);
        bool skip{ false };

        for(uint32_t j = 0;j < textures_loaded.size();j++)
        {
            if(textures_loaded[j]->path == std::format("{}/{}",directory,str.C_Str()))
            {
                textures.push_back(textures_loaded[j].get());
                skip = true;
                break;
            }
        }

        if(!skip)
        {
            auto texture{ std::make_unique<MeshTexturePack>(std::string_view(str.C_Str()),directory,type_name) };
            textures.push_back(texture.get());
            textures_loaded.push_back(std::move(texture));
        }
    }

    return textures;
}



quick3d::gl::Bone::Bone(std::string_view name, int id, const aiNodeAnim* channel) noexcept
    : name(name), id(id), local_transform(1.0f)
{
    num_positions = channel->mNumPositionKeys;
    for (int position_index = 0; position_index < num_positions; ++position_index)
    {
        aiVector3D ai_position = channel->mPositionKeys[position_index].mValue;
        float time_stamp = channel->mPositionKeys[position_index].mTime;
        KeyPosition data;
        data.position = aiVec3D2glm(ai_position);
        data.time_stamp = time_stamp;
        positions.push_back(data);
    }

    num_rotations = channel->mNumRotationKeys;
    for (int rotation_index = 0; rotation_index < num_rotations; ++rotation_index)
    {
        aiQuaternion ai_orientation = channel->mRotationKeys[rotation_index].mValue;
        float time_stamp = channel->mRotationKeys[rotation_index].mTime;
        KeyRotation data;
        data.orientation = aiQuat2glm(ai_orientation);
        data.time_stamp = time_stamp;
        rotations.push_back(data);
    }

    num_scalings = channel->mNumScalingKeys;
    for (int key_index = 0; key_index < num_scalings; ++key_index)
    {
        aiVector3D scale = channel->mScalingKeys[key_index].mValue;
        float time_stamp = channel->mScalingKeys[key_index].mTime;
        KeyScale data;
        data.scale = aiVec3D2glm(scale);
        data.time_stamp = time_stamp;
        scales.push_back(data);
    }
}

void quick3d::gl::Bone::update(float animation_time) noexcept
{
    glm::mat4 translation = interpolate_position(animation_time);
    glm::mat4 rotation = interpolate_rotation(animation_time);
    glm::mat4 scale = interpolate_scaling(animation_time);
    local_transform = translation * rotation * scale;
}

const glm::mat4& quick3d::gl::Bone::get_local_transform() const noexcept
{
    return local_transform;
}

std::string_view quick3d::gl::Bone::get_bone_name() const noexcept
{
    return name;
}

int quick3d::gl::Bone::get_bone_id() const noexcept
{
    return id;
}

int quick3d::gl::Bone::get_position_index(float animation_time) const noexcept
{
    for (int index = 0; index < num_positions - 1; ++index)
    {
        if (animation_time < positions[index + 1].time_stamp)
            return index;
    }
    assert(0);
}

int quick3d::gl::Bone::get_rotation_index(float animation_time) const noexcept
{
    for (int index = 0; index < num_rotations - 1; ++index)
    {
        if (animation_time < rotations[index + 1].time_stamp)
            return index;
    }
    assert(0);
}

int quick3d::gl::Bone::get_scale_index(float animation_time) const noexcept
{
    for (int index = 0; index < num_scalings - 1; ++index)
    {
        if (animation_time < scales[index + 1].time_stamp)
            return index;
    }
    assert(0);
}

float quick3d::gl::Bone::get_scale_factor(float last_time_stamp, float next_time_stamp, float animation_time) noexcept
{
    float scale_factor{ 0.0f };
    float midway_length = animation_time - last_time_stamp;
    float frames_diff = next_time_stamp - last_time_stamp;
    scale_factor = midway_length / frames_diff;
    return scale_factor;
}

glm::mat4 quick3d::gl::Bone::interpolate_position(float animation_time) noexcept
{
    if (1 == num_positions)
        return glm::translate(glm::mat4(1.0f), positions[0].position);

    int p0_index = get_position_index(animation_time);
    int p1_index = p0_index + 1;
    float scale_factor = get_scale_factor(positions[p0_index].time_stamp, positions[p1_index].time_stamp, animation_time);
    glm::vec3 finalPosition = glm::mix(positions[p0_index].position, positions[p1_index].position, scale_factor);
    return glm::translate(glm::mat4(1.0f), finalPosition);
}

glm::mat4 quick3d::gl::Bone::interpolate_rotation(float animation_time) noexcept
{
    if (1 == num_rotations)
    {
        auto rotation = glm::normalize(rotations[0].orientation);
        return glm::toMat4(rotation);
    }

    int p0Index = get_rotation_index(animation_time);
    int p1Index = p0Index + 1;
    float scale_factor = get_scale_factor(rotations[p0Index].time_stamp,
        rotations[p1Index].time_stamp, animation_time);
    glm::quat finalRotation = glm::slerp(rotations[p0Index].orientation, rotations[p1Index].orientation
        , scale_factor);
    finalRotation = glm::normalize(finalRotation);
    return glm::toMat4(finalRotation);

}

glm::mat4 quick3d::gl::Bone::interpolate_scaling(float animation_time) noexcept
{
    if (1 == num_scalings)
        return glm::scale(glm::mat4(1.0f), scales[0].scale);

    int p0Index = get_scale_index(animation_time);
    int p1Index = p0Index + 1;
    float scaleFactor = get_scale_factor(scales[p0Index].time_stamp,
        scales[p1Index].time_stamp, animation_time);
    glm::vec3 finalScale = glm::mix(scales[p0Index].scale, scales[p1Index].scale
        , scaleFactor);
    return glm::scale(glm::mat4(1.0f), finalScale);
}

quick3d::gl::Animation::Animation(std::string_view path, Model& model) noexcept(false)
{
    Assimp::Importer importer;
    const aiScene* scene{ importer.ReadFile(path.data(),aiProcess_Triangulate) };
    if (!(scene && scene->mRootNode))
        throw std::runtime_error("scene is empty");

    auto animation{ scene->mAnimations[0] };
    duration = animation->mDuration;
    tps = animation->mTicksPerSecond;
    read_heirarchy_data(root_node, scene->mRootNode);
    read_missing_bones(animation, model);
}

quick3d::gl::Bone* quick3d::gl::Animation::find_bone(std::string_view name) noexcept
{
    auto iter = std::find_if(std::begin(bones), std::end(bones), [&](const Bone& bone) -> bool
        {
            return bone.get_bone_name() == name;
        });

    if (iter == std::end(bones)) return nullptr;
    else return &(*iter);
}

float quick3d::gl::Animation::get_tps() const noexcept
{
    return tps;
}

float quick3d::gl::Animation::get_duration() const noexcept
{
    return duration;
}

const quick3d::gl::AssimpAnimationNode& quick3d::gl::Animation::get_root_node() const noexcept
{
    return root_node;
}

const std::map<std::string, quick3d::gl::BoneInfo>& quick3d::gl::Animation::get_bone_id_map() const noexcept
{
    return bone_info_map;
}

void quick3d::gl::Animation::read_missing_bones(const aiAnimation* animation, Model& model) noexcept
{
    auto size{ animation->mNumChannels };
    std::map<std::string, quick3d::gl::BoneInfo>& bone_info_map{ model.get_bones() };
    int& bone_count{ model.get_bone_count() };
    
    for (int i = 0; i < size; i++)
    {
        auto channel{ animation->mChannels[i] };
        std::string bone_name{ channel->mNodeName.data };

        if (bone_info_map.find(bone_name) == bone_info_map.end())
        {
            bone_info_map[bone_name].id = bone_count;
            ++bone_count;
        }
        
        bones.push_back(Bone(channel->mNodeName.data, bone_info_map[channel->mNodeName.data].id, channel));
    }

    this->bone_info_map = bone_info_map;
}

void quick3d::gl::Animation::read_heirarchy_data(AssimpAnimationNode& dest, const aiNode* src) noexcept(false)
{
    if (!src)
        throw std::runtime_error("animation node is null");

    dest.name = src->mName.data;
    dest.transformation = aiMatrix2glm(src->mTransformation);
    dest.children_count = src->mNumChildren;

    for (int i = 0; i < src->mNumChildren; i++)
    {
        AssimpAnimationNode new_node;
        read_heirarchy_data(new_node, src->mChildren[i]);
        dest.childrens.push_back(new_node);
    }
}

quick3d::gl::Animator::Animator(Animation* animation) noexcept
{
    current_time = 0.0;
    current_animation = animation;
    final_bone_matrices.reserve(1000);
    for (int i = 0; i < 1000; i++)
        final_bone_matrices.push_back(glm::mat4(1.0f));
}

void quick3d::gl::Animator::update_animation(float dt) noexcept
{
    delta_time = dt;
    if (current_animation)
    {
        current_time += current_animation->get_tps() * dt;
        current_time = fmod(current_time, current_animation->get_duration());
        calculate_bone_transform(&current_animation->get_root_node(), glm::mat4(1.0f));
    }
}

void quick3d::gl::Animator::play_animation(Animation* animation) noexcept
{
    current_animation = animation;
    current_time = 0.0f;
}

void quick3d::gl::Animator::calculate_bone_transform(const AssimpAnimationNode* node, glm::mat4 parentTransform) noexcept
{
    std::string node_name = node->name;
    glm::mat4 node_transform = node->transformation;
    Bone* Bone = current_animation->find_bone(node_name);

    if (Bone)
    {
        Bone->update(current_time);
        node_transform = Bone->get_local_transform();
    }

    glm::mat4 global_transformation = parentTransform * node_transform;

    auto boneInfoMap = current_animation->get_bone_id_map();
    if (boneInfoMap.find(node_name) != boneInfoMap.end())
    {
        int index = boneInfoMap[node_name].id;
        glm::mat4 offset = boneInfoMap[node_name].offset;
        final_bone_matrices[index] = global_transformation * offset;
    }

    for (int i = 0; i < node->children_count; i++)
        calculate_bone_transform(&node->childrens[i], global_transformation);
}

const std::vector<glm::mat4>& quick3d::gl::Animator::get_final_bone_matrices() noexcept
{
    return final_bone_matrices;
}
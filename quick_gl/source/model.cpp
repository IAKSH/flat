#include <format>
#include <stdexcept>
#include <quick_gl/model.hpp>

quick3d::gl::Model::Model(std::string_view path) noexcept(false)
    : directory(path.substr(0,path.find_last_of('/')))
{
    load_model(path);
}

const std::vector<std::unique_ptr<quick3d::gl::Mesh>>* quick3d::gl::Model::get_meshes() const noexcept
{
    return &meshes;
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
            vertex.tex_coords = vec;
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
            vertex.tex_coords = glm::vec2(0.0f, 0.0f);

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

    meshes.push_back(std::make_unique<Mesh>(textures,vertices,indices));
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
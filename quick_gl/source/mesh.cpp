#include <quick_gl/mesh.hpp>

quick3d::gl::Mesh::Mesh(std::vector<MeshTexturePack*> textures,
            std::vector<MeshVertexPack> vertices,
            std::vector<unsigned int> indices) noexcept
    : textures(textures),vertices(vertices),indices(indices)
{
    setup_vao();
}

void quick3d::gl::Mesh::setup_vao() noexcept
{
    auto vbo_size{ vertices.size() * sizeof(MeshVertexPack) };
    vbo = std::make_unique<Buffer>(GL_ARRAY_BUFFER, GL_STATIC_DRAW, vbo_size);
    vbo->write_buffer_data(vertices, vbo_size);

    auto ebo_size{ indices.size() * sizeof(unsigned int) };
    ebo = std::make_unique<Buffer>(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW, ebo_size);
    ebo->write_buffer_data(indices, ebo_size);

    vao.bind_ebo(*ebo);
    vao.add_attrib(*vbo, 0, 3, sizeof(MeshVertexPack) / sizeof(float), 0);
    vao.add_attrib(*vbo, 1, 3, sizeof(MeshVertexPack) / sizeof(float), offsetof(MeshVertexPack, normal)     / sizeof(float));
    vao.add_attrib(*vbo, 2, 2, sizeof(MeshVertexPack) / sizeof(float), offsetof(MeshVertexPack, tex_coords) / sizeof(float));
    vao.add_attrib(*vbo, 3, 3, sizeof(MeshVertexPack) / sizeof(float), offsetof(MeshVertexPack, tangent)    / sizeof(float));
    vao.add_attrib(*vbo, 4, 3, sizeof(MeshVertexPack) / sizeof(float), offsetof(MeshVertexPack, bitangent)  / sizeof(float));
    vao.add_attrib(*vbo, 5, 4, sizeof(MeshVertexPack) / sizeof(float), offsetof(MeshVertexPack, bone_ids)   / sizeof(float));
    vao.add_attrib(*vbo, 6, 4, sizeof(MeshVertexPack) / sizeof(float), offsetof(MeshVertexPack, weights)    / sizeof(float));
}

quick3d::gl::MeshTexturePack::MeshTexturePack(std::string_view file_name, std::string_view directory, std::string_view type)
    : type(type), path(std::format("{}/{}", directory, file_name))
{
    if (type == "texture_diffuse")
        texture = std::make_unique<Texture>(GL_SRGB8_ALPHA8, Image(std::format("{}/{}", directory, file_name), false));
    else
        texture = std::make_unique<Texture>(GL_RGBA8, Image(std::format("{}/{}", directory, file_name), false));
}
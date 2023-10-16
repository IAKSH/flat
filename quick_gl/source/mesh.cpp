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
    vbo->load_buffer_data(vertices, vbo_size);

    auto ebo_size{ indices.size() * sizeof(unsigned int) };
    ebo = std::make_unique<Buffer>(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW, ebo_size);
    ebo->load_buffer_data(indices, ebo_size);

    vao.bind_ebo(*ebo);
    vao.add_attrib(*vbo, 0, 3, sizeof(MeshVertexPack), 0);
    vao.add_attrib(*vbo, 1, 3, sizeof(MeshVertexPack), offsetof(MeshVertexPack, normal) / sizeof(float));
    vao.add_attrib(*vbo, 2, 2, sizeof(MeshVertexPack), offsetof(MeshVertexPack, tex_coords) / sizeof(float));
    vao.add_attrib(*vbo, 3, 3, sizeof(MeshVertexPack), offsetof(MeshVertexPack, tangent) / sizeof(float));
    vao.add_attrib(*vbo, 4, 3, sizeof(MeshVertexPack), offsetof(MeshVertexPack, bitangent) / sizeof(float));
    vao.add_attrib(*vbo, 5, 4, sizeof(MeshVertexPack), offsetof(MeshVertexPack, bone_ids) / sizeof(float));
    vao.add_attrib(*vbo, 6, 4, sizeof(MeshVertexPack), offsetof(MeshVertexPack, weights) / sizeof(float));
}
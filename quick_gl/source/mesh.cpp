#include <quick_gl/mesh.hpp>

quick3d::gl::Mesh::Mesh(std::vector<MeshTexturePack*> textures,
            std::vector<MeshVertexPack> vertices,
            std::vector<unsigned int> indices) noexcept
    : textures(textures),vertices(vertices),indices(indices)
{
    setup_vao();
}

quick3d::gl::Mesh::~Mesh() noexcept
{
    delete_vao();
}

void quick3d::gl::Mesh::setup_vao() noexcept
{
    glGenVertexArrays(1,&vao_id);
    glGenBuffers(1,&vbo_id);
    glGenBuffers(1,&ebo_id);

    glBindVertexArray(vao_id);

    glBindBuffer(GL_ARRAY_BUFFER,vbo_id);
    glBufferData(GL_ARRAY_BUFFER,vertices.size() * sizeof(MeshVertexPack),vertices.data(),GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,indices.size() * sizeof(unsigned int),indices.data(),GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(MeshVertexPack),(void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertexPack), (void *)offsetof(MeshVertexPack,normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(MeshVertexPack), (void *)offsetof(MeshVertexPack,tex_coords));

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertexPack), (void *)offsetof(MeshVertexPack,tangent));

    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertexPack), (void *)offsetof(MeshVertexPack,bitangent));

    glEnableVertexAttribArray(5);
    glVertexAttribIPointer(5, 4, GL_INT, sizeof(MeshVertexPack), (void *)offsetof(MeshVertexPack,bone_ids));

    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(MeshVertexPack), (void *)offsetof(MeshVertexPack,weights));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);
}

void quick3d::gl::Mesh::delete_vao() noexcept
{
    glDeleteVertexArrays(1,&vao_id);
    glDeleteBuffers(1,&vbo_id);
    glDeleteBuffers(1,&ebo_id);
}
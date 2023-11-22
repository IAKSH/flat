#include <quick_gl/mesh.hpp>
#include <array>

quick3d::gl::Mesh::Mesh(std::vector<MeshTexturePack*>& textures,
	std::vector<MeshVertexPack>& vertices,
	std::vector<unsigned int>& indices,
	GLenum primitive_type) noexcept
	: textures(textures), indices_len(indices.size()), primitive_type(primitive_type)
{
	setup_vao(vertices, indices);
}

void quick3d::gl::Mesh::setup_vao(std::vector<MeshVertexPack>& vertices,
	std::vector<unsigned int>& indices) noexcept
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
    vao.add_attrib(*vbo, 2, 2, sizeof(MeshVertexPack) / sizeof(float), offsetof(MeshVertexPack, uv) / sizeof(float));
    vao.add_attrib(*vbo, 3, 3, sizeof(MeshVertexPack) / sizeof(float), offsetof(MeshVertexPack, tangent)    / sizeof(float));
    vao.add_attrib(*vbo, 4, 3, sizeof(MeshVertexPack) / sizeof(float), offsetof(MeshVertexPack, bitangent)  / sizeof(float));
    vao.add_attrib(*vbo, 5, 4, sizeof(MeshVertexPack) / sizeof(float), offsetof(MeshVertexPack, bone_ids)   / sizeof(float));
    vao.add_attrib(*vbo, 6, 4, sizeof(MeshVertexPack) / sizeof(float), offsetof(MeshVertexPack, weights)    / sizeof(float));
}

quick3d::gl::VertexArray& quick3d::gl::Mesh::get_vao() noexcept
{
	return vao;
}

quick3d::gl::Buffer& quick3d::gl::Mesh::get_vbo() noexcept
{
	return *vbo;
}

quick3d::gl::Buffer& quick3d::gl::Mesh::get_ebo() noexcept
{
	return *ebo;
}

std::vector<quick3d::gl::MeshTexturePack*>& quick3d::gl::Mesh::get_textures() noexcept
{
	return textures;
}

void quick3d::gl::Mesh::set_indices_size(std::size_t indices_len) noexcept
{
	this->indices_len = indices_len;
}

quick3d::gl::MeshTexturePack::MeshTexturePack(std::string_view file_name, std::string_view directory, std::string_view type)
    : type(type), path(std::format("{}/{}", directory, file_name))
{
    if (type == "texture_diffuse")
        texture = std::make_unique<Texture>(GL_SRGB8_ALPHA8, Image(std::format("{}/{}", directory, file_name), false));
    else
        texture = std::make_unique<Texture>(GL_RGBA8, Image(std::format("{}/{}", directory, file_name), false));
}

void quick3d::gl::VertexArray::create_vao() noexcept
{
	glGenVertexArrays(1, &vao_id);
}

void quick3d::gl::VertexArray::delete_vao() noexcept
{
	glDeleteVertexArrays(1, &vao_id);
}

quick3d::gl::VertexArray::VertexArray() noexcept
	: has_ebo(false)
{
	create_vao();
}

quick3d::gl::VertexArray::~VertexArray() noexcept
{
	delete_vao();
}

GLuint quick3d::gl::VertexArray::get_vao_id() const noexcept
{
	return GLuint();
}

void quick3d::gl::VertexArray::bind_ebo(GLuint ebo_id) noexcept
{
	glBindVertexArray(vao_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_id);
	// unbind vao before you unbind ebo
	// because the binding vao will record any bind/unbind on GL_ELEMENT_ARRAY_BUFFER
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	has_ebo = true;
}

void quick3d::gl::VertexArray::add_attrib(GLenum buffer_target, uint32_t buffer_id,
	uint32_t index, uint32_t len, uint32_t vertex_len, uint32_t offset, bool normalized) noexcept(false)
{
	//if (buffer_target != GL_ARRAY_BUFFER)
	//	throw std::runtime_error("invalid buffer target given to VAO");

	glBindBuffer(buffer_target, buffer_id);
	glBindVertexArray(vao_id);

	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, len, GL_FLOAT, normalized, vertex_len * sizeof(float), (void*)(offset * sizeof(float)));

	glBindBuffer(buffer_target, 0);
	glBindVertexArray(0);
}

void quick3d::gl::VertexArray::draw(GLuint program_id, GLenum primitive, GLint first, GLsizei vertex_count, GLsizei instance) noexcept
{
	glUseProgram(program_id);
	glBindVertexArray(vao_id);

	// no need to bind vbo(s) and ebo here
	// because vao had recorded them before

	if (has_ebo)
		if (instance)
			glDrawElementsInstanced(primitive, vertex_count, GL_UNSIGNED_INT, 0, instance);
		else
			glDrawElements(primitive, vertex_count, GL_UNSIGNED_INT, 0);
	else
		if (instance)
			glDrawArraysInstanced(primitive, first, vertex_count, instance);
		else
			glDrawArrays(primitive, first, vertex_count);

	glBindVertexArray(0);
	glUseProgram(0);
}

std::unique_ptr<quick3d::gl::Mesh> quick3d::gl::gen_square_mesh() noexcept
{
	std::vector<MeshTexturePack*> textures;
	std::vector<MeshVertexPack> vertices
	{
		{glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f), glm::vec3(0.0f), {0}, {0.0f}},
		{glm::vec3(1.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, -1.0f), glm::vec3(0.0f), glm::vec3(0.0f), {0}, {0.0f}},
		{glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(-1.0f, -1.0f), glm::vec3(0.0f), glm::vec3(0.0f), {0}, {0.0f}},
		{glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(-1.0f, 1.0f), glm::vec3(0.0f), glm::vec3(0.0f), {0}, {0.0f}}
	};
	std::vector<unsigned int> indices
	{
		3,2,1,
		1,0,3
	};
	return std::make_unique<Mesh>(textures, vertices, indices);
}

std::unique_ptr<quick3d::gl::Mesh> quick3d::gl::gen_round_mesh(int segments) noexcept
{
	// segments是圆的分段数

	std::vector<MeshTexturePack*> textures;
	std::vector<MeshVertexPack> vertices;
	std::vector<unsigned int> indices;

	// gen vertices
	for (int i = 0; i <= segments; ++i)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(segments);
		float x = cosf(theta);
		float y = sinf(theta);

		MeshVertexPack vertex;
		vertex.position = glm::vec3(x, y, 0.0f);
		vertex.normal = glm::vec3(0.0f, 0.0f, 1.0f);
		vertex.uv = glm::vec2(x, y);
		vertex.tangent = glm::vec3(0.0f);
		vertex.bitangent = glm::vec3(0.0f);
		std::fill(std::begin(vertex.bone_ids), std::end(vertex.bone_ids), 0);
		std::fill(std::begin(vertex.weights), std::end(vertex.weights), 0.0f);

		vertices.push_back(vertex);
	}

	// gen index
	for (int i = 0; i < segments; ++i)
	{
		indices.push_back(0);
		indices.push_back(i + 1);
		indices.push_back(i + 2);
	}

	return std::make_unique<Mesh>(textures, vertices, indices);
}

std::unique_ptr<quick3d::gl::Mesh> quick3d::gl::gen_triangle_mesh() noexcept
{
	std::vector<MeshTexturePack*> textures;
	std::vector<MeshVertexPack> vertices
	{
		{glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.5f, 1.0f), glm::vec3(0.0f), glm::vec3(0.0f), {0}, {0.0f}},
		{glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f), glm::vec3(0.0f), {0}, {0.0f}},
		{glm::vec3(1.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f), glm::vec3(0.0f), {0}, {0.0f}}
	};
	std::vector<unsigned int> indices
	{
		0, 1, 2
	};
	return std::make_unique<Mesh>(textures, vertices, indices);
}

std::unique_ptr<quick3d::gl::Mesh> quick3d::gl::gen_line_mesh() noexcept
{
	std::vector<MeshTexturePack*> textures;
	std::vector<MeshVertexPack> vertices
	{
		{glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.5f), glm::vec3(0.0f), glm::vec3(0.0f), {0}, {0.0f}},
		{glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.5f), glm::vec3(0.0f), glm::vec3(0.0f), {0}, {0.0f}}
	};
	std::vector<unsigned int> indices
	{
		0, 1
	};
	return std::make_unique<Mesh>(textures, vertices, indices, GL_LINES);
}

std::unique_ptr<quick3d::gl::Mesh> quick3d::gl::gen_point_mesh() noexcept
{
	std::vector<MeshTexturePack*> textures;
	std::vector<MeshVertexPack> vertices
	{
		{glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.5f, 0.5f), glm::vec3(0.0f), glm::vec3(0.0f), {0}, {0.0f}}
	};
	std::vector<unsigned int> indices
	{
		0
	};
	return std::make_unique<Mesh>(textures, vertices, indices, GL_POINTS);
}

std::unique_ptr<quick3d::gl::Mesh> quick3d::gl::gen_ball_mesh(int segments, int stacks) noexcept
{
	// segments和stacks分别是球的分段数和分层数

	std::vector<MeshTexturePack*> textures;
	std::vector<MeshVertexPack> vertices;
	std::vector<unsigned int> indices;

	// gen vertex
	for (int i = 0; i <= stacks; ++i)
	{
		float v = float(i) / float(stacks);
		float phi = v * 3.1415926f;

		for (int j = 0; j <= segments; ++j)
		{
			float u = float(j) / float(segments);
			float theta = u * 2.0f * 3.1415926f;

			float x = cosf(theta) * sinf(phi);
			float y = cosf(phi);
			float z = sinf(theta) * sinf(phi);

			MeshVertexPack vertex;
			vertex.position = glm::vec3(x, y, z);
			vertex.normal = glm::vec3(x, y, z);
			vertex.uv = glm::vec2(u, v);
			vertex.tangent = glm::vec3(0.0f);
			vertex.bitangent = glm::vec3(0.0f);
			std::fill(std::begin(vertex.bone_ids), std::end(vertex.bone_ids), 0);
			std::fill(std::begin(vertex.weights), std::end(vertex.weights), 0.0f);

			vertices.push_back(vertex);
		}
	}

	// gen index
	for (int i = 0; i < stacks; ++i)
	{
		int k1 = i * (segments + 1);
		int k2 = k1 + segments + 1;

		for (int j = 0; j < segments; ++j, ++k1, ++k2)
		{
			if (i != 0)
			{
				indices.push_back(k1);
				indices.push_back(k2);
				indices.push_back(k1 + 1);
			}

			if (i != (stacks - 1))
			{
				indices.push_back(k1 + 1);
				indices.push_back(k2);
				indices.push_back(k2 + 1);
			}
		}
	}

	return std::make_unique<Mesh>(textures, vertices, indices);
}

std::unique_ptr<quick3d::gl::Mesh> quick3d::gl::gen_cube_mesh() noexcept
{
	std::vector<MeshTexturePack*> textures;
	std::vector<MeshVertexPack> vertices
	{
		// front
		{glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f), glm::vec3(0.0f), {0}, {0.0f}},
		{glm::vec3(1.0f, -1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f), glm::vec3(0.0f), {0}, {0.0f}},
		{glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f), glm::vec3(0.0f), {0}, {0.0f}},
		{glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f), glm::vec3(0.0f), {0}, {0.0f}},
		// back
		{glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f), glm::vec3(0.0f), {0}, {0.0f}},
		{glm::vec3(1.0f, -1.0f, -1.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f), glm::vec3(0.0f), {0}, {0.0f}},
		{glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f), glm::vec3(0.0f), {0}, {0.0f}},
		{glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f), glm::vec3(0.0f), {0}, {0.0f}}
	};
	std::vector<unsigned int> indices
	{
		// front
		0, 1, 2,
		2, 3, 0,
		// back
		6, 5, 4,
		4, 7, 6,
		// left
		3, 7, 4,
		4, 0, 3,
		// right
		1, 5, 6,
		6, 2, 1,
		// up
		3, 2, 6,
		6, 7, 3,
		// 下面
		1, 0, 4,
		4, 5, 1
	};
	return std::make_unique<Mesh>(textures, vertices, indices);
}
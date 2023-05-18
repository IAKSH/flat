#include "glm/ext/matrix_transform.hpp"
#include "object.hpp"
#include "pipe.hpp"

flat::RenableObject::RenableObject() = default;
flat::RenableObject::~RenableObject() = default;

// flush using default camera
void flat::RenableObject::flush_to_screen() const
{
    flush_to_screen(*default_camera);
}

const flat::opengl::RectangleVertexArray<flat::opengl::BufferType::Dynamic>& flat::RenableObject::get_rect_vao() const
{
    return rect;
}
#pragma once

#include "../physics.hpp"
#include "../../Misc/logger.hpp"
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glm/ext/matrix_clip_space.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

namespace flat::opengl
{
    class Camera : virtual public flat::Rotatable
    {
    private:
        float fov,zoom;
        int view_width,view_height;

    public:
        Camera();
        Camera(float w,float h);
        ~Camera();

        float get_zoom() {return zoom;}
        float get_fov() {return fov;}
        glm::mat4 get_matrix() const;
        void set_zoom(float val);
        void set_fov(float val);
    };
}
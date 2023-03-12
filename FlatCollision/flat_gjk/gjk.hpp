#include "../collision.hpp"

#include <array>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace flat::gjk
{
    class Hitbox2D : public flat::Hitbox2D
    {
    private:
        float x,y,r,w,h;
        int gjKIterCount = 0;
		int gjk (const glm::vec2 * vertices1, size_t count1,const glm::vec2 * vertices2, size_t count2);
		float Perturbation();
		float dotProduct (glm::vec2 a, glm::vec2 b) { return a.x * b.x + a.y * b.y; }
		float lengthSquared (glm::vec2 v) { return v.x * v.x + v.y * v.y; }
		glm::vec2 subtract (glm::vec2 a, glm::vec2 b) { a.x -= b.x; a.y -= b.y; return a; }
		glm::vec2 negate (glm::vec2 v) { v.x = -v.x; v.y = -v.y; return v; }
		glm::vec2 perpendicular (glm::vec2 v) { glm::vec2 p = { v.y, -v.x }; return p; }
		glm::vec2 tripleProduct (glm::vec2 a, glm::vec2 b, glm::vec2 c);
		glm::vec2 averagePoint (const glm::vec2 * vertices, size_t count);
		glm::vec2 support (const glm::vec2 * vertices1, size_t count1,const glm::vec2 * vertices2, size_t count2, glm::vec2 d);
		glm::vec2 Jostle(glm::vec2 a);
		std::array<glm::vec2,4> getHitboxVertexCoords(flat::Hitbox2D& obj);
		size_t indexOfFurthestPoint (const glm::vec2 * vertices, size_t count, glm::vec2 d);
    
    public:
        Hitbox2D();
        virtual ~Hitbox2D() override;
        virtual bool checkHit(flat::Hitbox2D& hitbox) override;
        virtual float const getPosX() override;
        virtual float const getPosY() override;
        virtual float const getRotate() override;
        virtual float const getWidth() override;
        virtual float const getHeight() override;
        virtual void setPosX(float posX) override;
        virtual void setPosY(float posY) override;
        virtual void setRotate(float rotate) override;
        virtual void setWidth(float width) override;
        virtual void setHeight(float height) override;
    };
}
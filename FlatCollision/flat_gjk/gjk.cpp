#include "gjk.hpp"

flat::gjk::Hitbox2D::Hitbox2D()
    : x(0.0f),y(0.0f),r(0.0f),w(0.5f),h(0.5f)
{
}

flat::gjk::Hitbox2D::~Hitbox2D()
{
}

std::array<glm::vec2, 4> flat::gjk::Hitbox2D::getHitboxVertexCoords(flat::Hitbox2D& obj)
{
	auto w = obj.getWidth();
	auto h = obj.getHeight();
	auto x = obj.getPosX();
	auto y = obj.getPosY();

	// original vertex
	glm::vec4 v1(-w / 2, h / 2, 0.0f, 1.0f);
	glm::vec4 v2(-w / 2, -h / 2, 0.0f, 1.0f);
	glm::vec4 v3(w / 2, -h / 2, 0.0f, 1.0f);
	glm::vec4 v4(w / 2, h / 2, 0.0f, 1.0f);

	// transform
	glm::mat4 rotateMat = glm::rotate(glm::mat4(1.0f), obj.getRotate(), glm::vec3(0.0f, 0.0f, 1.0f));
	v1 = rotateMat * v1;
  	v2 = rotateMat * v2;
  	v3 = rotateMat * v3;
  	v4 = rotateMat * v4;

	glm::mat4 transMat = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0.0f));
  	v1 = transMat * v1;
  	v2 = transMat * v2;
  	v3 = transMat * v3;
  	v4 = transMat * v4;

	std::array<glm::vec2,4> buffer
	{
		glm::vec2(v1.x,v1.y),
		glm::vec2(v2.x,v2.y),
		glm::vec2(v3.x,v3.y),
		glm::vec2(v4.x,v4.y)
	};

	return buffer;
}

bool flat::gjk::Hitbox2D::checkHit(flat::Hitbox2D& hitbox)
{
	auto vertices1 = getHitboxVertexCoords(*this);
	auto vertices2 = getHitboxVertexCoords(hitbox);

	size_t count1 = vertices1.size();
	size_t count2 = vertices2.size();

	while (1)
	{
		glm::vec2 a[vertices1.size()];
		glm::vec2 b[vertices2.size()];

		for (size_t i = 0; i < count1; ++i)
			a[i] = Jostle(vertices1[i]);
		for (size_t i = 0; i < count2; ++i)
			b[i] = Jostle(vertices2[i]);

		int collisionDetected = gjk(a, count1, b, count2);
		if (!collisionDetected)
		{
			gjKIterCount = 0;
			return false;
		}
		else
		{
			gjKIterCount = 0;
			return true;
		}
	}
}

glm::vec2 flat::gjk::Hitbox2D::tripleProduct(glm::vec2 a, glm::vec2 b, glm::vec2 c)
{

	glm::vec2 r;

	float ac = a.x * c.x + a.y * c.y; // perform a.dot(c)
	float bc = b.x * c.x + b.y * c.y; // perform b.dot(c)

	// perform b * a.dot(c) - a * b.dot(c)
	r.x = b.x * ac - a.x * bc;
	r.y = b.y * ac - a.y * bc;
	return r;
}

glm::vec2 flat::gjk::Hitbox2D::averagePoint(const glm::vec2 *vertices, size_t count)
{
	glm::vec2 avg(0.f, 0.f);
	for (size_t i = 0; i < count; i++)
	{
		avg.x += vertices[i].x;
		avg.y += vertices[i].y;
	}
	avg.x /= count;
	avg.y /= count;
	return avg;
}

size_t flat::gjk::Hitbox2D::indexOfFurthestPoint(const glm::vec2 *vertices, size_t count, glm::vec2 d)
{
	float maxProduct = dotProduct(d, vertices[0]);
	size_t index = 0;
	for (size_t i = 1; i < count; i++)
	{
		float product = dotProduct(d, vertices[i]);
		if (product > maxProduct)
		{
			maxProduct = product;
			index = i;
		}
	}
	return index;
}

glm::vec2 flat::gjk::Hitbox2D::support(const glm::vec2 *vertices1, size_t count1, const glm::vec2 *vertices2, size_t count2, glm::vec2 d)
{

	// get furthest point of first body along an arbitrary direction
	size_t i = indexOfFurthestPoint(vertices1, count1, d);

	// get furthest point of second body along the opposite direction
	size_t j = indexOfFurthestPoint(vertices2, count2, negate(d));

	// subtract (Minkowski sum) the two points to see if bodies 'overlap'
	return subtract(vertices1[i], vertices2[j]);
}

int flat::gjk::Hitbox2D::gjk(const glm::vec2 *vertices1, size_t count1, const glm::vec2 *vertices2, size_t count2)
{
	size_t index = 0; // index of current vertex of simplex
	glm::vec2 a, b, c, d, ao, ab, ac, abperp, acperp, simplex[3];

	glm::vec2 position1 = averagePoint(vertices1, count1); // not a CoG but
	glm::vec2 position2 = averagePoint(vertices2, count2); // it's ok for GJK )

	// initial direction from the center of 1st body to the center of 2nd body
	d = subtract(position1, position2);

	// if initial direction is zero – set it to any arbitrary axis (we choose X)
	if ((d.x == 0) && (d.y == 0))
		d.x = 1.f;

	// set the first support as initial point of the new simplex
	a = simplex[0] = support(vertices1, count1, vertices2, count2, d);

	if (dotProduct(a, d) <= 0)
		return 0; // no collision

	d = negate(a); // The next search direction is always towards the origin, so the next search direction is negate(a)

	while (1)
	{
		gjKIterCount++;

		a = simplex[++index] = support(vertices1, count1, vertices2, count2, d);

		if (dotProduct(a, d) <= 0)
			return 0; // no collision

		ao = negate(a); // from point A to Origin is just negative A

		// simplex has 2 points (a line segment, not a triangle yet)
		if (index < 2)
		{
			b = simplex[0];
			ab = subtract(b, a);		   // from point A to B
			d = tripleProduct(ab, ao, ab); // normal to AB towards Origin
			if (lengthSquared(d) == 0)
				d = perpendicular(ab);
			continue; // skip to next iteration
		}

		b = simplex[1];
		c = simplex[0];
		ab = subtract(b, a); // from point A to B
		ac = subtract(c, a); // from point A to C

		acperp = tripleProduct(ab, ac, ac);

		if (dotProduct(acperp, ao) >= 0)
		{

			d = acperp; // new direction is normal to AC towards Origin
		}
		else
		{

			abperp = tripleProduct(ac, ab, ab);

			if (dotProduct(abperp, ao) < 0)
				return 1; // collision

			simplex[0] = simplex[1]; // swap first element (point C)

			d = abperp; // new direction is normal to AB towards Origin
		}

		simplex[1] = simplex[2]; // swap element in the middle (point B)
		--index;
	}

	return 0;
}

float flat::gjk::Hitbox2D::Perturbation()
{
	return ((float)rand() / (float)RAND_MAX) * FLT_EPSILON * 100.0f * ((rand() % 2) ? 1.0f : -1.0f);
}

glm::vec2 flat::gjk::Hitbox2D::Jostle(glm::vec2 a)
{
	glm::vec2 b;
	b.x = a.x + Perturbation();
	b.y = a.y + Perturbation();
	return b;
}

float const flat::gjk::Hitbox2D::getPosX()
{
    return x;
}

float const flat::gjk::Hitbox2D::getPosY()
{
    return y;
}

float const flat::gjk::Hitbox2D::getRotate()
{
    return r;
}

float const flat::gjk::Hitbox2D::getWidth()
{
    return w;
}

float const flat::gjk::Hitbox2D::getHeight()
{
    return h;
}

void flat::gjk::Hitbox2D::setPosX(float posX)
{
    x = posX;
}

void flat::gjk::Hitbox2D::setPosY(float posY)
{
    y = posY;
}

void flat::gjk::Hitbox2D::setRotate(float rotate)
{
    r = rotate;
}

void flat::gjk::Hitbox2D::setWidth(float width)
{
    w = width;
}

void flat::gjk::Hitbox2D::setHeight(float height)
{
    h = height;
}
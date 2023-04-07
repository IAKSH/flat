#include "collision_detect.hpp"

#include <array>
#include <cfloat>

namespace ni::flat
{
    static int iter_count = 0;

    struct Vec2
    {
        float x,y,z;

        Vec2()
            : x{0.0f},y{0.0f},z{0.0f}
        {
        }
        Vec2(float x, float y)
			: x{x}, y(y)
		{
		}
        ~Vec2() = default;
    };

    Vec2 subtract(Vec2 a, Vec2 b)
	{
		a.x -= b.x;
		a.y -= b.y;
		return a;
	}

	Vec2 negate(Vec2 v)
	{
		v.x = -v.x;
		v.y = -v.y;
		return v;
	}

	Vec2 perpendicular(Vec2 v)
	{
		Vec2 p = { v.y, -v.x };
		return p;
	}

	float dotProduct(Vec2 a, Vec2 b)
	{
		return a.x * b.x + a.y * b.y;
	}

	float lengthSquared(Vec2 v)
	{
		return v.x * v.x + v.y * v.y;
	}

	Vec2 tripleProduct(Vec2 a, Vec2 b, Vec2 c)
	{
		Vec2 r;

		float ac = a.x * c.x + a.y * c.y; // perform a.dot(c)
		float bc = b.x * c.x + b.y * c.y; // perform b.dot(c)

		// perform b * a.dot(c) - a * b.dot(c)
		r.x = b.x * ac - a.x * bc;
		r.y = b.y * ac - a.y * bc;
		return r;
	}

	Vec2 averagePoint(const Vec2* vertices, size_t count)
	{
		Vec2 avg = { 0.f, 0.f };
		for (size_t i = 0; i < count; i++) {
			avg.x += vertices[i].x;
			avg.y += vertices[i].y;
		}
		avg.x /= count;
		avg.y /= count;
		return avg;
	}

	size_t indexOfFurthestPoint(const Vec2* vertices, size_t count, Vec2 d)
	{
		float maxProduct = dotProduct(d, vertices[0]);
		size_t index = 0;
		for (size_t i = 1; i < count; i++) {
			float product = dotProduct(d, vertices[i]);
			if (product > maxProduct) {
				maxProduct = product;
				index = i;
			}
		}
		return index;
	}

	Vec2 support(const Vec2* vertices1, size_t count1, const Vec2* vertices2, size_t count2, Vec2 d)
	{
		// get furthest point of first body along an arbitrary direction
		size_t i = indexOfFurthestPoint(vertices1, count1, d);

		// get furthest point of second body along the opposite direction
		size_t j = indexOfFurthestPoint(vertices2, count2, negate(d));

		// subtract (Minkowski sum) the two points to see if bodies 'overlap'
		return subtract(vertices1[i], vertices2[j]);
	}

	int gjk(const Vec2* vertices1, size_t count1, const Vec2* vertices2, size_t count2)
	{
		size_t index = 0; // index of current vertex of simplex
		Vec2 a, b, c, d, ao, ab, ac, abperp, acperp, simplex[3];

		Vec2 position1 = averagePoint(vertices1, count1); // not a CoG but
		Vec2 position2 = averagePoint(vertices2, count2); // it's ok for GJK )

		// initial direction from the center of 1st body to the center of 2nd body
		d = subtract(position1, position2);

		// if initial direction is zero ¡§C set it to any arbitrary axis (we choose X)
		if ((d.x == 0) && (d.y == 0))
			d.x = 1.f;

		// set the first support as initial point of the new simplex
		a = simplex[0] = support(vertices1, count1, vertices2, count2, d);

		if (dotProduct(a, d) <= 0)
			return 0; // no collision

		d = negate(a); // The next search direction is always towards the origin, so the next search direction is negate(a)

		while (1) {
			iter_count++;

			a = simplex[++index] = support(vertices1, count1, vertices2, count2, d);

			if (dotProduct(a, d) <= 0)
				return 0; // no collision

			ao = negate(a); // from point A to Origin is just negative A

			// simplex has 2 points (a line segment, not a triangle yet)
			if (index < 2) {
				b = simplex[0];
				ab = subtract(b, a); // from point A to B
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

			if (dotProduct(acperp, ao) >= 0) {

				d = acperp; // new direction is normal to AC towards Origin

			}
			else {

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

	float Perturbation()
	{
		return ((float)rand() / (float)RAND_MAX) * FLT_EPSILON * 100.0f * ((rand() % 2) ? 1.0f : -1.0f);
	}

	Vec2 Jostle(Vec2 a)
	{
		Vec2 b;
		b.x = a.x + Perturbation();
		b.y = a.y + Perturbation();
		return b;
	}

	bool collisionCheckGJK(float x1, float y1, float w1, float h1,float r1, float x2, float y2, float w2, float h2, float r2)
	{
        float dw1 = (w1 / 2) * abs(cos(r1)) + (h1 / 2) * abs(sin(r1));
        float dh1 = (h1 / 2) * abs(cos(r1)) + (w1 / 2) * abs(sin(r1));
        float dw2 = (w2 / 2) * abs(cos(r2)) + (h2 / 2) * abs(sin(r2));
        float dh2 = (h2 / 2) * abs(cos(r2)) + (w2 / 2) * abs(sin(r2));

        std::array<Vec2, 4> rotatedVertices1 = {Vec2{x1 - dh1,y1 - dw1},Vec2{x1 + dw1,y1 - dh1},Vec2{x1 + dh1,y1 + dw1},Vec2{x1 - dw1,y1 + dh1}};
        std::array<Vec2, 4> rotatedVertices2 = {Vec2{x2 - dh2,y2 - dw2},Vec2{x2 + dw2,y2 - dh2},Vec2{x2 + dh2,y2 + dw2},Vec2{x2 - dw2,y2 + dh2}};

		size_t count1 = rotatedVertices1.size();
		size_t count2 = rotatedVertices2.size();

		while (1)
		{
			Vec2 a[rotatedVertices1.size()];
			Vec2 b[rotatedVertices2.size()];

			for (size_t i = 0; i < count1; ++i)
				a[i] = Jostle(rotatedVertices1[i]);
			for (size_t i = 0; i < count2; ++i)
				b[i] = Jostle(rotatedVertices2[i]);

			int collisionDetected = gjk(a, count1, b, count2);
			if (!collisionDetected)
			{
				iter_count = 0;
				return false;
			}
			else
			{
				iter_count = 0;
				return true;
			}
		}

		return 0;
	}
}

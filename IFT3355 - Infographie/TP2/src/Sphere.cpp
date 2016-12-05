#include "Sphere.h"
#include "tools.h"

/* Sphere constructor. There is not need to store the center or radius because we will transform the ray using the
transformation matrix. This way, we "enter the sphere's world" where the center is (0, 0, 0) and the radius is 1. */
Sphere::Sphere(vec3 position, vec3 orientation, vec3 scaling, Material* material)
	: Geometry(position, orientation, scaling, material)
{

}

std::unique_ptr<struct Intersection> Sphere::intersect(const struct Ray& ray, decimal &currentdepth) const
{
	/* Let's transform the ray's origin/direction using the inverse of the transformation matrix. It is way simpler
	this way to take transformations into account. */
	vec3 transformedRayOrigin    = vec3(_transformationMatrixInverse * vec4(ray.origin, 1.0f));		// e
	vec3 transformedRayDirection = vec3(_transformationMatrixInverse * vec4(ray.direction, 0.0f));	// d

	/* The following equations come from Fundamentals of Computer Graphics, 3rd Edition, Chapter 4 (Ray Tracing),
	section 4.4.1 (Ray-Sphere Intersection), pages 76-77. In the right hand-side comments, a dot ('.') means
	'dot product'. */
	float a = glm::dot(transformedRayDirection, transformedRayDirection);	// d.d
	float b = 2 * glm::dot(transformedRayDirection, transformedRayOrigin);	// 2d.(e-c) but here c=(0, 0, 0)
	float c = glm::dot(transformedRayOrigin, transformedRayOrigin) - 1; // (e-c).(e-c) - R^2

	float t0, t1; // will hold solutions of the quadratic if calculable

	if (!Tools::calculateQuadratic(a, b, c, t0, t1))
	{
		// Quadratic can't be solve: the ray and the sphere don't intersect.

		return nullptr;
	}
	else if (0 > t1)
	{
		/* t1 < 0 means that the intersection is behind the scene. Don't forget that Tools:calculateQuadratic() puts
		the smallest value in t0 and the biggest in t1, so if t1 < 0, automatically t0 < 0; */

		return nullptr;
	}

	/* Let's calculate the intersection point. If t0 < 0, we must use t1. */
	vec3 intersectionPoint = transformedRayOrigin + ((double) ((0 > t0) ? t1 : t0)) * transformedRayDirection;

	vec3 intersectionNormal = glm::normalize(intersectionPoint);

	if (glm::distance(intersectionPoint, ray.origin) > currentdepth)
	{
		/* If distance > currentDepth -> let's exit. */

		return nullptr;
	}

	/* Now calculating uv coordinates using the course's notes (chap. 6, slide 17). Swap 'y' and 'z'. */
	float u, v;
	float z = intersectionPoint.z;

	if (fabs(z) < 0.0001) // epsilon
	{
		u = 0;
	}
	else
	{
		/* Common part, no matter if z>0 or z<0. */
		u = (float) (acos(intersectionPoint.x / sqrt(pow(intersectionPoint.x, 2) + pow(z, 2)))
			/ (2 * glm::pi<float>()));

		if (z < 0)
		{
			u = 1 - u;
		}
	}

	v = (float) acos(intersectionPoint.y) / glm::pi<float>(); // acos(y/r)/pi but here r = 1.

	vec2 uvCoordinates = vec2(u, v);

	intersectionNormal = glm::normalize(vec3(glm::transpose(_transformationMatrixInverse)
		* glm::vec4(intersectionNormal, 0.0f)));

	intersectionPoint = vec3(_transformationMatrixInverse * vec4(intersectionPoint, 1.0f));

	std::unique_ptr<struct Intersection> intersection(new Intersection{ray, intersectionPoint, intersectionNormal, 
		uvCoordinates, _material});

	return std::move(intersection);
}
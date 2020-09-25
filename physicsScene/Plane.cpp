#include "Plane.h"
#include <Gizmos.h>


Plane::Plane()
	: PhysicsObject(PLANE)
{
	m_normal = glm::vec2(0.0f, 1.0f);
	m_distanceToOrigin = 0.0f;
}

Plane::Plane(glm::vec2 normal, float distance)
	: PhysicsObject(PLANE)
{
	m_normal = glm::normalize(normal);
	m_distanceToOrigin = distance;
}

/**
 * draws the plane
 */
void Plane::makeGizmo()
{
	float lineSegmentLength = 300;
	glm::vec2 centerPoint = m_normal * m_distanceToOrigin;
	glm::vec2 parallel(m_normal.y, -m_normal.x);
	glm::vec4 color(1, 1, 1, 1);
	glm::vec2 start = centerPoint + (parallel * lineSegmentLength);
	glm::vec2 end = centerPoint - (parallel * lineSegmentLength);
	aie::Gizmos::add2DLine(start, end, color);
}

/**
 * resolves plane to sphere collsion
 */
void Plane::resolveCollision(Rigidbody* actor2, glm::vec2 contact)
{
	glm::vec2 normal =  m_normal;
	glm::vec2 relativeVelocity = actor2->getVelocity();

	float elacticity = 1;

	float j = glm::dot(-(1 + elacticity) * (relativeVelocity), normal) / (1 / actor2->getMass());

	glm::vec2 force = normal * j;
	actor2->applyForce(force,contact - actor2->getPosition());
}



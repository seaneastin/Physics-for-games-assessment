#include "Sphere.h"
#include <Gizmos.h>
Sphere::Sphere(glm::vec2 position, glm::vec2 velocity, float mass, float radius, glm::vec4 colour) : Rigidbody(SPHERE, position, velocity, 0,  mass)
{
	m_radius = radius;
	m_colour = colour;
	m_moment = 0.5f * m_mass * m_radius * m_radius;
}

void Sphere::makeGizmo()
{

	aie::Gizmos::add2DCircle(m_position, m_radius, 12, m_colour);

	glm::vec2 end = glm::vec2(std::cos(m_rotation), std::sin(m_rotation)) * m_radius;
	/*aie::Gizmos::add2DLine(m_position, m_position + end, glm::vec4(1, 1, 1, 1));*/
}

bool Sphere::checkCollision(PhysicsObject* p0ther)
{
	Sphere* otherSphere = dynamic_cast<Sphere*>(p0ther);
	if (otherSphere) {
		return glm::distance(m_position, otherSphere->getPosition()) < m_radius + otherSphere->getRadius();
	}
}

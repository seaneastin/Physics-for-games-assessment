#include "Rigidbody.h"

Rigidbody::Rigidbody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float rotation, float mass)
	: PhysicsObject(shapeID)
{
	m_position = position;
	m_velocity = velocity;
	m_rotation = rotation;
	m_mass = mass;
}

Rigidbody::~Rigidbody()
{

}

void Rigidbody::fixedUpdate(glm::vec2 gravity, float timeStep)
{


	applyForce(gravity * m_mass * timeStep, m_position);

	if (glm::length(m_velocity) < 0.1f)
	{
		m_velocity = glm::vec2(0.0f, 0.0f);
	}

	if (glm::abs(m_angularVelocity) < 0.1f)
	{
		m_angularVelocity = 0;
	}

	m_velocity -= m_velocity * m_linearDrag * timeStep;


	m_position += m_velocity * timeStep;
	m_angularVelocity -= m_angularVelocity * m_angularDrag * timeStep;
	m_rotation += m_angularVelocity * timeStep;
	


}

void Rigidbody::debug()
{
}

void Rigidbody::applyForce(glm::vec2 force, glm::vec2 pos)
{
	m_velocity += force / m_mass;
	m_angularVelocity += (force.y * pos.x - force.x * pos.y) / (m_moment);
}

void Rigidbody::applyForceToActor(Rigidbody* otherActor, glm::vec2 force)
{
	otherActor->applyForce(force, otherActor->m_position);
	applyForce(-force, m_position);
}

void Rigidbody::resolveCollision(Rigidbody* actor2, glm::vec2 contact, glm::vec2* collisionNormal)
{
	glm::vec2 normal = glm::normalize(actor2->getPosition() - m_position);
	
	glm::vec2 perpendicular(normal.y, -normal.x);
	
	//look at github for fixing this
	float radius = glm::dot(contact - m_position, -perpendicular);
	float otherradius = glm::dot(contact - actor2->m_position, perpendicular);


	float velocity = glm::dot(m_velocity, normal) - radius * m_angularVelocity;
	float otherVelocity = glm::dot(actor2->m_velocity, normal) + otherradius * actor2->m_angularVelocity;


	//they're moving apart so ignore the collsion
	if (velocity <= otherVelocity) return;


	float mass = 1.0f / (1.0f / m_mass + (radius * radius) / m_moment);
	float otherMass = 1.0f / (1.0f / actor2->m_mass + (otherradius * otherradius) / actor2->m_moment);
	//find the average elasticity
	float elacticity = (m_elasticity + actor2->m_elasticity) / 2;

	//find the impulse
	float j = (1.0f + elacticity) * mass * otherMass / (mass + otherMass) * (velocity - otherVelocity);
	// find the force;
		glm::vec2 force = normal * j;
		actor2->applyForce(force, contact - actor2->m_position);
		applyForce(-force, contact - m_position);
}

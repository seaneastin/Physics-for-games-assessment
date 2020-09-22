#pragma once
#include "PhysicsObject.h"
class Rigidbody : public PhysicsObject
{
public:
	Rigidbody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float rotation, float mass);
	~Rigidbody();

	virtual void fixedUpdate(glm::vec2 gravity, float timeStep);
	virtual void debug();
	void applyForce(glm::vec2 force, glm::vec2 pos);
	void applyForceToActor(Rigidbody* otherActor, glm::vec2 force);


	virtual bool checkCollision(PhysicsObject* p0ther) = 0;
	void resolveCollision(Rigidbody* actor2, glm::vec2 contact, glm::vec2* collisionNormal=nullptr);

	float getrotation() { return m_rotation; }



	glm::vec2 getPosition() { return m_position; }
	float getRotatio9n() { return m_rotation; }
	glm::vec2 getVelocity() { return m_velocity; }
	float getMass() { return m_mass; }
	float getLinearDrag() { return m_linearDrag; }
	void setLinearDrag(float value) { m_linearDrag = value; }
	float getAngularDrag() { return m_angularDrag; }
	void setAngularDrag(float value) { m_angularDrag = value; }
	float getElasticity() { return m_elasticity; }
	void setElasticity(float value) { m_elasticity = value; }

protected:
	glm::vec2 m_position;
	glm::vec2 m_velocity;
	float m_angularVelocity;
	float m_mass;
	float m_moment;
	float m_rotation; //2D so we only need a single float to represent our rotation

	float m_linearDrag = 0.3f;
	float m_angularDrag = 0.3f;
	float m_elasticity = 0.5f;
};


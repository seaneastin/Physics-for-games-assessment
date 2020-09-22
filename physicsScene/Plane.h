#pragma once
#include "PhysicsObject.h"
#include "Rigidbody.h"
class Plane : public PhysicsObject
{
public:
	Plane();
	Plane(glm::vec2 normal, float distance);
	~Plane() {}

	virtual void fixedUpdate(glm::vec2 gravity, float timeStep) {}
	virtual void debug() {}
	virtual void makeGizmo();
	virtual void resetPoistion() {}

	void resolveCollision(Rigidbody* actor2, glm::vec2 contact); 


	glm::vec2 getNormal() { return m_normal; };
	float getDistance() { return m_distanceToOrigin; }

protected:
	glm::vec2 m_normal;
	float m_distanceToOrigin;

};


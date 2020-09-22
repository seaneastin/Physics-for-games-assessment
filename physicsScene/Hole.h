#pragma once
#include "Rigidbody.h"
class Hole : public Rigidbody
{
	Hole(glm::vec2 position, glm::vec2 velocity, float mass, float radius, glm::vec4 colour);
	~Hole () {}

	virtual void makeGizmo();

	float getRadius() { return m_radius; }
	glm::vec4 getColour() { return m_colour; }

protected:
	float m_radius;
	glm::vec4 m_colour;
};


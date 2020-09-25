#pragma once
#include "glm\ext.hpp"

enum ShapeType {
	PLANE = 0,
	SPHERE,
	SHAPE_COUNT
};
/**
 * a pure virutal class
 */
class PhysicsObject
{
protected:
	PhysicsObject(ShapeType a_shapeID) : m_shapeID(a_shapeID) {}

public:
	virtual void fixedUpdate(glm::vec2 gravity, float timeStep) = 0;
	virtual void debug() = 0;
	virtual void makeGizmo() = 0;
	virtual void resetPosition() {};

	ShapeType geteShhapeID() { return m_shapeID; }

protected:
	ShapeType m_shapeID;
};


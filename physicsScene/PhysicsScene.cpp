#include "PhysicsScene.h"
#include <list>
#include "Sphere.h"
#include "Plane.h"
#include "Rigidbody.h"
PhysicsScene::PhysicsScene()
{
	m_timestep = 0.01f;
	m_gravity = { 0,0 };
}

PhysicsScene::~PhysicsScene()
{
	for (auto pActor : m_actors)
	{
		delete pActor;
	}
}
/**
 * adds an actor to the scene
 */
void PhysicsScene::addActor(PhysicsObject* actor)
{
	m_actors.push_back(actor);
}


/**
 * removes an actor from the scene
 */
void PhysicsScene::removeActor(PhysicsObject* actor)
{
	for (auto i = m_actors.begin(); i != m_actors.end(); i++)
	{
		if (*i == actor)
		{
			m_actors.erase(i);
		}
	}
}


/**
 * updates physics at a fixed time step
 */
void PhysicsScene::update(float dt)
{

	//update physics at a fixed time step

	static float accumulatedTime = 0.0f;

	accumulatedTime += dt;

	while (accumulatedTime >= m_timestep) {


		for (auto pActor : m_actors)
		{
			pActor->fixedUpdate(m_gravity, m_timestep);
		}
		accumulatedTime -= m_timestep;


		//check for collisoins
		checkForCollision();

	}

}

/**
 * draws the actors added to the scene
 */
void PhysicsScene::updateGizmos()
{
	for (auto pActor : m_actors) {
		pActor->makeGizmo();
	}
}

void PhysicsScene::debugScene()
{

}

typedef bool(*fn)(PhysicsObject*, PhysicsObject*);

static fn collistionFunctions[] =
{
	PhysicsScene::plane2Plane, PhysicsScene::plane2Sphere,
	PhysicsScene::sphere2Plane, PhysicsScene::sphere2Sphere,
};

void PhysicsScene::checkForCollision()
{
	int actorCount = m_actors.size();

	//need to check for collisions against all objects execpt fort this one
	for (int outer = 0; outer < actorCount - 1; outer++)
	{
		for (int inner = outer + 1; inner < actorCount; inner++)
		{
			PhysicsObject* object1 = m_actors[outer];
			PhysicsObject* object2 = m_actors[inner];

			int shapeID1 = object1->geteShhapeID();
			int shapeID2 = object2->geteShhapeID();


			int functionID = (shapeID1 * SHAPE_COUNT) + shapeID2;
			fn collisionFunctionPTR = collistionFunctions[functionID];

			if (collisionFunctionPTR != nullptr)
			{
				//did a collision occur?
				collisionFunctionPTR(object1, object2);
			}
		}
	}

}

bool PhysicsScene::plane2Plane(PhysicsObject* object1, PhysicsObject* object2)
{
	Plane* plane1 = dynamic_cast<Plane*>(object1);
	Plane* plane2 = dynamic_cast<Plane*>(object2);
	if (plane1 != nullptr && plane2 != nullptr)
	{
		return plane1->getNormal().x != plane2->getNormal().x || plane1->getNormal().y != plane2->getNormal().y;
	}
	return false;
}

bool PhysicsScene::plane2Sphere(PhysicsObject* object1, PhysicsObject* object2)
{
	sphere2Plane(object2, object1);
	return false;
}

bool PhysicsScene::sphere2Plane(PhysicsObject* object1, PhysicsObject* object2)
{
	Sphere* sphere = dynamic_cast<Sphere*>(object1);
	Plane* plane = dynamic_cast<Plane*>(object2);
	if (sphere != nullptr && plane != nullptr)
	{
		// calculate distance from sphere surface to plane surface
		float sphereToPlaneaDistance =
			glm::dot(sphere->getPosition(), plane->getNormal()) - plane->getDistance();
		// flip the normal if behind the plnae
		glm::vec2 collisionNormal = plane->getNormal();
		if (sphereToPlaneaDistance < 0) {
			collisionNormal *= -1;
			sphereToPlaneaDistance *= -1;
		}

		sphereToPlaneaDistance -= sphere->getRadius();
		if (sphereToPlaneaDistance <= 0) {
			glm::vec2 contact = sphere->getPosition() + (collisionNormal * -sphere->getRadius());
			plane->resolveCollision(sphere, contact);
			return true;
		}
	}
	return false;
}

bool PhysicsScene::sphere2Sphere(PhysicsObject* object1, PhysicsObject* object2)
{
	Sphere* sphere1 = dynamic_cast<Sphere*>(object1);
	Sphere* sphere2 = dynamic_cast<Sphere*>(object2);
	if (sphere1 != nullptr && sphere2 != nullptr) {
		if (glm::distance(sphere1->getPosition(), sphere2->getPosition()) < sphere1->getRadius() + sphere2->getRadius())
		{
			glm::vec2 contact = (sphere1->getPosition() + sphere2->getPosition()) * 0.5f;
			sphere1->resolveCollision(sphere2, contact);
	    }
	}
	return false;
}

#include "physicsSceneApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "PhysicsScene.h"
#include <Gizmos.h>
#include "Sphere.h"
#include "Plane.h"


physicsSceneApp::physicsSceneApp() {

}

physicsSceneApp::~physicsSceneApp() {

}

bool physicsSceneApp::startup() {
	
	// increase the 2D line countr to mazimize the number of objects we can draw
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);



	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	glm::vec2 gravity = glm::vec2(0, 0);

	m_physicsScene = new PhysicsScene();
	m_physicsScene->setGravity(gravity);
	m_physicsScene->setTimeStep(0.01f);

	glm::vec2 initialvelocity = glm::vec2(0.0f, 0.0f);
	glm::vec2 initialposition = glm::vec2(-70.0f, 60.0f);
	
	Sphere* ball = new Sphere(glm::vec2(-10.0f, 1.0f), glm::vec2(5000.0f, 0.0f), 1.0f, 2.0f, glm::vec4(128, 0, 128, 1));
	
	//setupContinuousDemo(initialposition, initialvelocity, gravity.y);
	m_physicsScene->addActor(ball);
	createSpheresintriangle(100, glm::vec2(0.0f, 1.0f), 1.0f, 2.0f);

	Plane* floor = new Plane(glm::vec2(0.0f, 60.0f), -50.0f);
	Plane* wall = new Plane(glm::vec2(40.0f, 0.0f), 80.0f);
	Plane* wall2 = new Plane(glm::vec2(40.0f, 0.0f), -40.0f);
	Plane* floor2 = new Plane(glm::vec2(0.0f, 60.0f), 50.0f);
	m_physicsScene->addActor(floor);
	m_physicsScene->addActor(floor2);
	m_physicsScene->addActor(wall);
	m_physicsScene->addActor(wall2);


	return true;
}

void physicsSceneApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

void physicsSceneApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	aie::Gizmos::clear(); 

	m_physicsScene->update(deltaTime);
	m_physicsScene->updateGizmos();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void physicsSceneApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	static float aspectRatio = 16 / 9.f;
	aie::Gizmos::draw2D(glm::ortho<float>(-100, 100, -100 / aspectRatio, 100 / aspectRatio, -1.0f, 1.0f));


	
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}

void physicsSceneApp::setupContinuousDemo(glm::vec2 startPos, glm::vec2 velocity, float gravity)
{
	float time = 0.0f;
	float timeStep = 0.5f;
	float radius = 1.0f;
	int segments = 12;
	glm::vec4 color = glm::vec4(1, 1, 0, 1);
	glm::vec2 endPos;
	while (time <= 5)
	{
		//calculate the x, y position of the projectile at time

		float x = startPos.x + velocity.x * time;
		float y = (startPos.y + velocity.y * time) + (.5f * gravity * (time * time));




		endPos = glm::vec2(x, y);

		aie::Gizmos::add2DCircle(endPos, radius, segments, color);
		time += timeStep;
	}
}
/**
 * allows you to make spheres spawn in a rack
 */
void physicsSceneApp::createSpheresintriangle(int spherestocreate,glm::vec2 positionm, float mass, float radius)
{	
	glm::vec2 firstSphereInRow = positionm; //keeps track of first sphere in the row
	int howmanyinarow = 1; //keeps track how many in a row
	int sphereinarow = 1; //keeps track of spheres made already
	for (int i = 0; i < spherestocreate; i++)
	{

			Sphere* sphere = new Sphere(positionm, glm::vec2(0.0f, 0.0f), mass, radius, glm::vec4(1.0f, 1.0f, 1.0f,1.0f));
			m_physicsScene->addActor(sphere);
			//keeps track of 1st sphere in the row
			if (sphereinarow == 1)
			{
				firstSphereInRow = glm::vec2(positionm.x, positionm.y);
			}
			//if the number of spheres being created is greater than 1 it will offset the position of the next sphere
			if (howmanyinarow > 1)
			{
				positionm = glm::vec2(positionm.x, positionm.y - 4.0f);
			}

		

			//if the row being created is done then it will set up another row3
			if (sphereinarow >= howmanyinarow)
			{

				positionm = glm::vec2(positionm.x + 5, firstSphereInRow.y + 2);
				howmanyinarow++;
				sphereinarow = 1;
			}
			else
			{
				sphereinarow++;
			}
			



		
	}
}

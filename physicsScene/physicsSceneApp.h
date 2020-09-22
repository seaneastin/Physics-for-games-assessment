#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "PhysicsScene.h"

class physicsSceneApp : public aie::Application {
public:

	physicsSceneApp();
	virtual ~physicsSceneApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	void setupContinuousDemo(glm::vec2 startPos, glm::vec2 velocity, float gravity);
	void createSpheresintriangle(int spherestocreate,glm::vec2 positionm, float mass, float radius);
protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
	PhysicsScene*       m_physicsScene;
};
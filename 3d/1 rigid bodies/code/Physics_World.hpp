#pragma once
#include <memory>
#include <vector>
#include <iostream>

#include <Light.hpp>
#include <Model.hpp>
#include <OpenGL.hpp>
#include <Model_Obj.hpp>
#include <Render_Node.hpp>

#include <SFML/Window.hpp>
#include <btBulletDynamicsCommon.h>

using namespace std;
using namespace glt;

class Physics_World
{

	btDefaultCollisionConfiguration collisionConfiguration;

	btCollisionDispatcher collisionDispatcher;

	btDbvtBroadphase overlappingPairCache;

	btSequentialImpulseConstraintSolver constraintSolver;

	shared_ptr< btDiscreteDynamicsWorld > world;	//parametro para guardar el mundo

public:
	///\brief Physics_World -> constructor del mundo fisico
	Physics_World();
	///\brief ~Physics_World -> destructor del mundo fisico
	~Physics_World();
	/// \brief getWorld -> devuelve el mundo fisico
	btDiscreteDynamicsWorld * getWorld();
	///\brief addRigidBody -> añade un nuevo cuerpo fisico al physics world
	///@param body -> cuerpo fisico
	void addRigidBody(btRigidBody *body);

	void step()
	{
		//world->step();
	}

private:
	///\brief createWorld -> crea el mundo fisico
	shared_ptr< btDiscreteDynamicsWorld > createWorld(); //construye el world

};
#include <Physics_World.hpp>

//\brief Physics_World -> constructor del mundo fisico
Physics_World::Physics_World() : collisionDispatcher(&collisionConfiguration) {

	world = createWorld();
}

//\brief createWorld -> crea el mundo fisico
shared_ptr< btDiscreteDynamicsWorld > Physics_World::createWorld() {



	shared_ptr< btDiscreteDynamicsWorld > dynamicsWorld
	(
		new btDiscreteDynamicsWorld
		(
			&collisionDispatcher,
			&overlappingPairCache,
			&constraintSolver,
			&collisionConfiguration
		)
	);

	dynamicsWorld->setGravity(btVector3(0, -10, 0));

	return dynamicsWorld;
}

// \brief getWorld -> devuelve el mundo fisico
btDiscreteDynamicsWorld * Physics_World::getWorld() {

	return world.get();
}

// \brief ~Physics_World -> destructor del mundo fisico
Physics_World::~Physics_World() {

	
	
}

//\brief addRigidBody -> añade un nuevo cuerpo fisico al physics world
//@param body -> cuerpo fisico
void Physics_World::addRigidBody(btRigidBody *body) {

	world->addRigidBody(body);

}
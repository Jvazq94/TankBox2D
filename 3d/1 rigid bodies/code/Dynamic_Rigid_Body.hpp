#pragma once




#include <Rigid_Body.hpp>
#include <Shape.hpp>
#include <Physics_World.hpp>

using namespace std;
using namespace glt;

class Dynamic_Rigid_Body : public Rigid_Body
{

	btScalar mass;

public:

	Dynamic_Rigid_Body(std::shared_ptr< Shape > & shape, float mass, float restitution, btVector3 &origen, Physics_World *dynamicWorld)
		:
		Rigid_Body(shape, origen), mass(btScalar(mass))
	{
		btVector3 localInertia(0, 0, 0);

		shape->get()->calculateLocalInertia(mass, localInertia);

		btRigidBody::btRigidBodyConstructionInfo info
		(
			mass, state.get(), shape.get()->get(), localInertia
		);

		//btDynamicsWorld * realWorld = dynamicWorld->getWorld();
		body.reset(new btRigidBody(info));
		body->setRestitution(restitution);
		//dynamicWorld->getWorld()->addRigidBody(body.get());
		dynamicWorld->getWorld()->addRigidBody(body.get());

		
	}
};



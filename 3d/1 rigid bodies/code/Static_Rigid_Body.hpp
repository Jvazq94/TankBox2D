#pragma once
#include <Rigid_Body.hpp>
#include <Shape.hpp>
#include <Physics_World.hpp>


class Static_Rigid_Body : public Rigid_Body
{

public:

	Static_Rigid_Body(shared_ptr< Shape > shape, float restitution, btVector3 &origen, Physics_World *dynamicWorld) : Rigid_Body(shape, origen)
	{
		btRigidBody::btRigidBodyConstructionInfo info(0, state.get(), shape.get()->get());

		
		//shared_ptr<btDynamicsWorld> realWorld = dynamicWorld->getWorld();
		body.reset(new btRigidBody(info));
		body->setRestitution(restitution);
		
		//body->getWorldTransform().setRotation(btQuaternion (0, 40, 30, 1));
		//dynamicWorld->getWorld()->addRigidBody(body.get());
		dynamicWorld->getWorld()->addRigidBody(body.get());
	}

};
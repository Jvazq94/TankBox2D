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
#include <Shape.hpp>

using namespace std;
using namespace glt;

class Rigid_Body
{
protected:

	unique_ptr< btRigidBody 		  > body;
	unique_ptr< btDefaultMotionState  > state;
	shared_ptr< Shape   			  > shape;

//	btRigidBody * body;

public:
	//Rigid_Body();

		Rigid_Body(shared_ptr< Shape > shape,btVector3 &origen) : shape (shape)
		{
			btTransform transform;

			//btVector3 pos = origen;
			transform.setIdentity();
			transform.setOrigin(origen);
			

			

			state.reset(new btDefaultMotionState(transform));
			
		}
	
		virtual ~Rigid_Body() = default;

		btRigidBody * get()
		{
		return body.get();
		}

};

//body->setCollisionflags(btCollisionObject::CF_NO_CONTACT_RESPONSE);


//body.reset(new btCollisionOBJ);
//Body.setCollisionShape(...);

//////////////////////////////////////////////////////
// class Shape;
//	shared_ptr<btCollisionShape> physics.shape;


// class BoxShape::public Shape
//   BoxShape(float whith, float height, float depth)
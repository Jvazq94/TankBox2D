#pragma once

#include <Shape.hpp>

class Shpre_Shape : public Shape {

public:

	Shpre_Shape(float radius)
		:
		Shape(shared_ptr<btCollisionShape>(new btSphereShape(btScalar(radius)))) {

	}
	
};
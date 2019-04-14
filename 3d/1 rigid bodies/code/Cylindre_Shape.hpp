#pragma once


#include <Shape.hpp>

class Cylindre_Shape : public Shape {

public:

	Cylindre_Shape(btVector3 &cylindreVector)
		:
		Shape(shared_ptr<btCollisionShape>(new btCylinderShape (cylindreVector))) {

	}

};
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

class Shape {

	shared_ptr<btCollisionShape> shape;

public:

	virtual ~Shape() = default;
	btCollisionShape * get() {
		return shape.get();
	}

	Shape(shared_ptr<btCollisionShape> & shape) : shape(shape) {

	}

protected:

	

	
	/*btCollisionShape & get(){
	return *shape;
	}*/
};
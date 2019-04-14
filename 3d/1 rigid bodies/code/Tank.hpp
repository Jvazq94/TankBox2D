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
#include <Entity.hpp>
#include <Physics_World.hpp>
#include <Dynamic_Rigid_Body.hpp>
#include <Shpere_Shape.hpp>
#include<Box_Shape.hpp>
#include <Static_Rigid_Body.hpp>
#include <Scene.hpp>
#include <Cylindre_Shape.hpp>

using namespace std;
using namespace glt;

class Tank {

	shared_ptr<Rigid_Body> body;
	map<string, shared_ptr<Entity>> tank_Entities; // Grupo de objetos del tanke
	Physics_World *dynamicWorld; //Mundo fisico
	shared_ptr<Scene> tank_Scene; //Escena en la que se encuentra

	//Joints de las ruedas
	btHingeConstraint *r1Joint;
	btHingeConstraint *r2Joint;
	btHingeConstraint *r3Joint;
	btHingeConstraint *r4Joint;
	//Joints de los cuerpos del tanke
	btHingeConstraint *t1Joint;
	btHingeConstraint *t2Joint;

	int i; //Variable para el numero de balas
	int moveTower = 0; //variable para el movimiento de la torreta

public:


	///\brief Tank -> Constructor del tanke
	///@param  world -> mundo fisico de la escena
	///@param scene -> escena
	Tank(Physics_World *world, shared_ptr<Scene> scene);
	///\brief ~Tank -> destructor de la clase Tank
	~Tank();
	///\brief update -> funcion que se ejecuta cada tick, controla el movimiento, disparo y actualiza los cuerpos del tanke
	void update();
	///\brief BulletSpawn -> funcion para crear las balas cuando dispara el tanke
	void BulletSpawn();
	///\brief createDynamicSphereBody -> Creacion de un cuerpo dinamico con un shape de tipo esfera
	///@param shape -> shape del cuerpo
	///@param mass -> masa del cuerpo
	///@param restitution -> restitucion del cuerpo
	///@param position -> posicion de la creacion del cuerpo
	shared_ptr<Rigid_Body> createDynamicSphereBody(double shape, float mass, float restitution, btVector3 &position);
	///\brief createStaticBody -> Creacion de un cuerpo dinamico con un shape de tipo caja
	///@param x -> tamaño en X del cuerpo
	///@param y -> tamaño en Y del cuerpo
	///@param z -> tamaño en Z del cuerpo
	///@param restitution -> restitucion del cuerpo
	///@param position -> posicion de la creacion del cuerpo
	shared_ptr<Rigid_Body> createStaticBody(float x, float y, float z, float restitution, btVector3 &position);
	///\brief createDynamicBoxBody -> Creacion de un cuerpo dinamico con un shape de tipo caja
	///@param x -> tamaño en X del cuerpo
	///@param y -> tamaño en Y del cuerpo
	///@param z -> tamaño en Z del cuerpo
	///@param mass -> masa del cuerpo
	///@param restitution -> restitucion del cuerpo
	///@param position -> posicion de la creacion del cuerpo
	shared_ptr<Rigid_Body> createDynamicBoxBody(float x, float y, float z, float mass, float restitution, btVector3 &position);
	///\brief createDynamicCylindreBody -> Creacion de un cuerpo dinamico con un shape de tipo cilindro
	///@param x -> tamaño en X del cuerpo
	///@param y -> tamaño en Y del cuerpo
	///@param z -> tamaño en Z del cuerpo
	///@param mass -> masa del cuerpo
	///@param restitution -> restitucion del cuerpo
	///@param position -> posicion de la creacion del cuerpo
	shared_ptr<Rigid_Body> createDynamicCylindreBody(float x, float y, float z, float mass, float restitution, btVector3 &position);
};
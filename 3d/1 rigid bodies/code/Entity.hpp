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
#include <Rigid_Body.hpp>

using namespace std;
using namespace glt;


class Entity
{
	shared_ptr<Model> graphics_model;
	shared_ptr<Rigid_Body> physics_model;
	float model_scale_x;
	float model_scale_y;
	float model_scale_z;
	bool rotateBody;

public:
	///\brief Entity -> constructo de entidades para la escena
	///@param model -> modelo de la entidad
	///@param physics -> cuerpo fisico del objeto
	///@param xScale -> escala en X del cuerpo fisico
	///@param yScale -> escala en Y del cuerpo fisico
	///@param zScale -> escala en Z del cuerpo fisico
	///@param rotate -> si el cuerpo debe rotar o no
	Entity(shared_ptr<Model> model, shared_ptr<Rigid_Body> physics, float xScale, float yScale, float zScale, bool rotate);
	///\brief ~Entity -> destructo de la clase Entity
	~Entity();
	///\brief update -> funcion que se ejecuta en cada tick del programa
	void update();
	
	///\brief getModel -> devuelve el modelo grafico del objeto
	shared_ptr<Model> getModel();
	///\brieg GetBody -> devuelve el cuerpo fisico del objeto
	shared_ptr<Rigid_Body> GetBody();
};
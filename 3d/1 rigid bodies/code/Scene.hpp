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
#include <Box_Shape.hpp>
#include <Static_Rigid_Body.hpp>

using namespace std;
using namespace glt;


class Scene
{
	map<string, shared_ptr<Entity>> entities;
	map<string, shared_ptr<Entity>> pilars;
	int pilarsCount = 0;

	shared_ptr<Rigid_Body> bodyPaint;

	Physics_World *physics_world;
	Physics_World *dynamicWorld;

	shared_ptr<Entity> tank_body;
	bool upPlatform = false;
	bool left = true;
	bool opened = false;

	int delay = 0;
	
	

public:
	shared_ptr< Render_Node > scene_node;

	///\brief create_scene -> crea la escena con todos sus objetos
	shared_ptr< Render_Node > create_scene();
	///\brief OpenDoor -> abre la puerta de la escena, se llama cuando el tanke hace colision con la llave
	void OpenDoor();
	///\brief SetTankBody -> setea el cuerpo del tanke en una variable propia de la clase escena para comprobar las colisiones
	///@param tankBody -> objeto de tipo Entity que contiene el cuerpo del tanke
	void SetTankBody(shared_ptr<Entity> tankBody);
	///\brief Scene -> Constructor de la escena
	///@param  world -> mundo fisico de la escena
	Scene(Physics_World *world);
	///\brief ~Scene -> destructor de la clase escena
	~Scene();
	bool newBody = true;
	///\brief getNode -> devuelve la escena actual
	shared_ptr< Render_Node > getNode();
	///\brief configure_scene -> configura la luz y la camara de la escena
	void configure_scene();
	///\brief reset_viewport ->actualiza el viewport de la escena
	///@param window -> ventana de la escena
	void reset_viewport(const sf::Window & window);



	///\brief render -> renderiza la escena en cada momento, tambien se usa como un update
	void render() {

		 //Recorre todos los objetos de entities y los actualiza
		for (auto const& i : entities) {

			entities[i.first]->update();

		}

				
		//Comprueba las colisiones de todos los objetos del mundo
		int manifold_count = dynamicWorld->getWorld()->getDispatcher()->getNumManifolds();										
		for (int i = 0; i < manifold_count; i++)
		{
			btPersistentManifold * manifold = dynamicWorld->getWorld()->getDispatcher()->getManifoldByIndexInternal(i);
			btCollisionObject * object_a = (btCollisionObject *)(manifold->getBody0());
			btCollisionObject * object_b = (btCollisionObject *)(manifold->getBody1());
			int numContacts = manifold->getNumContacts();
			for (int j = 0; j < numContacts; j++)
			{
				btManifoldPoint & point = manifold->getContactPoint(j);
				if (point.getDistance() < 0.f)
				{
					
					//Comprueba si los objetos que coinciden son unos especificos
					if
						(
						(object_a == entities["key"]->GetBody()->get() && object_b == tank_body->GetBody()->get()) ||
							(object_a == tank_body->GetBody()->get() && object_b == entities["key"]->GetBody()->get())
							)
					{
						if (!opened) {
							entities["key"]->getModel()->set_visible(false);
							
							upPlatform = true;
							OpenDoor();
							opened = true;
						}
						
					}
				}
			}
		}
		
		if (upPlatform && delay < 50) {
			delay++;
		}
		//Mueve la plataforma cada tick en caso de que tenga que moverse
		if (upPlatform && left && delay >= 50) {
			
			btRigidBody *platform_body = entities["platform"]->GetBody()->get();
			platform_body->activate();

			//Cambia la posición de la plataforma cada tick
			platform_body->getWorldTransform().setOrigin(btVector3 (platform_body->getWorldTransform().getOrigin().getX() - 0.05f, platform_body->getWorldTransform().getOrigin().getY(), platform_body->getWorldTransform().getOrigin().getZ()));
			
			//Comprueba si la plataforma ha llegado a su destino
			if (platform_body->getWorldTransform().getOrigin().getX() <= 11) {

				if (platform_body->getWorldTransform().getOrigin().getX() == 11) {
					platform_body->setLinearFactor(btVector3(0, 0, 0));
					left = false;
					delay = 0;
				}
				else{

					//platfomr_body->getWorldTransform().getOrigin().getY = -3;
					platform_body->setLinearFactor(btVector3(0, 0, 0));
					left = false;
					delay = 0;

				}
			}
		}
		else if (upPlatform && !left && delay >= 500) {

			btRigidBody *platform_body = entities["platform"]->GetBody()->get();
			platform_body->activate();

			//Cambia la posición de la plataforma cada tick
			//platform_body->getWorldTransform().setOrigin(btVector3(platform_body->getWorldTransform().getOrigin().getX() + 0.05f, platform_body->getWorldTransform().getOrigin().getY(), platform_body->getWorldTransform().getOrigin().getZ()));


			platform_body->setLinearFactor(btVector3(1, 0, 0));
			platform_body->applyCentralForce(btVector3(-0.05f, 0, 0));


			//Comprueba si la plataforma ha llegado a su destino
			if (platform_body->getWorldTransform().getOrigin().getX() >= 15) {

				if (platform_body->getWorldTransform().getOrigin().getX() == 15) {
					platform_body->setLinearFactor(btVector3(0, 0, 0));
					left = true;
					delay = 0;
				}
				else {

					//platfomr_body->getWorldTransform().getOrigin().getY = -3;
					platform_body->setLinearFactor(btVector3(0, 0, 0));
					left = true;
					delay = 0;

				}
			}

		}
		if (GetKeyState('K') & 0x8000) {
			upPlatform = true;
		}

		scene_node->render();
	}
	///\ brief createDynamicBody -> Creacion de un cuerpo dinamico con un shape de tipo esfera
	///@param shape -> shape del cuerpo
	///@param mass -> masa del cuerpo
	///@param restitution -> restitucion del cuerpo
	///@param position -> posicion de la creacion del cuerpo
	shared_ptr<Rigid_Body> createDynamicBody(double shape, float mass, float restitution, btVector3 &position);
	///\ brief createStaticBody -> Creacion de un cuerpo dinamico con un shape de tipo caja
	///@param x -> tamaño en X del cuerpo
	///@param y -> tamaño en Y del cuerpo
	///@param z -> tamaño en Z del cuerpo
	///@param restitution -> restitucion del cuerpo
	///@param position -> posicion de la creacion del cuerpo
	shared_ptr<Rigid_Body> createStaticBody(float x, float y, float z, float restitution, btVector3 &position);
	///\ brief createDynamicBoxBody -> Creacion de un cuerpo dinamico con un shape de tipo caja
	///@param x -> tamaño en X del cuerpo
	///@param y -> tamaño en Y del cuerpo
	///@param z -> tamaño en Z del cuerpo
	///@param mass -> masa del cuerpo
	///@param restitution -> restitucion del cuerpo
	///@param position -> posicion de la creacion del cuerpo
	shared_ptr<Rigid_Body> createDynamicBoxBody(float x, float y, float z, float mass, float restitution, btVector3 &position);



		
};
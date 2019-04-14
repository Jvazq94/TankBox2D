

#include <Scene.hpp>
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
#include <Tank.hpp>


using namespace std;
using namespace glt;

// \brief Scene -> Constructor de la escena
//@param  world -> mundo fisico de la escena
Scene::Scene(Physics_World *world) {

	//Guardas el phusic world y la escena
	dynamicWorld = world;
	scene_node = create_scene();
	
}

// \brief create_scene -> crea la escena con todos sus objetos
shared_ptr< Render_Node > Scene::create_scene() { //Crea la escena
	
	
	//suelo 1
	bodyPaint = createStaticBody(3, 1, 10, 0.f, btVector3(20, -3, -10)); //Crea un cuerpo físico para el objeto
	shared_ptr<Entity> floor(new Entity(shared_ptr<Model>(new Model_Obj("../../../../assets/caja2.obj")), bodyPaint, 3.f,0.5f,10.f, true)); //creal el objeto pasandole los 
	entities["floor"] = floor;	//Guarda el objeto de tipo "Entity" en un array																//parámetros del cuerpo físico y el modelo

	//suelo 2
	bodyPaint = createStaticBody(3, 1, 10, 0.f, btVector3(0, -3, -10));
	shared_ptr<Entity> floor2(new Entity(shared_ptr<Model>(new Model_Obj("../../../../assets/caja2.obj")), bodyPaint, 3.f, 0.5f, 10.f, true));
	entities["floor2"] = floor2;

	//suelo 3
	bodyPaint = createStaticBody(3, 1, 10, 0.f, btVector3(-10, -3, -10));
	shared_ptr<Entity> floor3(new Entity(shared_ptr<Model>(new Model_Obj("../../../../assets/caja2.obj")), bodyPaint, 3.f, 0.5f, 10.f, true));
	entities["floor3"] = floor3;

	//llave
	bodyPaint = createStaticBody(.2f, .2f, .2f, 0.f, btVector3(19, -1, -12));
	shared_ptr<Entity> key(new Entity(shared_ptr<Model>(new Model_Obj("../../../../assets/key.obj")), bodyPaint, .5f, .5f, .5f, true));
	entities["key"] = key;

	//plataforma
	bodyPaint = createDynamicBoxBody(9.f, 1.f, 4, 100000.f,1.f, btVector3(21.f, -3, -4.f));
	shared_ptr<Entity> platform(new Entity(shared_ptr<Model>(new Model_Obj("../../../../assets/caja2.obj")), bodyPaint, 9.f, 0.5f, 4.f, true));
	entities["platform"] = platform;

	platform->GetBody()->get()->setLinearFactor(btVector3(0, 0, 0)); //Le limita el movimiento en todos los ejes

	//puerta
	bodyPaint = createDynamicBoxBody(1.f, 4.f, 8.f, 10000000.f, 0.f, entities["floor2"]->GetBody()->get()->getWorldTransform().getOrigin() + btVector3(0,4,0));
	shared_ptr<Entity> door(new Entity(shared_ptr<Model>(new Model_Obj("../../../../assets/caja2.obj")), bodyPaint, 1.f, 3.f, 8.f, true));
	entities["door"] = door;

	door->GetBody()->get()->setLinearFactor(btVector3(0, 0, 0)); //Le limitamos el movimiento de todos los ejes

	//pilar 1
	bodyPaint = createStaticBody(1, 3, 1, 0.f, btVector3(-9, 0, -5));
	shared_ptr<Entity> pilar1(new Entity(shared_ptr<Model>(new Model_Obj("../../../../assets/caja2.obj")), bodyPaint, 1.f, 3.f, 1.f, true));
	entities["pilar1"] = pilar1;
	pilars["pilar1"] = pilar1;

	//pilar 2
	bodyPaint = createStaticBody(1, 3, 1, 0.f, btVector3(-9, 0, -8));
	shared_ptr<Entity> pilar2(new Entity(shared_ptr<Model>(new Model_Obj("../../../../assets/caja2.obj")), bodyPaint, 1.f, 3.f, 1.f, true));
	entities["pilar2"] = pilar2;
	pilars["pilar2"] = pilar2;
	 
	//pilar 3
	bodyPaint = createStaticBody(1, 3, 1, 0.f, btVector3(-9, 0, -11));
	shared_ptr<Entity> pilar3(new Entity(shared_ptr<Model>(new Model_Obj("../../../../assets/caja2.obj")), bodyPaint, 1.f, 3.f, 1.f, true));
	entities["pilar3"] = pilar3;
	pilars["pilar3"] = pilar3;
	


	shared_ptr< Render_Node > scene(new Render_Node); //Crea el render de la escena
	shared_ptr< Camera      > camera(new Camera(20.f, 1.f, 50.f, 1.f)); // Crea la cámara de la escen
	shared_ptr< Light       > light(new Light); // Crea el foco de luz de la escena

	camera->translate(Vector3(4, 3, 15.f)); // Mueve la cámara a un punto especifico

	// Se añaden los nodos a la escena:
	
	scene->add("box", floor->getModel());
	scene->add("floor2", floor2->getModel());
	scene->add("floor3", floor3->getModel());
	scene->add("camera", camera);
	scene->add("light", light);
	scene->add("key", key->getModel());
	scene->add("platform", platform->getModel());
	scene->add("door", door->getModel());
	scene->add("pilar1", pilar1->getModel());
	scene->add("pilar2", pilar2->getModel());
	scene->add("pilar3", pilar3->getModel());

	return scene; 
}

// \brief OpenDoor -> abre la puerta de la escena, se llama cuando el tanke hace colision con la llave
void Scene::OpenDoor() {



		entities["door"]->GetBody()->get()->activate(); //Activa el cuerpo físico por si se encontraba en "sleep"
		entities["door"]->GetBody()->get()->setLinearFactor(btVector3(1, 1, 1)); //Le habilita el momivimiento en los ejes
		entities["door"]->GetBody()->get()->getWorldTransform().setRotation(btQuaternion(90, 90, 0, 1)); // Rota el cuerpo
		entities["door"]->GetBody()->get()->getWorldTransform().setOrigin(entities["door"]->GetBody()->get()->getWorldTransform().getOrigin() + btVector3(0, 3, 0)); // Mueve el cuerpo
		entities["door"]->GetBody()->get()->setLinearFactor(btVector3(0, 0, 0)); // Le quita el movimiento al cuerpo

	
}

// \brief configure_scene -> configura la luz y la camara de la escena
void Scene::configure_scene()
{

	scene_node->get("light")->translate(Vector3(10.f, 10.f, 10.f));
	scene_node->get("camera")->translate(Vector3(0.f, 0.f, 5.f));

}

// \brief reset_viewport ->actualiza el viewport de la escena
// @param window -> ventana de la escena
void Scene::reset_viewport(const sf::Window & window)
{
	

	GLsizei width = GLsizei(window.getSize().x);
	GLsizei height = GLsizei(window.getSize().y);

	
	scene_node->get_active_camera()->set_aspect_ratio(float(width) / height);

	glViewport(0, 0, width, height);
}

// \brief getNode -> devuelve la escena actual
shared_ptr< Render_Node > Scene::getNode(){ //Devuelve la escena

	
	return scene_node;
}

// \ brief createDynamicBody -> Creacion de un cuerpo dinamico con un shape de tipo esfera
// @param shape -> shape del cuerpo
// @param mass -> masa del cuerpo
// @param restitution -> restitucion del cuerpo
// @param position -> posicion de la creacion del cuerpo
shared_ptr<Rigid_Body> Scene::createDynamicBody(double shape, float mass, float restitution, btVector3 &position) { // Crea un cuerpo dinamico de esfera

	shared_ptr<Rigid_Body> sphere_body(
		new Dynamic_Rigid_Body
		(
			shared_ptr<Shape>(new Shpre_Shape(shape)), mass, restitution, position, dynamicWorld
		)
	);

	return sphere_body;
}

// \ brief createStaticBody -> Creacion de un cuerpo dinamico con un shape de tipo caja
// @param x -> tamaño en X del cuerpo
// @param y -> tamaño en Y del cuerpo
// @param z -> tamaño en Z del cuerpo
// @param restitution -> restitucion del cuerpo
// @param position -> posicion de la creacion del cuerpo
shared_ptr<Rigid_Body> Scene::createStaticBody(float x, float y, float z, float restitution, btVector3 &position) { //crea un cuerpo estatico de caja

	shared_ptr<Rigid_Body> rigid_body(
		new Static_Rigid_Body
		(
			shared_ptr<Shape>(new Box_Shape(x, y, z)), restitution, position, dynamicWorld
		)
	);

	return rigid_body;
}

// \ brief createDynamicBoxBody -> Creacion de un cuerpo dinamico con un shape de tipo caja
// @param x -> tamaño en X del cuerpo
// @param y -> tamaño en Y del cuerpo
// @param z -> tamaño en Z del cuerpo
// @param mass -> masa del cuerpo
// @param restitution -> restitucion del cuerpo
// @param position -> posicion de la creacion del cuerpo
shared_ptr<Rigid_Body> Scene::createDynamicBoxBody(float x, float y, float z, float mass, float restitution, btVector3 &position) { // crea objeto dinámico de caja

	shared_ptr<Rigid_Body> sphere_body(
		new Dynamic_Rigid_Body
		(
			shared_ptr<Shape>(new Box_Shape(x, y, z)), mass, restitution, position, dynamicWorld
		)
	);

	return sphere_body;



}

// \brief SetTankBody -> setea el cuerpo del tanke en una variable propia de la clase escena para comprobar las colisiones
// @param tankBody -> objeto de tipo Entity que contiene el cuerpo del tanke
void Scene::SetTankBody(shared_ptr<Entity> tankBody) { //setea el cuerpo físico del tanke de la escena a un parametro para mas tarde poder comprobar colisiones

	tank_body = tankBody;
}

// \brief ~Scene -> destructor de la clase escena
Scene::~Scene() {


}

#include <Tank.hpp>


// \brief Tank -> Constructor del tanke
//@param  world -> mundo fisico de la escena
//@param scene -> escena
Tank::Tank(Physics_World *world, shared_ptr<Scene> scene) {

	
	dynamicWorld = world; //Se guarda el mundo fisico
	tank_Scene = scene; //Se guarda la escena



	body = createDynamicCylindreBody(0.5f, 0.2f, 0.5f, 1.f, 1.f, btVector3(18.5f, -2, -1)); //Se crea un cuerpo fisico
	shared_ptr<Entity> rueda(new Entity(shared_ptr<Model>(new Model_Obj("../../../../assets/cilindro.obj")), body, 0.5f, 0.2f, 0.5f, true)); //Rueda 1
	tank_Entities["rueda"] = rueda;

	body = createDynamicCylindreBody(0.5f, 0.2f, 0.5f, 1.f, 1.f, btVector3(19.5f, -2, -1));
	shared_ptr<Entity> rueda2(new Entity(shared_ptr<Model>(new Model_Obj("../../../../assets/cilindro.obj")), body, 0.5f, 0.2f, 0.5f, true)); //Rueda 2
	tank_Entities["rueda2"] = rueda2;

	body = createDynamicCylindreBody(0.5f, 0.2f, 0.5f, 1.f, 1.f, btVector3(18.5f, -2, -3));
	shared_ptr<Entity> rueda3(new Entity(shared_ptr<Model>(new Model_Obj("../../../../assets/cilindro.obj")), body, 0.5f, 0.2f, 0.5f, true));  //Rueda3
	tank_Entities["rueda3"] = rueda3;

	body = createDynamicCylindreBody(0.5f, 0.2f, 0.5f, 1.f, 1.f, btVector3(19.5f, -2, -3));
	shared_ptr<Entity> rueda4(new Entity(shared_ptr<Model>(new Model_Obj("../../../../assets/cilindro.obj")), body, 0.5f, 0.2f, 0.5f, true));  //Rueda4
	tank_Entities["rueda4"] = rueda4;
	
	//Se rotan las ruedas para que esten en la posicion correcta
	rueda->GetBody()->get()->getWorldTransform().setRotation(btQuaternion(0, 90, 90, 1));
	rueda2->GetBody()->get()->getWorldTransform().setRotation(btQuaternion(0, 90, 90, 1));
	rueda3->GetBody()->get()->getWorldTransform().setRotation(btQuaternion(0, 90, 90, 1));
	rueda4->GetBody()->get()->getWorldTransform().setRotation(btQuaternion(0, 90, 90, 1));

	body = createDynamicBoxBody(1.3f, .5f, 0.5f,1.f,0.f, btVector3(19, -2, -2));

	shared_ptr<Entity> tank_body(new Entity(shared_ptr<Model>(new Model_Obj("../../../../assets/caja2.obj")), body, 1.3f, 0.5f, 0.5f, true));  //Cuerpo tanke
	tank_Entities["tank_body"] = tank_body;
	

	body = createDynamicBoxBody(.5f, .5f, 0.5f, 1.f, 0.f, btVector3(19, -1, -2));

	shared_ptr<Entity> tank_body2(new Entity(shared_ptr<Model>(new Model_Obj("../../../../assets/caja2.obj")), body, .5f, 0.5f, 0.5f, true));  //Cabeza torreta
	tank_Entities["tank_body2"] = tank_body2;

	body = createDynamicCylindreBody(0.2f, .5f, 0.2f, .1f, 0.f, btVector3(20.3f, -1, -2));
	shared_ptr<Entity> tank_body3(new Entity(shared_ptr<Model>(new Model_Obj("../../../../assets/cilindro.obj")), body, 0.2f, .7f, 0.2f, true)); //Torreta
	tank_Entities["tank_body3"] = tank_body3;

	tank_body3->GetBody()->get()->getWorldTransform().setRotation(btQuaternion(90, 90, 0, 1));

	

	scene->SetTankBody(tank_Entities["tank_body"]); //Se envia el cuerpo del tanke a la escena

	// Se añaden los nodos a la escena:

	scene->getNode()->add("tank_body", tank_body->getModel());
	scene->getNode()->add("tank_body2", tank_body2->getModel());
	scene->getNode()->add("tank_body3", tank_body3->getModel());
	scene->getNode()->add("rueda",  rueda->getModel());
	scene->getNode()->add("rueda2", rueda2->getModel());
	scene->getNode()->add("rueda3", rueda3->getModel());
	scene->getNode()->add("rueda4", rueda4->getModel());



	//Se genera los Joints de las ruedas con el cuerpo principal

	 btHingeConstraint *joint1 = new btHingeConstraint(
		 *rueda->GetBody()->get(), *tank_body->GetBody()->get(), btVector3(0,0,0), btVector3(-.6f,-.3f,.7f), btVector3(0, 1, 0), btVector3(0, 0, 0)); //Joint Rueda 1

	 r1Joint = joint1;

	 btHingeConstraint *joint2 = new btHingeConstraint(
		 *rueda2->GetBody()->get(), *tank_body->GetBody()->get(), btVector3(0, 0, 0), btVector3(.6f, -.3f, .7f), btVector3(0, 1, 0), btVector3(0, 0, 0)); //Joint Rueda 2

	 r2Joint = joint2;

	 btHingeConstraint *joint3 = new btHingeConstraint(
		 *rueda3->GetBody()->get(), *tank_body->GetBody()->get(), btVector3(0,0, 0), btVector3(-.6f, -.3f, -.7f), btVector3(0, 1, 0), btVector3(0,0,0)); //Joint Rueda 3

	 r3Joint = joint3;

	 btHingeConstraint *joint4 = new btHingeConstraint(
		 *rueda4->GetBody()->get(), *tank_body->GetBody()->get(), btVector3(0, 0, 0), btVector3(.6f, -.3f, -.7f), btVector3(0, 1, 0), btVector3(0, 0, 0)); //Joint Rueda 3

	 r4Joint = joint4;

	 //Se generan los joints del cuerpo del tanke

	 btHingeConstraint *joint5 = new btHingeConstraint(
		 *tank_body2->GetBody()->get(), *tank_body->GetBody()->get(), btVector3(0, 0, 0), btVector3(0, 1.f, 0), btVector3(0, 1, 0), btVector3(0, 0, 0)); //Joint Cabeza torreta con cuerpo principal

	 t1Joint = joint5;

	 btHingeConstraint *joint6 = new btHingeConstraint(
		 *tank_body3->GetBody()->get(), *tank_body2->GetBody()->get(), btVector3(0, -.7f, 0), btVector3(.6f, 0, 0), btVector3(0, 0, 1), btVector3(0, 0, 0)); //Joint Torreta con Cabeza torreta


	 
	 t2Joint = joint6;

	 //Se le habilita un montor angular a los joints para poder añadiles fuerzas
	 r1Joint->enableAngularMotor(true, 0, 1.f);
	 r2Joint->enableAngularMotor(true, 0, 1.f);
	 r3Joint->enableAngularMotor(true, 0, 1.f);
	 r4Joint->enableAngularMotor(true, 0, 1.f);
	 joint6->enableAngularMotor(true, 0.f, 1.f);

	 t1Joint->enableAngularMotor(true, 0, 1.f);

	 //Se añaden los joints al mundo fisico
	 dynamicWorld->getWorld()->addConstraint(joint1);
	 dynamicWorld->getWorld()->addConstraint(joint2);
	 dynamicWorld->getWorld()->addConstraint(joint3);
	 dynamicWorld->getWorld()->addConstraint(joint4);
	 dynamicWorld->getWorld()->addConstraint(joint5);
	 dynamicWorld->getWorld()->addConstraint(joint6);
}


// \ brief createDynamicSphereBody -> Creacion de un cuerpo dinamico con un shape de tipo esfera
// @param shape -> shape del cuerpo
// @param mass -> masa del cuerpo
// @param restitution -> restitucion del cuerpo
// @param position -> posicion de la creacion del cuerpo
shared_ptr<Rigid_Body> Tank::createDynamicSphereBody(double shape, float mass, float restitution, btVector3 &position) {//Crea un cuerpo dinamico de esfera

	shared_ptr<Rigid_Body> sphere_body(
		new Dynamic_Rigid_Body
		(
			shared_ptr<Shape>(new Shpre_Shape(shape)), mass, restitution, position, dynamicWorld
		)
	);

	return sphere_body;

}

// \ brief createDynamicBoxBody -> Creacion de un cuerpo dinamico con un shape de tipo caja
// @param x -> tamaño en X del cuerpo
// @param y -> tamaño en Y del cuerpo
// @param z -> tamaño en Z del cuerpo
// @param mass -> masa del cuerpo
// @param restitution -> restitucion del cuerpo
// @param position -> posicion de la creacion del cuerpo
shared_ptr<Rigid_Body> Tank::createDynamicBoxBody(float x, float y, float z, float mass, float restitution, btVector3 &position) { // crea un cuerpo dinamico de caja
	
	shared_ptr<Rigid_Body> sphere_body(
		new Dynamic_Rigid_Body
		(
			shared_ptr<Shape>(new Box_Shape(x, y, z)), mass, restitution, position, dynamicWorld
		)
	);

	return sphere_body;



}

// \ brief createDynamicCylindreBody -> Creacion de un cuerpo dinamico con un shape de tipo cilindro
// @param x -> tamaño en X del cuerpo
// @param y -> tamaño en Y del cuerpo
// @param z -> tamaño en Z del cuerpo
// @param mass -> masa del cuerpo
// @param restitution -> restitucion del cuerpo
// @param position -> posicion de la creacion del cuerpo
shared_ptr<Rigid_Body> Tank::createDynamicCylindreBody(float x, float y, float z, float mass, float restitution, btVector3 &position) { //crea un cuerpo dinamico de cilindro
	
	shared_ptr<Rigid_Body> sphere_body(
		new Dynamic_Rigid_Body
		(
			shared_ptr<Shape>(new Cylindre_Shape(btVector3(x, y, z))), mass, restitution, position, dynamicWorld
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
shared_ptr<Rigid_Body> Tank::createStaticBody(float x, float y, float z, float restitution, btVector3 &position) { //crea un cuerpo estatico de caja

	shared_ptr<Rigid_Body> rigid_body(
		new Static_Rigid_Body
		(
			shared_ptr<Shape>(new Box_Shape(x, y, z)), restitution, position, dynamicWorld
		)
	);

	return rigid_body;

}
// \brief BulletSpawn -> funcion para crear las balas cuando dispara el tanke
void Tank::BulletSpawn() { //Crea balas cuando se dispara

	//Calcula el vector directo en el que debe salir la bala
	btVector3 move = tank_Entities["tank_body3"]->GetBody()->get()->getWorldTransform().getOrigin() - tank_Entities["tank_body2"]->GetBody()->get()->getWorldTransform().getOrigin(); 

	//se crea un cuerpo fisico de la bala 
	body = createDynamicSphereBody(.1, 1.f, 1.f, tank_Entities["tank_body3"]->GetBody()->get()->getWorldTransform().getOrigin() + move *1.2f);

	body->get()->getWorldTransform().setRotation(tank_Entities["tank_body3"]->GetBody()->get()->getWorldTransform().getRotation());//Se rota la bala en funcion de la torreta
	body->get()->setIgnoreCollisionCheck(tank_Entities["tank_body3"]->GetBody()->get(), true); //Se le da los cuerpo a los que debe ignorar
	body->get()->setIgnoreCollisionCheck(tank_Entities["tank_body2"]->GetBody()->get(), true);
	
	

	shared_ptr<Entity> bullet(new Entity(shared_ptr<Model>(new Model_Obj("../../../../assets/sphere.obj")), body, .5f, .5f, .5f, true)); //Se crea el objeto bala de tipo entity
	
	string name = "bullet" + to_string(i); //Se le da un nombre a la bala
	i++; //Aumenta el contador de balas
	tank_Entities[name] = bullet; //Se añade la bala a el array de entitys
	tank_Scene->getNode()->add(name, bullet->getModel()); //Se añade la bala a la escena
	

	bullet->GetBody()->get()->applyImpulse(move * 10, bullet->GetBody()->get()->getCenterOfMassPosition()); //Se le añade un impulso a la bala segun el vector director
	tank_Entities[name]->update();
	

}

// \brief update -> funcion que se ejecuta cada tick, controla el movimiento, disparo y actualiza los cuerpos del tanke
void Tank::update() {


	//Se actualizan todos los cuerpos del tanke
	for (auto const& i : tank_Entities) {

		tank_Entities[i.first]->update();
		tank_Entities[i.first]->GetBody()->get()->activate();
	}

	//Comprueba la tecla que se esta pulsando para darle fuerza a los joints de las ruedas y moverla
	if (GetKeyState('W') & 0x8000) {


		r1Joint->setMotorTargetVelocity(-3.f);
		r2Joint->setMotorTargetVelocity(-3.f);
		r3Joint->setMotorTargetVelocity(-3.f);
		r4Joint->setMotorTargetVelocity(-3.f);

		
	}
	else if (GetKeyState('A') & 0x8000) {


		r1Joint->setMotorTargetVelocity(-3.f);
		r2Joint->setMotorTargetVelocity(-3.f);
		r3Joint->setMotorTargetVelocity(3.f);
		r4Joint->setMotorTargetVelocity(3.f);
	}
	else if (GetKeyState('D') & 0x8000) {

		r1Joint->setMotorTargetVelocity(3.f);
		r2Joint->setMotorTargetVelocity(3.f);
		r3Joint->setMotorTargetVelocity(-3.f);
		r4Joint->setMotorTargetVelocity(-3.f);

	}
	else if (GetKeyState('S') & 0x8000) {

		r1Joint->setMotorTargetVelocity(3.f);
		r2Joint->setMotorTargetVelocity(3.f);
		r3Joint->setMotorTargetVelocity(3.f);
		r4Joint->setMotorTargetVelocity(3.f);

	}else{
		r1Joint->setMotorTargetVelocity(0.f);
		r2Joint->setMotorTargetVelocity(0.f);
		r3Joint->setMotorTargetVelocity(0.f);
		r4Joint->setMotorTargetVelocity(0.f);
		
	}

	//Comprueba la tecla pulsada para darle fuerza a la cabeza de la torreta y moverla
	if (GetKeyState('E') & 0x8000) {

		t1Joint->setMotorTargetVelocity(-2.f);

	}
	else if  (GetKeyState('Q') & 0x8000) {

		t1Joint->setMotorTargetVelocity(2.f);
	}
	else {

		t1Joint->setMotorTargetVelocity(0.f);

	}

	//Se comprueba la tecla pulsada para darle fuerza a la torreta y moverla 
	if (GetKeyState('R') & 0x8000 && moveTower < 15) {

		t2Joint->setMotorTargetVelocity(1.f);
		moveTower++;

	}
	else if (GetKeyState('T') & 0x8000 && moveTower > -15) {

		t2Joint->setMotorTargetVelocity(-1.f);
		moveTower--;

	}
	else {

		t2Joint->setMotorTargetVelocity(0.f);

	}
	//Se comprueba si se esta pulsando el "Space" para spawnear una bala
	if (GetKeyState(VK_SPACE) & 0x8000) {

		BulletSpawn(); 
	}

}

// \brief ~Tank -> destructor de la clase Tank
Tank::~Tank() {

	
}
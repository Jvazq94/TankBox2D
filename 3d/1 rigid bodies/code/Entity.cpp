#include <Entity.hpp>

//\brief Entity -> constructo de entidades para la escena
//@param model -> modelo de la entidad
//@param physics -> cuerpo fisico del objeto
//@param xScale -> escala en X del cuerpo fisico
//@param yScale -> escala en Y del cuerpo fisico
//@param zScale -> escala en Z del cuerpo fisico
//@param rotate -> si el cuerpo debe rotar o no
Entity::Entity(shared_ptr<Model> model, shared_ptr<Rigid_Body> physics, float xScale, float yScale, float zScale, bool rotate) {

	graphics_model = model;
	physics_model = physics;
	model_scale_x = xScale * 2;
	model_scale_y = yScale * 2;
	model_scale_z = zScale * 2;
	rotateBody = rotate;
}

//\brief update -> funcion que se ejecuta en cada tick del programa
void Entity::update() {

	

	// Apply the physics transform to the graphics model:
	
		btTransform physics_transform;

		physics_model->get()->getMotionState()->getWorldTransform(physics_transform);

		glm::mat4 graphics_transform;

		physics_transform.getOpenGLMatrix(glm::value_ptr(graphics_transform));

		graphics_model->set_transformation(graphics_transform);

		graphics_model->scale(model_scale_x, model_scale_y, model_scale_z);
		

		if (rotateBody) {

			graphics_model->rotate_around_y(0.01f);
		}

	
}

//\brief getModel -> devuelve el modelo grafico del objeto
shared_ptr<Model> Entity::getModel() {

	return graphics_model;
}

//\brieg GetBody -> devuelve el cuerpo fisico del objeto
shared_ptr<Rigid_Body> Entity::GetBody() {
	return physics_model;
}

//\brief ~Entity -> destructo de la clase Entity
Entity::~Entity() {

}
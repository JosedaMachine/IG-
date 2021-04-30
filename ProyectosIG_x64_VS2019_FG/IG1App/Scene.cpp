#include "Scene.h"
#include "CheckML.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>
#include "QuadricEntity.h"

using namespace glm;
//-------------------------------------------------------------------------

void Scene::init(){
	setGL();  // OpenGL settings
					
	chargeTextures(); //We charge here the textures

	// Graphics objects (entities) of the scene
	if (mid == 0) {
		TIE* tie = new TIE(gTextures.back());
		gObjects.push_back(tie);
		gObjects.push_back(new EjesRGB(400.0));
	}
	else if (mid == 1) {
		//Anillo cuadrado
		gObjects.push_back(new EjesRGB(400.0));
		gObjects.push_back(new AnilloCuadrado());
	}
	else if (mid == 2) {
		gObjects.push_back(new EjesRGB(400.0));
		gObjects.push_back(new CuboConTapas(100));
	}
}

void Scene::chargeTextures(){
	Texture* t = new Texture();
	t->load("../Bmps/baldosaC.bmp");
	gTextures.push_back(t);

	t = new Texture();
	t->load("../Bmps/baldosaP.bmp");
	gTextures.push_back(t);

	t = new Texture();
	t->load("../Bmps/container.bmp");
	gTextures.push_back(t);

	t = new Texture();
	t->load("../Bmps/papelC.bmp");
	gTextures.push_back(t);

	t = new Texture();
	t->load("../Bmps/windowV.bmp", 255 / 2);
	gTextures.push_back(t);

	t = new Texture();
	//Si se le aplica el alpha, se ve negro el fondo de la imagen
	t->load("../Bmps/grass.bmp", u8vec3(0, 0, 0));
	gTextures.push_back(t);

	t = new Texture();
	t->load("../Bmps/noche.bmp", 255 / 1.5);
	gTextures.push_back(t);
}

//-------------------------------------------------------------------------
void Scene::free()
{ // release memory and resources   

	for (Entidad* el : gObjects){
		delete el;  el = nullptr;
	}

	for (Entidad* cosa : gObjectsTrans){
		delete cosa;  cosa = nullptr;
	}
	
	for (Texture* el : gTextures){
		delete el;  el = nullptr;
	}

	gTextures.clear();
	gObjects.clear();
	gObjectsTrans.clear();
}
//-------------------------------------------------------------------------
void Scene::setGL()
{
	// OpenGL basic setting
	glClearColor(0.0, 0.0, 0.0, 1.0);  // background color (alpha=1 -> opaque)
	glEnable(GL_DEPTH_TEST);  // enable Depth test 
	glEnable(GL_TEXTURE_2D);

}
//-------------------------------------------------------------------------
void Scene::resetGL()
{
	glClearColor(.0, .0, .0, .0);  // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);  // disable Depth test 	
	glDisable(GL_TEXTURE_2D);
}
void Scene::sceneDirLight(Camera const& cam) const
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glm::fvec4 posDir = { 1, 1, 1, 0 };
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(cam.viewMat()));
	glLightfv(GL_LIGHT0, GL_POSITION, value_ptr(posDir));
	glm::fvec4 ambient = { 0, 0, 0, 1 };
	glm::fvec4 diffuse = { 1, 1, 1, 1 };
	glm::fvec4 specular = { 0.5, 0.5, 0.5, 1 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, value_ptr(ambient));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, value_ptr(diffuse));
	glLightfv(GL_LIGHT0, GL_SPECULAR, value_ptr(specular));
}
//-------------------------------------------------------------------------

void Scene::render(Camera const& cam) const{
	sceneDirLight(cam);

	cam.upload(); //viewport proyect

	for (Entidad* el : gObjects) {
		el->render(cam.viewMat());	//cada elemento renderiza
	}
	
	for (Entidad* cosa : gObjectsTrans)
	{
		cosa->render(cam.viewMat());	//cada elemento renderiza
	}
}

void Scene::update() {
	for (auto& o : gObjects) {
		o->update();
	}
}

void Scene::changeScene(int id) {
	resetGL();
	free();
	mid = id;
	init();
}
//-------------------------------------------------------------------------



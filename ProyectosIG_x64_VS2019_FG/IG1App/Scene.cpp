#include "Scene.h"
#include "CheckML.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;
//-------------------------------------------------------------------------

void Scene::init()
{
	setGL();  // OpenGL settings

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

	// allocate memory and load resources
	// Lights
	// Textures

	// Graphics objects (entities) of the scene

	if (mid == 0) {

		//Rect�ngulo
		gObjects.push_back(new RectanguloRGB(800, 800));
		gObjects.back()->setModelMat(translate(dmat4(1), dvec3(0, 0, -100)));

		gObjects.back()->setColor(dvec4(1.0, 1.0, 1.0, 0.0));
		gObjects.push_back(new Poligono(100, 300));
		gObjects.back()->setColor(dvec4(1.0, 1.0, 0.0, 0.0));
		gObjects.push_back(new Poligono(360, 200)); //igual hay que meterle 360 lados porque un c�rculo tiene 360 grados //Igual no
		gObjects.back()->setColor(dvec4(1.0, 0.07, 0.57, 0.0));


		//Serpinpi
		gObjects.push_back(new SerPinspi(200, 10000));
		gObjects.back()->setColor(dvec4(1.0, 1.0, 1.0, 0.0));


		//Tri�ngulo
		gObjects.push_back(new TrianguloRGB(20, 200));
		gObjects.back()->setModelMat(translate(gObjects.back()->modelMat(), dvec3(200, 0, 0)));

	}
	else if (mid == 1) {

		gObjects.push_back(new EjesRGB(400.0));

		gObjects.push_back(new Suelo(700, 700, 5, 5));
		gObjects.back()->setTexture(t);
		gObjects.back()->setModelMat(glm::rotate(dmat4(1), radians(-90.0), dvec3(1, 0, 0)));

		gObjects.push_back(new Estrella3D(50, 10, 100));
		gObjects.back()->setColor(dvec4(1.0, 1.0, 1.0, 0.0));
		gObjects.back()->setModelMat(glm::translate(gObjects.back()->modelMat(), dvec3(-200, 300, - 200)));
		gObjects.back()->setTexture(gTextures[1]);

		int sideCube = 200.0f;
		gObjects.push_back(new Caja(sideCube, gTextures[3]));
		gObjects.back()->setTexture(gTextures[2]);
		gObjects.back()->setModelMat(glm::translate(gObjects.back()->modelMat(), dvec3(-sideCube, sideCube / 2, -sideCube)));

		int sizePhoto = 100;
		gObjects.push_back(new Foto(sizePhoto, sizePhoto, GL_FRONT));
		gObjects.back()->setModelMat(glm::translate(dmat4(1), dvec3(0, 5, 0)));
		gObjects.back()->setModelMat(glm::rotate(gObjects.back()->modelMat(), radians(-90.0), dvec3(1, 0, 0)));

		gObjectsTrans.push_back(new Glass(700.0, 200));
		gObjectsTrans.back()->setTexture(gTextures[4]);
		gObjectsTrans.back()->setModelMat(glm::translate(gObjectsTrans.back()->modelMat(), dvec3(0, 100, 0)));

		Texture* cristal = new Texture();
		gTextures.push_back(cristal);
		gObjects.back()->setTexture(cristal);
	}
	else if (mid == 2) {
		gObjects.push_back(new EjesRGB(400.0));
	}
}
//-------------------------------------------------------------------------
void Scene::free()
{ // release memory and resources   

	for (Abs_Entity* el : gObjects){
		delete el;  el = nullptr;
	}

	for (Abs_Entity* cosa : gObjectsTrans){
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

void Scene::render(Camera const& cam) const
{
	sceneDirLight(cam);

	cam.upload(); //viewport proyect

	for (Abs_Entity* el : gObjects) {
		el->render(cam.viewMat());	//cada elemento renderiza
	}
	
	for (Abs_Entity* cosa : gObjectsTrans)
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



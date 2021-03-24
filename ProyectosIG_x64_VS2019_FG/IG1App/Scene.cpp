#include "Scene.h"
#include "CheckML.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;
//-------------------------------------------------------------------------

void Scene::init()
{
	setGL();  // OpenGL settings

	glEnable(GL_DEPTH_TEST);

	Texture* t = new Texture();
	t->load("../Bmps/baldosaC.bmp");
	gTextures.push_back(t);

	Texture* text = new Texture();
	text->load("../Bmps/baldosaP.bmp");
	gTextures.push_back(text);
	
	Texture* caja = new Texture();
	caja->load("../Bmps/container.bmp");
	gTextures.push_back(caja);

	Texture* chuches = new Texture();
	chuches->load("../Bmps/papelC.bmp");
	gTextures.push_back(chuches);

	Texture* glass = new Texture();
	glass->load("../Bmps/windowV.bmp", 255 / 2);
	gTextures.push_back(glass);

	// allocate memory and load resources
	// Lights
	// Textures

	// Graphics objects (entities) of the scene

	if (mid == 0) {

		//Rect�ngulo
		/*gObjects.push_back(new RectanguloRGB(800, 800));
		gObjects.back()->setModelMat(translate(dmat4(1), dvec3(0, 0, -100)));*/

		//gObjects.back()->setColor(dvec4(1.0, 1.0, 1.0, 0.0));
		/*gObjects.push_back(new Poligono(100, 300));
		gObjects.back()->setColor(dvec4(1.0, 1.0, 0.0, 0.0));*/
		/*gObjects.push_back(new Poligono(360, 200)); //igual hay que meterle 360 lados porque un c�rculo tiene 360 grados //Igual no
		gObjects.back()->setColor(dvec4(1.0, 0.07, 0.57, 0.0));*/


		//Serpinpi
		/*gObjects.push_back(new SerPinspi(200, 10000));
		gObjects.back()->setColor(dvec4(1.0, 1.0, 1.0, 0.0));*/


		//Tri�ngulo
		/*gObjects.push_back(new TrianguloRGB(20, 200));
		gObjects.back()->setModelMat(translate(gObjects.back()->modelMat(), dvec3(200, 0, 0)));*/

	}
	else if (mid == 1) {
		gObjects.push_back(new EjesRGB(400.0));

		gObjects.push_back(new Suelo(700, 700, 5, 5));
		gObjects.back()->setTexture(t);
		gObjects.back()->setModelMat(glm::rotate(dmat4(1), radians(-90.0), dvec3(1, 0, 0)));

		gObjects.push_back(new Estrella3D(100, 10, 100));
		gObjects.back()->setColor(dvec4(1.0, 1.0, 1.0, 0.0));
		gObjects.back()->setModelMat(glm::translate(gObjects.back()->modelMat(), dvec3(0, 300, 0)));
		gObjects.back()->setTexture(text);


		int sideCube = 200.0f;
		gObjects.push_back(new Caja(sideCube, chuches));
		gObjects.back()->setTexture(caja);
		gObjects.back()->setModelMat(glm::translate(gObjects.back()->modelMat(), dvec3(100, sideCube / 2, 0)));

		int sizePhoto = 100;
		gObjects.push_back(new Foto(sizePhoto, sizePhoto, GL_FRONT));
		gObjects.back()->setModelMat(glm::translate(dmat4(1), dvec3(-100, 20, 0)));
		gObjects.back()->setModelMat(glm::rotate(gObjects.back()->modelMat(), radians(-90.0), dvec3(1, 0, 0)));

		Texture* sandokan = new Texture();
		gTextures.push_back(sandokan);
		gObjects.back()->setTexture(sandokan);

		gObjects.push_back(new Glass(700.0, 200));
		gObjects.back()->setTexture(glass);

		gObjects.back()->setModelMat(glm::translate(gObjects.back()->modelMat(), dvec3(0, 100, 0)));
		
	}

}
//-------------------------------------------------------------------------
void Scene::free()
{ // release memory and resources   

	for (Abs_Entity* el : gObjects)
	{
		delete el;  el = nullptr;
	}
	
	for (Texture* el : gTextures)
	{
		delete el;  el = nullptr;
	}

	gTextures.clear();
	gObjects.clear();
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
//-------------------------------------------------------------------------

void Scene::render(Camera const& cam) const
{
	cam.upload(); //viewport proyect

	for (Abs_Entity* el : gObjects)
	{
		el->render(cam.viewMat());	//cada elemento renderiza
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



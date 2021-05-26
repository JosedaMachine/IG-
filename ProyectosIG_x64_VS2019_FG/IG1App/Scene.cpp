#include "Scene.h"
#include "CheckML.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>
#include "QuadricEntity.h"

using namespace glm;
Scene::Scene() {
	glEnable(GL_LIGHTING);
}
//-------------------------------------------------------------------------
void Scene::init() {
	setGL();  // OpenGL settings

	chargeTextures(); //We charge here the textures

	// Graphics objects (entities) of the scene
	if (mid == 0) {
		TIE* tie = new TIE(gTextures[6]);
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
	else if (mid == 3) {
		//gObjects.push_back(new EjesRGB(400.0));

		float radius = 100.0;
		Esfera* esfera = new Esfera(radius, 50, 50);
		Material* m = new Material();
		m->setCopper();
		esfera->setMaterial(m);
		gObjects.push_back(esfera);
		gObjects.back()->setModelMat(glm::translate(gObjects.back()->modelMat(), glm::dvec3(0, 0, radius * 2)));


		Sphere* sphere = new Sphere(radius);
		gObjects.push_back(sphere);
		gObjects.back()->setModelMat(glm::translate(gObjects.back()->modelMat(), glm::dvec3(radius * 2, 0, 0)));

		//Cambiar el color
		//Cambiar la posicion desde fuera
		//Que no haya dependencia de movimiento
	}
	else if (mid == 4) {
		Texture* t = new Texture();
		t->load("../Bmps/checker.bmp", 255);
		gTextures.push_back(t);


		t = new Texture();
		t->load("../Bmps/stones.bmp", 255);
		gTextures.push_back(t);


		gObjects.push_back(new EjesRGB(400.0));

		GridCube* cubito = new GridCube(200.0f, 2, gTextures[7], gTextures.back());
		gObjects.push_back(cubito);

		//Grid* grilla = new Grid(200, 2);
		//gObjects.push_back(grilla);

		//gObjects.back()->setTexture(gTextures.back());
	}
	else if (mid == 5) {
		gObjects.push_back(new Esfera(10000, 50, 50));
		gObjects.back()->setModelMat(translate(dmat4(1), dvec3(0, -10500, 0)));
		gObjects.back()->setColor(dvec4(0.20, 1, 0.92, 1));

		int numTies = 3;
		std::vector<TIE*> ties;

		for (int i = 0; i < numTies; i++) {
			TIE* t = new TIE(gTextures[6]);

			gObjects.push_back(t);
			ties.push_back(t);
		}
		ties[0]->setModelMat(translate(dmat4(1), dvec3(1250, 500, 0)));
		ties[0]->setModelMat(rotate(ties[0]->modelMat(), radians(300.0), dvec3(0.0, 1.0, 0.0)));

		ties[2]->setModelMat(translate(dmat4(1), dvec3(0, 500, 1250)));
	}
}

void Scene::enableDirLight() {
	dirLight->enable();
}
void Scene::disableDirLight() {
	dirLight->disable();
}
//-------------------------------------------------------------------------
void Scene::chargeTextures() {
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
	t->load("../Bmps/noche.bmp", 255 / 1.2);
	gTextures.push_back(t);




}

void Scene::brightScene() {
	dirLight->enable();
	GLfloat amb[] = { 0.25,0.25,0.25, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);
}

void Scene::darkScene() {
	//glDisable(GL_LIGHTING);
	dirLight->disable();
	GLfloat amb[] = { 0,0,0, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);
}
//-------------------------------------------------------------------------
void Scene::free()
{ // release memory and resources   

	for (Entidad* el : gObjects) {
		delete el;  el = nullptr;
	}

	for (Entidad* cosa : gObjectsTrans) {
		delete cosa;  cosa = nullptr;
	}

	for (Texture* el : gTextures) {
		delete el;  el = nullptr;
	}
	delete dirLight;
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

	dirLight = new DirLight();
	posLight = new PosLight();
}
//-------------------------------------------------------------------------
void Scene::resetGL()
{
	glClearColor(.0, .0, .0, .0);  // background color (alpha=1 -> opaque)
	glDisable(GL_DEPTH_TEST);  // disable Depth test 	
	glDisable(GL_TEXTURE_2D);
}
//-------------------------------------------------------------------------
void Scene::sceneDirLight(Camera const& cam) const {
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
void Scene::render(Camera const& cam) const {
	//Ya no se renderiza la escena así. Sino con el atributo dirLight, bastante intuitivo eh Segundo

	//sceneDirLight(cam);
	dirLight->upload(cam.viewMat());

	cam.upload(); //viewport proyect

	for (Entidad* el : gObjects) {
		el->render(cam.viewMat());	//cada elemento renderiza
	}

	for (Entidad* cosa : gObjectsTrans) {
		cosa->render(cam.viewMat());	//cada elemento renderiza
	}
}
//-------------------------------------------------------------------------
void Scene::update() {
	for (auto& o : gObjects) {
		o->update();
	}
}
//-------------------------------------------------------------------------
void Scene::changeScene(int id) {
	if (id != mid) {
		resetGL();
		free();
		mid = id;
		init();
	}
}
//-------------------------------------------------------------------------



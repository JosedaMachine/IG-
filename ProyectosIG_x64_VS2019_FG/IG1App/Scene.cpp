#include "Scene.h"
#include "CheckML.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>
#include "QuadricEntity.h"

bool Scene::lightOn = false;

using namespace glm;
Scene::Scene() {
	glEnable(GL_LIGHTING);

	dirLight = nullptr;
	posLight = nullptr;
	spotLight = nullptr;

	tieForm = nullptr;

	if(!lightOn)
	 createLights();
}
//-------------------------------------------------------------------------
void Scene::createLights() {

	lightOn = true;

	dirLight = new DirLight();
	dirLight->setPosDir({ 0, 0, -1 });
	dirLight->disable();

	posLight = new PosLight();
	posLight->setDiff({ 1, 1, 0, 1 });
	posLight->setAmb({ 0.2, 0.2, 0, 1 });
	posLight->setSpec({ 0.5, 0.5, 0.5, 1 });
	posLight->setPosDir({ 115, 115, 0 });
	posLight->disable();


	spotLight = new SpotLight();
	spotLight->disable();
}
//-------------------------------------------------------------------------
void Scene::TIEsLightsOn(bool light)
{
	tieForm->turnLights(light);
}
void Scene::orbita()
{
	tieForm->setModelMat((translate(tieForm->modelMat(), dvec3(radius * sin(tieForm->getAng()), 0, radius * cos(tieForm->getAng())))));
	tieForm->addAng(10);
}
void Scene::rota()
{
}
//-------------------------------------------------------------------------
Scene::~Scene() {
	free(); resetGL();
	if (dirLight)
		delete dirLight;
	if (posLight)
		delete posLight;
	if (spotLight)
		delete spotLight;

	delete tieForm;
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
		sphere->setColor({ 0.15, 0.28, 0.59 ,1 });
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

		GridCube* cubito = new GridCube(200.0f, 100, gTextures[7], gTextures.back());
		gObjects.push_back(cubito);
		if (spotLight) {
			spotLight->setPosDir({ 0, 0, -50 });
			spotLight->setSpot(glm::fvec3(0.0, 0.0, 1.0), 20, 0);
		}

		//Grid* grilla = new Grid(200, 2);
		//gObjects.push_back(grilla);

		//gObjects.back()->setTexture(gTextures.back());
	}
	else if (mid == 5) {
		gObjects.push_back(new EjesRGB(400.0));

		radius = 5500;

		if (posLight)
			posLight->setPosDir({ radius + 30, radius + 30, 0 });

		if(dirLight)
			dirLight->setPosDir({0, 1, 0});

		if (spotLight) {
			spotLight->setPosDir({ -radius, -radius, 50 });
			spotLight->setSpot(glm::fvec3(0.0, 0.0, -1.0), 75, 0);
		}

		Esfera* esf = new Esfera(radius, 300, 300);
		Material* m = new Material();
		m->setGold();
		esf->setMaterial(m);
		gObjects.push_back(esf);										
		gObjects.back()->setModelMat(translate(dmat4(1), dvec3(0, -radius * 1.2f, 0))); /*Y = -10500*/
		gObjects.back()->setColor(dvec4(0.20, 1, 0.92, 1));
		
		TIE_FORMATION* tieFor = new TIE_FORMATION(gTextures[6], 0.5);
		tieFor->setModelMat(translate(dmat4(1), dvec3(0, -900, 0)));
		gObjects.push_back(tieFor);

		tieForm = tieFor;
	}
}
//-------------------------------------------------------------------------
void Scene::enableDirLight() {
	if (dirLight)
		dirLight->enable();
}
//-------------------------------------------------------------------------
void Scene::disableDirLight() {
	if (dirLight)
		dirLight->disable();
}
//-------------------------------------------------------------------------
void Scene::disablePosLight()
{
	if (posLight)
		posLight->disable();
}
//-------------------------------------------------------------------------
void Scene::enablePosLight()
{
	if (posLight)
		posLight->enable();
}
//-------------------------------------------------------------------------
void Scene::disableSpotLight() {
	if (spotLight)
		spotLight->disable();
}
//-------------------------------------------------------------------------
void Scene::enableSpotLight() {
	if (spotLight)
		spotLight->enable();
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
//-------------------------------------------------------------------------
void Scene::brightScene() {
	if(dirLight)
		dirLight->enable();

	if(posLight)
		posLight->enable();
	GLfloat amb[] = { 0.25,0.25,0.25, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);
}
//-------------------------------------------------------------------------
void Scene::darkScene() {
	//glDisable(GL_LIGHTING);
	if(dirLight)
		dirLight->disable();

	if (posLight)
		posLight->disable();

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
	//Ya no se renderiza la escena as�. Sino con el atributo dirLight, bastante intuitivo eh Segundo

	//sceneDirLight(cam);
	if (dirLight)
		dirLight->upload(cam.viewMat());
	if (posLight)
		posLight->upload(cam.viewMat());
	if (spotLight)
		spotLight->upload(cam.viewMat());
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



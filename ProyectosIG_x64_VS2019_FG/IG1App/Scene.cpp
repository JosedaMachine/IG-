#include "Scene.h"
#include "CheckML.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>
#include "QuadricEntity.h"

bool Scene::lightOn = false;

using namespace glm;
Scene::Scene() {
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
	//dirLight->disable();
	lights.push_back(dirLight);

	posLight = new PosLight();
	posLight->setDiff({ 1, 1, 0, 1 });
	posLight->setAmb({ 0.2, 0.2, 0, 1 });
	posLight->setSpec({ 0.5, 0.5, 0.5, 1 });
	posLight->setPosDir({ 115, 115, 0 });
	//posLight->disable();
	lights.push_back(posLight);

	spotLight = new SpotLight();
	//spotLight->disable();
	lights.push_back(spotLight);
}
//-------------------------------------------------------------------------
void Scene::TIEsLightsOn(bool light)
{
	tieForm->turnLights(light);
}
//-------------------------------------------------------------------------
void Scene::orbita() {

	dmat4 mat = tieForm->modelMat();
	//tieForm->setModelMat((translate(dmat4(1), dvec3(radius * sin(tieForm->getAng()), -radius , radius * cos(tieForm->getAng())))));
	////tieForm->setModelMat(rotate(tieForm->modelMat(), radians(1.0), dvec3(0, 0.0f, 1)));
	//tieForm->setModelMat(rotate(tieForm->modelMat(), radians(90.0), dvec3(1, 0, 0)));
	//tieForm->addAng(0.1);

	//Rotacion Horizontal
	//para sacar el angulo perpendicular a la esfera podemos usar el teoream del coseno.
	// Dada una posicion inicial c, una posicion final b, y el centro de la esfera a,
	// usamos Rotar en Y : cosA = (a^2 - b^2 - c^2)/(-2*b*c). Y luego ang(A) = cos^-1(cos(A));
	// El mismo concepto para rotar en X

	//ESTO DA ASCO
	//Lo mete en el centro de la esfera
	mat = translate(mat, dvec3(0.0, -radius - 200, 0.0));

	//Rota el objeto y con ello sus ejes
	mat = rotate(mat, radians(1.0), dvec3(1, 0.0, 0));

	//Lo posiciona donde de verdad tiene que ir con sus ejes rotados
	mat = translate(mat, dvec3(0.0, radius + 200, 0.0));

	tieForm->setModelMat(mat);
}
//-------------------------------------------------------------------------
void Scene::rota()
{
	tieForm->setModelMat(rotate(tieForm->modelMat(), radians(1.0), dvec3(0.0, 1.0, 0.0)));
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
	if (mid == 1) {
		glEnable(GL_LIGHTING);

		TIE* tie = new TIE(gTextures[6], 0.05);
		gObjects.push_back(tie);
		gObjects.push_back(new EjesRGB(400.0));
	}
	else if (mid == 2) {
		glDisable(GL_LIGHTING);
		//Anillo cuadrado
		gObjects.push_back(new EjesRGB(400.0));
		gObjects.push_back(new AnilloCuadrado());
	}
	else if (mid == 3) {
		glEnable(GL_LIGHTING);
		gObjects.push_back(new EjesRGB(400.0));
		gObjects.push_back(new CuboConTapas(100));
	}
	else if (mid == 4) {
		glEnable(GL_LIGHTING);

		gObjects.push_back(new EjesRGB(400.0));

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
	else if (mid == 5) {
		glEnable(GL_LIGHTING);

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
	}
	else if (mid == 6) {
		glEnable(GL_LIGHTING);

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
	else if (mid == 7) {
		glDisable(GL_LIGHTING);
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
	else if(mid == 8) {
		glDisable(GL_LIGHTING);

		gObjects.push_back(new EjesRGB(400.0));

		gObjects.push_back(new Suelo(700, 700, 5, 5));
		gObjects.back()->setTexture(gTextures[0]);
		gObjects.back()->setModelMat(glm::rotate(dmat4(1), radians(-90.0), dvec3(1, 0, 0)));

		gObjects.push_back(new Estrella3D(50, 10, 100));
		gObjects.back()->setColor(dvec4(1.0, 1.0, 1.0, 0.0));
		gObjects.back()->setModelMat(glm::translate(gObjects.back()->modelMat(), dvec3(-200, 300, -200)));
		gObjects.back()->setTexture(gTextures[1]);

		int sideCube = 200.0f;
		gObjects.push_back(new Caja(sideCube, gTextures[3]));
		gObjects.back()->setTexture(gTextures[2]);
		gObjects.back()->setModelMat(glm::translate(gObjects.back()->modelMat(), dvec3(-sideCube, sideCube / 2, -sideCube)));

		gObjectsTrans.push_back(new Glass(700.0, 200));
		gObjectsTrans.back()->setTexture(gTextures[4]);
		gObjectsTrans.back()->setModelMat(glm::translate(gObjectsTrans.back()->modelMat(), dvec3(0, 100, 0)));

		int sizePhoto = 100;
		gObjects.push_back(new Foto(sizePhoto, sizePhoto, GL_FRONT));
		gObjects.back()->setModelMat(glm::translate(dmat4(1), dvec3(0, 5, 0)));
		gObjects.back()->setModelMat(glm::rotate(gObjects.back()->modelMat(), radians(-90.0), dvec3(1, 0, 0)));

		Texture* t = new Texture();
		gTextures.push_back(t);
		gObjects.back()->setTexture(t);
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
	for (Light* light : lights){
		if (light) light->enable();
	}

	if (tieForm) tieForm->turnLights(true);

	GLfloat amb[] = { 0.25,0.25,0.25, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);
}
//-------------------------------------------------------------------------
void Scene::darkScene() {
	for (Light* light : lights) {
		if (light) light->disable();
	}

	if (tieForm) tieForm->turnLights(false);

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



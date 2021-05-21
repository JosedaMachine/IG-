#include "Entity.h"
#include "QuadricEntity.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>
#include "IG1App.h"
#include "Material.h"

using namespace glm;

//-------------------------------------------------------------------------

void Abs_Entity::upload(dmat4 const& modelViewMat) const
{ 
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(modelViewMat));  // transfers modelView matrix to the GPU
}
//-------------------------------------------------------------------------
class EntityWithMaterial : public Abs_Entity {
public:
	EntityWithMaterial() : Abs_Entity() { };
	virtual ~EntityWithMaterial() { };
	void setMaterial(Material* matl) { material = matl; };
protected:
	Material* material = nullptr;
};
//-------------------------------------------------------------------------

EjesRGB::EjesRGB(GLdouble l): Abs_Entity()
{
  mMesh = Mesh::createRGBAxes(l);
}
//-------------------------------------------------------------------------

EjesRGB::~EjesRGB() 
{ 
	delete mMesh; mMesh = nullptr; 
};
//-------------------------------------------------------------------------

void EjesRGB::render(dmat4 const& modelViewMat) const 
{
	if (mMesh != nullptr) {
		glEnable(GL_COLOR_MATERIAL);

		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glLineWidth(4);
		mMesh->render();
		glLineWidth(1);

		glDisable(GL_COLOR_MATERIAL);
	}
}

TrianguloRGB::TrianguloRGB(GLdouble rd, float rad) {
	mMesh = Mesh::createTrianguloRGB(rd);

	radius = rad;
	angLoc = 0;
	angGlob = 0;
}

TrianguloRGB::~TrianguloRGB() {
	delete mMesh; mMesh = nullptr;

}
void TrianguloRGB::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);

		//glPolygonMode(GL_BACK, GL_LINE); 
		glPolygonMode(GL_BACK, GL_LINE);
		mMesh->render();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

void TrianguloRGB::update() {
	angLoc = angLoc + 10.0;
	angGlob = angGlob + 0.05;

	setModelMat(translate(dmat4(1), dvec3(radius* cos(angGlob), radius * sin(angGlob),0)));

	setModelMat(rotate(modelMat(), radians(-angLoc), dvec3(0, 0, 1))); //Pasamos negativo porque los ángulos pues son iguales para todos los sitios

}

Poligono::Poligono(GLuint numL, GLdouble rd) {
	mMesh = Mesh::generaPoligono(numL,  rd);
}

Poligono::~Poligono() {
	delete mMesh; mMesh = nullptr;

}

void Poligono::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		glColor3d(mColor.r, mColor.g, mColor.b);
		glLineWidth(2);
		upload(aMat);
		mMesh->render();

		glLineWidth(1);
		glColor3d(1, 1, 1);
	}
}

SerPinspi::SerPinspi(GLuint rd, GLdouble numP) {
	mMesh = Mesh::generaSierpinski(rd, numP);
}

SerPinspi::~SerPinspi()
{
	delete mMesh; mMesh = nullptr;
}

void SerPinspi::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		glColor3d(mColor.r, mColor.g, mColor.b);
		glLineWidth(2);
		upload(aMat);
		mMesh->render();

		glLineWidth(1);
		glColor3d(1, 1, 1);
	}
}

Rectangulo::Rectangulo(GLdouble w, GLdouble h) {
	mMesh = Mesh::generaRectangulo(w, h);
}

Rectangulo::~Rectangulo()
{
	delete mMesh; mMesh = nullptr;
}

void Rectangulo::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		glColor3d(mColor.r, mColor.g, mColor.b);
		glLineWidth(2);
		upload(aMat);
		glPolygonMode(GL_BACK, GL_LINE);
		mMesh->render();

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glLineWidth(1);
		glColor3d(1, 1, 1);
	}
}



RectanguloRGB::RectanguloRGB(GLdouble w, GLdouble h) {
	mMesh = Mesh::generaRectanguloRGB(w, h);
}

RectanguloRGB::~RectanguloRGB()
{
	delete mMesh; mMesh = nullptr;
}

void RectanguloRGB::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		glColor3d(mColor.r, mColor.g, mColor.b);
		glLineWidth(2);
		upload(aMat);
		glPolygonMode(GL_BACK, GL_POINT);
		mMesh->render();


		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glLineWidth(1);
		glColor3d(1, 1, 1);
	}
}


Estrella3D::Estrella3D(GLdouble re, GLuint np, GLdouble h) {
	mMesh = Mesh::generaEstrellaTexCor(re, np,h);

	angZ = 0;
	angY = 0;
}

Estrella3D::~Estrella3D() {
	delete mMesh; mMesh = nullptr;
}

void Estrella3D::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		glColor3d(mColor.r, mColor.g, mColor.b);
		glLineWidth(2);

		mTexture->bind(GL_REPLACE);

		upload(aMat);
		/*glPolygonMode(GL_BACK, GL_LINE);
		glPolygonMode(GL_FRONT, GL_LINE);*/

		mMesh->render();

		aMat = modelViewMat * rotate(modelMat(), radians(180.0), dvec3(1, 0, 0));
		upload(aMat);
		mMesh->render();


		mTexture->unbind();
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glLineWidth(1);
		glColor3d(1, 1, 1);
	}
}

void Estrella3D::update() {
	angZ += 3.0f;
	angY += 3.0f;

	setModelMat(translate(dmat4(1), dvec3(-200, 300, -200)));

	setModelMat(rotate(modelMat(), -radians(angZ), dvec3(0, 1, 0))); //Pasamos negativo porque los �ngulos pues son iguales para todos los sitios

	setModelMat(rotate(modelMat(), -radians(angY), dvec3(0, 0, 1)));
}
//-------------------------------------------------------------------------

Caja::Caja(GLdouble ld, Texture* interi)
{
	mMesh = Mesh::generaContCuboTexCor(ld);
	interior = interi;
}

Caja::~Caja()
{
	delete mMesh; mMesh = nullptr;
}

/// <summary>
/// Renderiza la caja
/// </summary>
/// <param name="modelViewMat"></param>
void Caja::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		glColor3d(mColor.r, mColor.g, mColor.b);
		upload(aMat);


		//Activamos el modo cool 
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);//No se ve lo de atrás
		
		//Hacemos Bind de la texture
		mTexture->bind(GL_REPLACE);

		//Renderizamos
		mMesh->render();
		//Quitamos la textura
		mTexture->unbind();

		glCullFace(GL_FRONT);	//No se ve lo de delante

		interior->bind(GL_REPLACE);

		upload(aMat);
		mMesh->render();

		interior->unbind();

		glDisable(GL_CULL_FACE);

		//Se restauran los valores por defecto
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glLineWidth(1);
		glColor3d(1, 1, 1);
	}
}

void Caja::update()
{
}

Suelo::Suelo(GLdouble w, GLdouble h, GLuint rw, GLuint  rh)
{
	mMesh = Mesh::generaRectanguloTexCor(w, h, rw, rh);
}

Suelo::~Suelo()
{
	delete mMesh; mMesh = nullptr;
}

void Suelo::render(glm::dmat4 const& modelViewMat) const
{
	if(mMesh!= nullptr)
	{
		dmat4 aMat = modelViewMat * mModelMat;
		upload(aMat);	
		mTexture->bind(GL_REPLACE);
		mMesh->render();
		mTexture->unbind();
	}
}

void Suelo::update()
{
	
}

Foto::Foto(GLsizei width, GLsizei height, GLuint buffer)
{
	mTexture = new Texture();

	mTexture->loadColorBuffer(width, height, buffer);

	mMesh = Mesh::generaRectanguloTexCor(width, height, 1, 1);
}

Foto::~Foto()
{
}

void Foto::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr)
	{
		dmat4 aMat = modelViewMat * mModelMat;
		upload(aMat);
		mTexture->bind(GL_REPLACE);
		mMesh->render();
		mTexture->unbind();
	}
}

void Foto::update()
{
	mTexture->loadColorBuffer(IG1App::s_ig1app.winWidth(), IG1App::s_ig1app.winheigth(), GL_FRONT);
}

Glass::Glass(GLdouble w, GLdouble h){
	mMesh = Mesh::generaCristalera(w,h);
}

Glass::~Glass()
{
	delete mMesh; mMesh = nullptr;
}

void Glass::render(glm::dmat4 const& modelViewMat) const {
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);

		//Activar modo Blender3D
		//Activamos la máscara: ponerla a false
		glDepthMask(GL_FALSE);
		glEnable(GL_BLEND); //Activar blending
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//glEnable(GL_CULL_FACE);

		//Hacemos Bind de la texture
		mTexture->bind(GL_REPLACE);
		//glCullFace(GL_BACK);

		//Renderizamos
		mMesh->render();
		//Quitamos la textura
		mTexture->unbind();

		//glDisable(GL_CULL_FACE);
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
	}
}

void Glass::update()
{
}

PoligonoText::PoligonoText(GLuint numL, GLdouble rd)
{
	mMesh = Mesh::generaPolygonTexCor(rd, numL);
}

PoligonoText::~PoligonoText()
{
	delete mMesh; mMesh = nullptr;
}

void PoligonoText::render(glm::dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);

		//Activar modo Blender3D
		glDepthMask(GL_FALSE);
		glEnable(GL_BLEND); //Activar blending
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//glEnable(GL_CULL_FACE);

		//Hacemos Bind de la texture
		if(mTexture != nullptr) mTexture->bind(GL_REPLACE);
		//glCullFace(GL_BACK);

		//Renderizamos
		mMesh->render();
		//Quitamos la textura
		if (mTexture != nullptr) mTexture->unbind();

		//glDisable(GL_CULL_FACE);
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
	}
}

Planta::Planta(GLdouble w, GLdouble h)
{
	mMesh = Mesh::generaRectanguloTexCor(w, h, 1, 1);
}
//-------------------------------------------------------------------------

void Planta::render(glm::dmat4 const& modelViewMat) const{
	if (mMesh != nullptr) {
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0);

		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		mTexture->setWrap(GL_REPEAT);
		mTexture->bind(GL_REPLACE);
		mMesh->render();

		aMat = rotate(aMat, radians(60.0), dvec3(0.0, 1.0, 0.0)); // rotamos la matriz
		upload(aMat);
		mMesh->render();

		aMat = rotate(aMat, radians(60.0), dvec3(0.0, 1.0, 0.0)); // rotamos la matriz
		upload(aMat);
		mMesh->render();

		mTexture->unbind();

		glDisable(GL_ALPHA_TEST);
	}
}

AnilloCuadrado::AnilloCuadrado()
{
	mMesh = IndexMesh::generaAnilloCuadradoIndexado(30,30);
}

AnilloCuadrado::~AnilloCuadrado()
{
	delete mMesh; mMesh = nullptr;
}

void AnilloCuadrado::render(glm::dmat4 const& modelViewMat) const
{
	glEnable(GL_COLOR_MATERIAL);
	
	mMesh->render();

	glDisable(GL_COLOR_MATERIAL);
}

CuboConTapas::CuboConTapas(GLdouble l)
{
	mMesh = IndexMesh::generaCuboConTapadIndexado(l);
}

CuboConTapas::~CuboConTapas()
{
	delete mMesh; mMesh = nullptr;
}

void CuboConTapas::render(glm::dmat4 const& modelViewMat) const{
	glEnable(GL_COLOR_MATERIAL);

	glColor3f(0.0, 1.0, 0.0);

	mMesh->render();

	glColor3f(1.0, 1.0, 1.0);

	glDisable(GL_COLOR_MATERIAL);
}

void CompoundEntity::addEntity(Entidad* ae){
	gObjects.push_back(ae);
}

CompoundEntity::~CompoundEntity(){
	for (Entidad* ae : gObjects) delete ae;
	for (Entidad* ae : gObjectsTranslucid) delete ae;
	gObjects.clear();
	gObjectsTranslucid.clear();
}

void CompoundEntity::render(glm::dmat4 const& modelViewMat) const {
	for (Entidad* ae : gObjects) ae->render(modelViewMat * modelMat());

	for (Entidad* ae : gObjectsTranslucid) ae->render(modelViewMat * modelMat());
}

TIE::TIE(Texture* t, GLdouble size){
	float radioDiscoCono = 100 * size;
	//Cuerpo
	Sphere* esfera = new Sphere(130.0 * size);
	gObjects.push_back(esfera);
	//Front
	Cylinder* cono = new Cylinder(radioDiscoCono, radioDiscoCono, 40.0);
	glm::dmat4 mAux = cono->modelMat();
	mAux = translate(mAux, dvec3(0, 0, 101));
	cono->setModelMat(mAux);

	gObjects.push_back(cono);
	//Front
	Disk* disco = new Disk(radioDiscoCono, 0, 360);
	glm::dmat4 mAux2 = disco->modelMat();
	mAux2 = translate(mAux2, dvec3(0, 0, 141));
	disco->setModelMat(mAux2);
	gObjects.push_back(disco);

	//Eje transversal
	Cylinder* cono1 = new Cylinder(50.0 * size, 50 * size, 200.0);
	glm::dmat4 mAux3 = cono1->modelMat();
	mAux3 = rotate(mAux3, radians(90.0), dvec3(0, 1.0, 0));
	mAux3 = translate(mAux3, dvec3(0, 0, 120));
	cono1->setModelMat(mAux3);
	gObjects.push_back(cono1);

	//Eje transversal
	Cylinder* cono2 = new Cylinder(50.0 * size, 50* size, 200.0);
	glm::dmat4 mAux4 = cono2->modelMat();
	mAux4 = rotate(mAux4, radians(-90.0), dvec3(0, 1.0, 0));
	mAux4 = translate(mAux4, dvec3(0, 0, 120));
	cono2->setModelMat(mAux4);
	gObjects.push_back(cono2);

	//Ala1
	PoligonoText* ala2 = new PoligonoText(6, 500 * size);
	glm::dmat4 mAux6 = ala2->modelMat();
	mAux6 = rotate(mAux6, radians(90.0), dvec3(0, 1.0, 0));
	mAux6 = translate(mAux6, dvec3(0, 0, 320));
	ala2->setModelMat(mAux6);
	gObjectsTranslucid.push_back(ala2);
	gObjectsTranslucid.back()->setColor(dvec4(1.0, 1.0, 1.0, 0.0));
	gObjectsTranslucid.back()->setTexture(t);
	//Ala2
	PoligonoText* ala1 = new PoligonoText(6, 500 * size);
	glm::dmat4 mAux5 = ala1->modelMat();
	mAux5 = rotate(mAux5, radians(-90.0), dvec3(0, 1.0, 0));
	mAux5 = translate(mAux5, dvec3(0, 0, 320));
	ala1->setModelMat(mAux5);
	gObjectsTranslucid.push_back(ala1);
	gObjectsTranslucid.back()->setColor(dvec4(1.0, 1.0, 1.0, 0.0));
	gObjectsTranslucid.back()->setTexture(t);
}

TIE::~TIE(){
	int n = 0;
}

void TIE::render(glm::dmat4 const& modelViewMat) const{
	/*dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);*/
	//CompoundEntity::render(aMat);
	// 
	CompoundEntity::render(modelViewMat);
}

ConeMbR::ConeMbR(GLdouble h, GLdouble r, GLuint n){
	int m = 3;
	dvec3* perfil = new dvec3[m];
	perfil[0] = dvec3(0.0, 0.0, 0.0);
	perfil[1] = dvec3(r, 0.0, 0.0);
	perfil[2] = dvec3(0.0, h, 0.0);

	//Igual eres un poco PS
	mMesh = MbR::generaIndexMeshByRevolution(m, n, perfil);
}

ConeMbR::~ConeMbR()
{
	delete mMesh; mMesh = nullptr;
}

void ConeMbR::render(glm::dmat4 const& modelViewMat) const{
	glEnable(GL_COLOR_MATERIAL);

	glColor3f(0.0, 1.0, 0.0);

	mMesh->render();

	glColor3f(1.0, 1.0, 1.0);

	glDisable(GL_COLOR_MATERIAL);
}

Esfera::Esfera(GLdouble r, GLdouble p, GLuint m){
	dvec3* perfil = new dvec3[p];

	float angIni = 270.0;

	float angToAdd = (180.0 / (p-1));
	vec2 c(0, 0);

	for (int i = 0; i < p ; i++) {
		perfil[i] = dvec3(c.x + r * cos(radians(angIni)), c.y + r * sin(radians(angIni)), 0);
		angIni += angToAdd;
	}

	mMesh = MbR::generaIndexMeshByRevolution(p, m, perfil);
}

Esfera::~Esfera()
{
	delete mMesh; mMesh = nullptr;
}

void Esfera::render(glm::dmat4 const& modelViewMat) const
{
	glEnable(GL_COLOR_MATERIAL);

	glColor3f(mColor.r, mColor.g, mColor.b);

	//glLineWidth(4);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
	upload(aMat);
	mMesh->render();

	//glLineWidth(1);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glColor3f(1.0, 1.0, 1.0);

	glDisable(GL_COLOR_MATERIAL);
}

Grid::Grid(GLdouble r, GLint nDiv) {

	mMesh = IndexMesh::generaGridTex(r, nDiv);
}

Grid::~Grid() {
	delete mMesh; mMesh = nullptr;
}

void Grid::render(glm::dmat4 const& modelViewMat) const {

	//glColor3f(0.15, 0.28, 0.59);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	mTexture->bind(GL_REPLACE);
	
	//Añado esto para que se pueda mover y rotar desde fuera
	dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
	upload(aMat);

	mMesh->render();

	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//glColor3f(1.0, 1.0, 1.0);

	mTexture->unbind();

}

GridCube::GridCube(GLdouble r, GLint nDiv, Texture* up, Texture* sides){
	top = up;
	side = sides;

	//top
	gObjects.push_back(new Grid(r, nDiv));
	gObjects.back()->setTexture(top);
	gObjects.back()->setModelMat(translate(gObjects.back()->modelMat(), dvec3(0, r / 2, 0)));
	//Down
	gObjects.push_back(new Grid(r, nDiv));
	gObjects.back()->setTexture(top);
	gObjects.back()->setModelMat(translate(dmat4(1), dvec3(0, -r / 2, 0)));
	////N
	gObjects.push_back(new Grid(r, nDiv));
	gObjects.back()->setTexture(side);
	//Si lo roto, rotan tambien sus ejes. Por lo tanto, si hago una translacion en Y, se va a aplicar sobre su eje Y , que correspondria a X o Z en funcion de como se haya rotado
	//Por eso es mejor, primero Translate y luego rotate (usando en la segunda el modelMat);
	gObjects.back()->setModelMat(translate(dmat4(1), dvec3(r / 2, 0, 0)));
	gObjects.back()->setModelMat(rotate(gObjects.back()->modelMat(), radians(90.0), dvec3(1.0, 0.0, 0.0)));
	//Ahora roto en Z porque ahora la Z es su Y (hemos rotado en X 90 grados, luego el resto de ejes han rotado 90 grados)
	//Como hacer para que el sistema de coordenadas sea global y no local??????????????
	gObjects.back()->setModelMat(rotate(gObjects.back()->modelMat(), radians(90.0), dvec3(0.0, 0.0, 1.0)));
	//Para que las piedras vayan hacia abajo
	gObjects.back()->setModelMat(rotate(gObjects.back()->modelMat(), radians(90.0), dvec3(0.0, 1.0, 0.0)));

	////W
	gObjects.push_back(new Grid(r, nDiv));
	gObjects.back()->setTexture(side);
	gObjects.back()->setModelMat(translate(dmat4(1), dvec3(0, 0, r / 2)));
	gObjects.back()->setModelMat(rotate(gObjects.back()->modelMat(), radians(90.0), dvec3(1.0, 0.0, 0.0)));
	gObjects.back()->setModelMat(rotate(gObjects.back()->modelMat(), radians(90.0), dvec3(0.0, 1.0, 0.0)));
	//gObjects.back()->setModelMat(rotate(gObjects.back()->modelMat(), radians(90.0), dvec3(1.0, 0.0,0.0)));
	// 

	////E
	gObjects.push_back(new Grid(r, nDiv));
	gObjects.back()->setTexture(side);
	gObjects.back()->setModelMat(translate(dmat4(1), dvec3(0, 0, -r / 2)));
	gObjects.back()->setModelMat(rotate(gObjects.back()->modelMat(), radians(90.0), dvec3(1.0, 0.0, 0.0)));
	gObjects.back()->setModelMat(rotate(gObjects.back()->modelMat(), radians(90.0), dvec3(0.0, 1.0, 0.0)));


	////S
	gObjects.push_back(new Grid(r, nDiv));
	gObjects.back()->setTexture(side);
	gObjects.back()->setModelMat(translate(dmat4(1), dvec3(-r / 2, 0, 0)));
	gObjects.back()->setModelMat(rotate(gObjects.back()->modelMat(), radians(90.0), dvec3(1.0, 0.0, 0.0)));
	gObjects.back()->setModelMat(rotate(gObjects.back()->modelMat(), radians(90.0), dvec3(0.0, 0.0, 1.0)));
	gObjects.back()->setModelMat(rotate(gObjects.back()->modelMat(), radians(90.0), dvec3(0.0, 1.0, 0.0)));
}

GridCube::~GridCube(){
	delete mMesh; mMesh = nullptr;
}

void GridCube::render(glm::dmat4 const& modelViewMat) const{
	CompoundEntity::render(modelViewMat);
}

void GridCube::setTextures(Texture* top_, Texture* side_){
	top = top_;
	side = side_;
}

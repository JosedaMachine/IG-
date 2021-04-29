#include "Entity.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>
#include "IG1App.h"

using namespace glm;

//-------------------------------------------------------------------------

void Abs_Entity::upload(dmat4 const& modelViewMat) const
{ 
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(modelViewMat));  // transfers modelView matrix to the GPU
}
//-------------------------------------------------------------------------
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

Estrella3D::~Estrella3D()
{
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

}

void AnilloCuadrado::render(glm::dmat4 const& modelViewMat) const
{
	mMesh->render();
}

CuboConTapas::CuboConTapas(GLdouble l)
{
	mMesh = IndexMesh::generaCuboConTapadIndexado(l);
}

CuboConTapas::~CuboConTapas()
{

}

void CuboConTapas::render(glm::dmat4 const& modelViewMat) const
{
	glEnable(GL_COLOR_MATERIAL);

	glColor3f(0.0, 1.0, 0.0);

	mMesh->render();

	glColor3f(1.0, 1.0, 1.0);

	glDisable(GL_COLOR_MATERIAL);
}

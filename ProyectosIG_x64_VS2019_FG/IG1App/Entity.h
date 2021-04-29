//#pragma once
#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Mesh.h"
#include "IndexMesh.h"
#include "Texture.h"
#include "CheckML.h"
#include "EntityWithIndexMesh.h"

class IG1App;

using namespace glm;
//-------------------------------------------------------------------------

class Abs_Entity : public Entidad  // abstract class
{
public:
	Abs_Entity(): mModelMat(1.0) {};  // 4x4 identity matrix
	virtual ~Abs_Entity() {};

	Abs_Entity(const Abs_Entity& e) = delete;  // no copy constructor
	Abs_Entity& operator=(const Abs_Entity& e) = delete;  // no copy assignment

	virtual void render(glm::dmat4 const& modelViewMat) const = 0;  // abstract method
	void setColor(dvec4 mCol) {
		mColor = mCol;
	}

	void setTexture(Texture* tex) { mTexture = tex; }

	// modeling matrix
	glm::dmat4 const& modelMat() const { return mModelMat; };
	void setModelMat(glm::dmat4 const& aMat) { mModelMat = aMat; };

	//M�todo update
	virtual void update() {};
protected:

	Mesh* mMesh = nullptr;   // the mesh
	glm::dmat4 mModelMat;    // modeling matrix //rotaciones, escalas, etc
	glm::dvec4 mColor;
	Texture* mTexture = nullptr;
	
	// transfers modelViewMat to the GPU
	virtual void upload(glm::dmat4 const& mModelViewMat) const; 

};
//-------------------------------------------------------------------------

class EjesRGB : public Abs_Entity 
{
public:
	explicit EjesRGB(GLdouble l);
	~EjesRGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};


class TrianguloRGB : public Abs_Entity
{
public:
	explicit TrianguloRGB(GLdouble rd, float radius);
	~TrianguloRGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;

	void update();

private:
	double angGlob;
	double angLoc;

	float radius;
};

class Poligono : public Abs_Entity
{
public:
	explicit Poligono(GLuint numL, GLdouble rd);
	~Poligono();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

class PoligonoText : public Abs_Entity
{
public:
	explicit PoligonoText(GLuint numL, GLdouble rd);
	~PoligonoText();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

class SerPinspi : public Abs_Entity
{
public:
	explicit SerPinspi(GLuint rd, GLdouble numP);
	~SerPinspi();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

class Rectangulo : public Abs_Entity
{
public:
	explicit Rectangulo(GLdouble w, GLdouble h);
	~Rectangulo();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

class RectanguloRGB : public Abs_Entity
{
public:
	explicit RectanguloRGB(GLdouble w, GLdouble h);
	~RectanguloRGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

class Estrella3D : public Abs_Entity
{
public:
	explicit Estrella3D(GLdouble re, GLuint np, GLdouble h);
	~Estrella3D();
	virtual void render(glm::dmat4 const& modelViewMat) const;

	virtual void update();

private:

	double angZ, angY;
};

class Caja : public Abs_Entity
{
public:
	explicit Caja(GLdouble ld, Texture* interi);
	~Caja();
	virtual void render(glm::dmat4 const& modelViewMat) const;

	virtual void update();

private:
	Texture* interior;
};

class Suelo : public Abs_Entity
{
public:
	explicit Suelo(GLdouble w, GLdouble h, GLuint rw, GLuint  rh);
	~Suelo();
	virtual void render(glm::dmat4 const& modelViewMat) const;

	virtual void update();

private:
	
};

class Foto : public Abs_Entity
{
public:
	explicit Foto(GLsizei width, GLsizei height, GLuint buffer);
	~Foto();
	virtual void render(glm::dmat4 const& modelViewMat) const;

	virtual void update();

private:

};

class Glass : public Abs_Entity
{
public:
	explicit Glass(GLdouble w, GLdouble h);
	~Glass();
	virtual void render(glm::dmat4 const& modelViewMat) const;

	virtual void update();

private:

};

class Planta : public Abs_Entity
{
public:
	explicit Planta(GLdouble w, GLdouble h);
	virtual ~Planta() {};
	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update() {};
};

class AnilloCuadrado : public Abs_Entity
{
public:
	explicit AnilloCuadrado();
	~AnilloCuadrado();
	virtual void render(glm::dmat4 const& modelViewMat) const;

	
};

class CuboConTapas : public EntityWithIndexMesh
{
public:
	explicit CuboConTapas(GLdouble l);
	~CuboConTapas();
	virtual void render(glm::dmat4 const& modelViewMat) const;


};
//-------------------------------------------------------------------------

#endif //_H_Entities_H_
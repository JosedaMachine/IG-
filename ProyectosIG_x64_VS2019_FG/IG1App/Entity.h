//#pragma once
#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Mesh.h"
#include "IndexMesh.h"
#include "Texture.h"
#include "CheckML.h"
#include "Material.h"
#include "EntityWithIndexMesh.h"
#include "MbR.h"
#include "Light.h"

class IG1App;

using namespace glm;
//-------------------------------------------------------------------------

class Abs_Entity : public Entidad  // abstract class
{
public:
	Abs_Entity() : mModelMat(1.0) {};  // 4x4 identity matrix
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
//-----------------------------------------------------------
class EntityWithMaterial : public Abs_Entity {
public:
	EntityWithMaterial() : Abs_Entity() { };
	virtual ~EntityWithMaterial() { };

	void setMaterial(Material* matl) { material = matl; };
protected:
	Material* material = nullptr;
};
//-----------------------------------------------------------
class CompoundEntity : public Abs_Entity {
public:
	CompoundEntity() {};
	virtual ~CompoundEntity();

	void addEntity(Entidad* ae);

	virtual void render(glm::dmat4 const& modelViewMat) const;
	virtual void update() {};
protected:
	//Vector de entidades Opacas y Translucidas
	std::vector<Entidad*> gObjects, gObjectsTranslucid;
};
//-------------------------------------------------------------------------
class TIE : public CompoundEntity {
public:
	explicit TIE(Texture* t, GLdouble size = 1.0, bool hasLight = false);
	virtual ~TIE();
	virtual void render(glm::dmat4 const& modelViewMat) const;
	void turnLight(bool turn);

	SpotLight* getSpotLight() { return light; }
private:
	SpotLight* light = nullptr;
};
//-------------------------------------------------------------------------
class TIE_FORMATION : public CompoundEntity {
public:
	explicit TIE_FORMATION(Texture* t, GLdouble size = 1.0);
	virtual ~TIE_FORMATION();
	virtual void render(glm::dmat4 const& modelViewMat) const;

	void turnLights(bool light);

private:

};
//-------------------------------------------------------------------------

class EjesRGB : public Abs_Entity
{
public:
	explicit EjesRGB(GLdouble l);
	virtual ~EjesRGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};


class TrianguloRGB : public Abs_Entity
{
public:
	explicit TrianguloRGB(GLdouble rd, float radius);
	virtual ~TrianguloRGB();
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
	virtual ~Poligono();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

class PoligonoText : public Abs_Entity
{
public:
	explicit PoligonoText(GLuint numL, GLdouble rd);
	virtual ~PoligonoText();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

class SerPinspi : public Abs_Entity
{
public:
	explicit SerPinspi(GLuint rd, GLdouble numP);
	virtual ~SerPinspi();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

class Rectangulo : public Abs_Entity
{
public:
	explicit Rectangulo(GLdouble w, GLdouble h);
	virtual ~Rectangulo();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

class RectanguloRGB : public Abs_Entity
{
public:
	explicit RectanguloRGB(GLdouble w, GLdouble h);
	virtual ~RectanguloRGB();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

class Estrella3D : public Abs_Entity
{
public:
	explicit Estrella3D(GLdouble re, GLuint np, GLdouble h);
	virtual ~Estrella3D();
	virtual void render(glm::dmat4 const& modelViewMat) const;

	virtual void update();

private:

	double angZ, angY;
};

class Caja : public Abs_Entity
{
public:
	explicit Caja(GLdouble ld, Texture* interi);
	virtual ~Caja();
	virtual void render(glm::dmat4 const& modelViewMat) const;

	virtual void update();

private:
	Texture* interior;
};

class Suelo : public Abs_Entity
{
public:
	explicit Suelo(GLdouble w, GLdouble h, GLuint rw, GLuint  rh);
	virtual ~Suelo();
	virtual void render(glm::dmat4 const& modelViewMat) const;

	virtual void update();

private:

};

class Foto : public Abs_Entity
{
public:
	explicit Foto(GLsizei width, GLsizei height, GLuint buffer);
	virtual ~Foto();
	virtual void render(glm::dmat4 const& modelViewMat) const;

	virtual void update();

private:

};

class Glass : public Abs_Entity
{
public:
	explicit Glass(GLdouble w, GLdouble h);
	virtual ~Glass();
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
	virtual ~AnilloCuadrado();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

class CuboConTapas : public EntityWithIndexMesh
{
public:
	explicit CuboConTapas(GLdouble l);
	virtual ~CuboConTapas();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

class ConeMbR : public Abs_Entity
{
public:
	explicit ConeMbR(GLdouble h, GLdouble r, GLuint n);
	virtual ~ConeMbR();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

class Esfera : public EntityWithMaterial
{
public:
	explicit Esfera(GLdouble r, GLdouble p, GLuint m);
	virtual ~Esfera();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

class Grid : public Abs_Entity
{
public:
	explicit Grid(GLdouble r, GLint nDiv);
	virtual ~Grid();
	virtual void render(glm::dmat4 const& modelViewMat) const;
};

class GridCube : public CompoundEntity
{
public:
	explicit GridCube(GLdouble r, GLint nDiv, Texture* top_, Texture* side_);
	virtual ~GridCube();
	virtual void render(glm::dmat4 const& modelViewMat) const;

	void setTextures(Texture* top, Texture* side);
private:
	Texture* top, * side;
};
//-------------------------------------------------------------------------

#endif //_H_Entities_H_
#pragma once
#include "Entity.h"
class QuadricEntity : public Abs_Entity 
{
public:
	QuadricEntity();
	~QuadricEntity() { gluDeleteQuadric(q); };

protected:
	GLUquadricObj* q;
};

class Sphere : public QuadricEntity
{
public:
	Sphere(GLdouble rr); // r es el radio de la esfera
	void render(glm::dmat4 const& modelViewMat) const;
protected:
	GLdouble r;
};

class Cylinder : public QuadricEntity
{
public:
	Cylinder(GLdouble rs, GLdouble ri, GLdouble hei); 
	void render(glm::dmat4 const& modelViewMat) const;
protected:
	GLdouble rS, rI, h;
};

class Disk : public QuadricEntity
{
public:
	Disk(GLdouble re, GLdouble ri, int slice); // r es el radio de la esfera
	void render(glm::dmat4 const& modelViewMat) const;
protected:
	GLdouble rE, rI;

	int slices;
};

class PartialDisk : public QuadricEntity
{
public:
	PartialDisk(GLdouble re, GLdouble ri, GLdouble an); // r es el radio de la esfera
	void render(glm::dmat4 const& modelViewMat) const;
protected:
	GLdouble rE, rI, ang;
};
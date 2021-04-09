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
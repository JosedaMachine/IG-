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

};
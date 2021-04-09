#include "QuadricEntity.h"

QuadricEntity::QuadricEntity()
{
	q = gluNewQuadric();
}

Sphere::Sphere(GLdouble rr) { r = rr; }

void Sphere::render(glm::dmat4 const& modelViewMat) const
{
	dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);
	// Aquí se puede fijar el color de la esfera así:
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(0.15,0.28,0.59);
	// Aquí se puede fijar el modo de dibujar la esfera:
	//gluQuadricDrawStyle(q, GLU_SILHOUETTE);
	gluSphere(q, r, 50, 50);
	// Aquí se debe recuperar el color:
	glColor3f(1.0, 1.0, 1.0);
}

Cylinder::Cylinder(GLdouble rs, GLdouble ri, GLdouble hei) { rS = rs; rI = ri; h = hei; }

void Cylinder::render(glm::dmat4 const& modelViewMat) const
{
	dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);
	// Aquí se puede fijar el color de la esfera así:
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(0.27, 0.08, 0.06);
	// Aquí se puede fijar el modo de dibujar la esfera:
	//gluQuadricDrawStyle(q, GLU_SILHOUETTE);
	gluCylinder(q, rS, rI, h, 50, 50);
	// Aquí se debe recuperar el color:
	glColor3f(1.0, 1.0, 1.0);
}

Disk::Disk(GLdouble re, GLdouble ri)
{
	rE = re;
	rI = ri;
}

void Disk::render(glm::dmat4 const& modelViewMat) const
{
	dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);
	// Aquí se puede fijar el color de la esfera así:
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(0.27, 0.08, 0.06);
	// Aquí se puede fijar el modo de dibujar la esfera:
	//gluQuadricDrawStyle(q, GLU_SILHOUETTE);
	gluDisk(q,rI,rE,50,360);
	// Aquí se debe recuperar el color:
	glColor3f(1.0, 1.0, 1.0);
}

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
	// glEnable(GL_COLOR_MATERIAL);
	// glColor3f(...);
	// Aquí se puede fijar el modo de dibujar la esfera:
	// gluQuadricDrawStyle(q, ...);
	gluSphere(q, r, 50, 50);
	// Aquí se debe recuperar el color:
	// glColor3f(1.0, 1.0, 1.0);
}

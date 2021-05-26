#include "Material.h"

 void Material::upload() {
	glMaterialfv(face, GL_AMBIENT, value_ptr(ambient));
	glMaterialfv(face, GL_DIFFUSE, value_ptr(diffuse));
	glMaterialfv(face, GL_SPECULAR, value_ptr(specular));
	glMaterialf(face, GL_SHININESS, expF);
	glShadeModel(sh);
	//glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE); // Defecto
}

void Material::setCopper() {
	ambient = { 0.19125, 0.0735, 0.0225, 1 };
	diffuse = { 0.7038, 0.27048, 0.0828, 1 };
	specular = { 0.256777, 0.137622, 0.086014, 1 };
	expF = 12.8;
}

void Material::setGold()
{
	ambient = { 0.24725, 0.1995, 0.0745, 1 };
	diffuse = { 0.75164, 0.60648, 0.2264, 1 };
	specular = { 0.628281, 0.555802, 0.366065, 1 };
	expF = 51.2;
}

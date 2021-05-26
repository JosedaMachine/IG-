#include "Light.h"

GLuint Light::cont = 0;

Light::Light()
{
	if (cont < GL_MAX_LIGHTS) {
		id = GL_LIGHT0 + cont;
		++cont;
		glEnable(id);
	}

}

void Light::uploadL(){
	// Transfiere las características de la luz a la GPU
	glLightfv(id, GL_AMBIENT, value_ptr(ambient));
	glLightfv(id, GL_DIFFUSE, value_ptr(diffuse));
	glLightfv(id, GL_SPECULAR, value_ptr(specular));
}

void Light::disable(){
	if (id < GL_LIGHT0 + GL_MAX_LIGHTS) glDisable(id);
}

void Light::enable() {
	if (id < GL_LIGHT0 + GL_MAX_LIGHTS) glEnable(id);
}

void Light::setAmb(glm::fvec4 amb) {
	ambient = amb; 
	uploadL();
}

void Light::setDiff(glm::fvec4 amb)
{
	diffuse = amb;
	uploadL();
}

void Light::setSpec(glm::fvec4 amb)
{
	specular = amb;
	uploadL();
}
//----------------------------------------------

void DirLight::upload(glm::dmat4 const& modelViewMat)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(modelViewMat));
	glLightfv(id, GL_POSITION, value_ptr(posDir));
	uploadL();
}

void DirLight::setPosDir(glm::fvec3 dir) {
	posDir = glm::fvec4(dir, 0.0);
}

//----------------------------------------------
void PosLight::upload(glm::dmat4 const& modelViewMat)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(modelViewMat));
	glLightfv(id, GL_POSITION, value_ptr(posDir));
	glLightf(id, GL_CONSTANT_ATTENUATION, kc);
	glLightf(id, GL_LINEAR_ATTENUATION, kl);
	glLightf(id, GL_QUADRATIC_ATTENUATION, kq);
	uploadL();
}

void PosLight::setPosDir(glm::fvec3 dir)
{
	posDir = glm::fvec4(dir, 1.0);
}

void PosLight::setAtte(GLfloat kc_, GLfloat kl_, GLfloat kq_)
{
	kc = kc_;
	kl = kl_;
	kq = kq_;
}

//----------------------------------------------

void SpotLight::upload(glm::dmat4 const& modelViewMat)
{
	PosLight::upload(modelViewMat);
	glLightfv(id, GL_SPOT_DIRECTION, value_ptr(direction));
	glLightf(id, GL_SPOT_CUTOFF, cutoff);
	glLightf(id, GL_SPOT_EXPONENT, exp);


	//Por qué no se hace upload??????
	//uploadL();
}

// Ojo al 0.0: la dirección de emisión del foco es vector
void SpotLight::setSpot(glm::fvec3 dir, GLfloat cf, GLfloat e)
{
	direction = glm::fvec4(dir, 0.0);
	cutoff = cf;
	exp = e;
}

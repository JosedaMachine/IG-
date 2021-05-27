#include "Camera.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;

//-------------------------------------------------------------------------
Camera::Camera(Viewport* vp) : mViewPort(vp), mViewMat(1.0), mProjMat(1.0),
xRight(vp->width() / 2.0), xLeft(-xRight),
yTop(vp->height() / 2.0), yBot(-yTop)
{
	setPM();
}
//-------------------------------------------------------------------------
void Camera::uploadVM() const
{
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(mViewMat)); // transfers view matrix to the GPU 
}
//-------------------------------------------------------------------------
void Camera::setAxes() {
	mRight = row(mViewMat, 0);
	mUpward = row(mViewMat, 1);
	mFront = -row(mViewMat, 2);
}
//-------------------------------------------------------------------------
void Camera::changePrj()
{
	bOrto = !bOrto;
	setPM();
}
//-------------------------------------------------------------------------
void Camera::setCenital()
{
	mEye = dvec3(0, 1000, 0);
	mLook = dvec3(0, 10, 0);
	mUp = dvec3(1, 0, 0);
	
	mAng = -90;
	setVM();
}
//-------------------------------------------------------------------------
void Camera::setVM() {
	mViewMat = lookAt(mEye, mLook, mUp);  // glm::lookAt defines the view matrix 
	setAxes();
}
//-------------------------------------------------------------------------
void Camera::set2D()
{
	mEye = dvec3(0, 0, 500);
	mLook = dvec3(0, 0, 0);
	mUp = dvec3(0, 1, 0);
	setVM();
}
//-------------------------------------------------------------------------
void Camera::set3D() {
	mEye = dvec3(500, 500, 500);
	mLook = dvec3(0, 10, 0);
	mUp = dvec3(0, 1, 0);

	mRadio = 1000;
	//Porque la c�mara empieza en -45
	mAng = -45;

	setVM();
}
//-------------------------------------------------------------------------
void Camera::moveLR(GLdouble cs) {
	mEye += mRight * cs;
	mLook += mRight * cs;
	setVM();
}
//-------------------------------------------------------------------------
void Camera::moveFB(GLdouble cs) {
	mEye += mFront * cs;
	mLook += mFront * cs;
	setVM();
}
//-------------------------------------------------------------------------
void Camera::moveUD(GLdouble cs) {
	mEye += mUpward * cs;
	mLook += mUpward * cs;
	setVM();
}
//-------------------------------------------------------------------------
void Camera::orbit(GLdouble incAng, GLdouble incY) {
	mAng += incAng;
	mEye.x = mLook.x + cos(radians(mAng)) * mRadio;
	mEye.z = mLook.z - sin(radians(mAng)) * mRadio;
	mEye.y += incY;
	setVM();
}
//-------------------------------------------------------------------------
void Camera::setSize(GLdouble xw, GLdouble yh) {
	xRight = xw / 2.0;
	xLeft = -xRight;
	yTop = yh / 2.0;
	yBot = -yTop;
	setPM();
}
//-------------------------------------------------------------------------
void Camera::setScale(GLdouble s) {
	mScaleFact -= s;
	if (mScaleFact < 0) mScaleFact = 0.01;
	setPM();
}
//-------------------------------------------------------------------------
void Camera::setPM() {
	if (bOrto) {//si orto esta a true la vista sera ortogonal
		//(left, right, bottom, top, near, far)
		mProjMat = ortho(xLeft * mScaleFact, xRight * mScaleFact, yBot * mScaleFact, yTop * mScaleFact, mNearVal, mFarVal);
	}
	else {//si no, sera en perspectiva
		//Para que no se vaya al carajo, ponemos top como 2 * yTop, si lo ponemos a mNearVal = 1, se ve muy lejos
		mProjMat = frustum(xLeft * mScaleFact, xRight * mScaleFact, yBot * mScaleFact, yTop * mScaleFact, 2 * yTop, mFarVal);
		//near es 2*top para un fov de 60. Si se quiere un fov de 90 near = top
	}
	uploadPM();
}
//-------------------------------------------------------------------------
void Camera::uploadPM() const {
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(value_ptr(mProjMat)); // transfers projection matrix to the GPU
	glMatrixMode(GL_MODELVIEW);
}
//-------------------------------------------------------------------------



#include "IG1App.h"
#include "CheckML.h"
#include <iostream>

using namespace std;

//-------------------------------------------------------------------------
// static single instance (singleton pattern)

IG1App IG1App::s_ig1app;  // default constructor (constructor with no parameters)

//-------------------------------------------------------------------------

void IG1App::close()  
{
	if (!mStop) {  // if main loop has not stopped
		cout << "Closing glut...\n";
		glutLeaveMainLoop();  // stops main loop and destroy the OpenGL context
		mStop = true;   // main loop stopped  
	}
	free();
}
//-------------------------------------------------------------------------

void IG1App::run()   // enters the main event processing loop
{
	if (mWinId == 0) { // if not initialized
		init();       // initialize the application 
		glutMainLoop();      // enters the main event processing loop 
		return;
		mStop = true;  // main loop has stopped  
	}
}
//-------------------------------------------------------------------------

void IG1App::init()
{
	// create an OpenGL Context
	iniWinOpenGL();   

	// create the scene after creating the context 
	// allocate memory and resources
	mViewPort = new Viewport(mWinW, mWinH); //glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT)
	mCamera = new Camera(mViewPort);
	mCamera1 = new Camera(mViewPort);

	mScene = new Scene;
	//mScene1 = new Scene;

	//mCamera->set2D();
	//mCamera1->set2D();

	//mScene1->setMid(5);
	mScene->setMid(5);

	mScene->init();
	//mScene1->init();

	GLuintmLastUpdateTime = glutGet(GLUT_ELAPSED_TIME);
}
//-------------------------------------------------------------------------

void IG1App::iniWinOpenGL() 
{  // Initialization
	cout << "Starting glut...\n";
	int argc = 0;
	glutInit(&argc, nullptr);
		
	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);  // GLUT_CORE_PROFILE
	glutInitContextFlags(GLUT_DEBUG);		// GLUT_FORWARD_COMPATIBLE

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glutInitWindowSize(mWinW, mWinH);   // window size
	//glutInitWindowPosition (140, 140);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH /*| GLUT_STENCIL*/); // RGBA colors, double buffer, depth buffer and stencil buffer   
	
	mWinId = glutCreateWindow("IG1App");  // with its associated OpenGL context, return window's identifier 
	
	// Callback registration
	glutReshapeFunc(s_resize);
	glutKeyboardFunc(s_key);
	glutSpecialFunc(s_specialKey);
	glutDisplayFunc(s_display);
	
	glutMouseFunc(s_mouse);
	glutMotionFunc(s_motion);
	glutMouseWheelFunc(s_mouseWheel);

	//glutIdleFunc(s_update);

	cout << glGetString(GL_VERSION) << '\n';
	cout << glGetString(GL_VENDOR) << '\n';
}
//-------------------------------------------------------------------------

void IG1App::free() 
{  // release memory and resources
	delete mScene; mScene = nullptr;
	delete mScene1; mScene1 = nullptr;
	delete mCamera; mCamera = nullptr;
	delete mCamera1; mCamera1 = nullptr;
	delete mViewPort; mViewPort = nullptr;
}
//-------------------------------------------------------------------------

void IG1App::display() const   
{  // double buffering
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clears the back buffer

	if (m2Scenes) display2Scenes();
	else if (m2Vistas) display2Vistas();
	else mScene->render(*mCamera);  // uploads the viewport and camera to the GPU
	
	glutSwapBuffers();	// swaps the front and back buffer
}

void IG1App::display2Scenes() const {
	Camera auxCam = *mCamera; //camara auxiliar para renderizar las vistas
	Camera auxCam1 = *mCamera1; //camara auxiliar para renderizar las vistas

	Viewport auxVP = *mViewPort; //se copia el puntero del puerto de vista para no alterar el original

	//Para que sea dos vistas tienen que tener la misma altura, pero anchura la mitad
	mViewPort->setSize(mWinW / 2, mWinH);

	//Asignamos el tama�o a la camara, segun el VP
	auxCam.setSize(mViewPort->width(), mViewPort->height());
	auxCam1.setSize(mViewPort->width(), mViewPort->height());

	//2D
	mViewPort->setPos(0, 0);
	mScene->render(auxCam);
	//auxCam.set2D();

	//3D
	mViewPort->setPos(mWinW / 2, 0);
	//auxCam.setCenital();
	//auxCam.set3D();
	mScene1->render(auxCam1);

	*mViewPort = auxVP; //restauramos el puntero de vista
}

void IG1App::display2Vistas() const
{
	Camera auxCam = *mCamera; //camara auxiliar para renderizar las vistas
	Viewport auxVP = *mViewPort; //se copia el puntero del puerto de vista para no alterar el original
	//Para que sea dos vistas tienen que tener la misma altura, pero anchura la mitad
	mViewPort->setSize(mWinW / 2, mWinH);
	auxCam.setSize(mViewPort->width(), mViewPort->height());

	mViewPort->setPos(0, 0);
	mScene->render(auxCam);

	mViewPort->setPos(mWinW / 2, 0);
	auxCam.setCenital();
	mScene->render(auxCam);
	
	*mViewPort = auxVP; //restauramos el puntero de vista
}

//-------------------------------------------------------------------------
void IG1App::resize(int newWidth, int newHeight) {
	mWinW = newWidth; mWinH = newHeight;

	// Resize Viewport to the new window size
	mViewPort->setSize(newWidth, newHeight);

	// Resize Scene Visible Area such that the scale is not modified
	mCamera->setSize(mViewPort->width(), mViewPort->height()); 

	mCamera1->setSize(mViewPort->width(), mViewPort->height()); 
}
//-------------------------------------------------------------------------

void IG1App::key(unsigned char key, int x, int y) 
{
	bool need_redisplay = true;
	int mdf = glutGetModifiers(); // returns the modifiers (Shift, Ctrl, Alt)

	switch (key) {
	case 27:  // Escape key 
		glutLeaveMainLoop();  // stops main loop and destroy the OpenGL context
	case '+':
		mCamera->setScale(+0.09/*+0.01*/);  // zoom in  (increases the scale)
		break;
	case '-':
		mCamera->setScale(-0.09 /*- 0.01*/);  // zoom out (decreases the scale)
		break;
	case 'l':
		if (m2Scenes) {
			if (mCoord.x >= (mWinW / 2)) {
				mCamera1->set3D();
				mScene1->set2D(false);
			}
			else {
				mCamera->set3D();
				mScene->set2D(false);
			}
		}
		else {
			mCamera->set3D();
			mScene->set2D(false);
		}
		break;
	case 'o':
		if (m2Scenes) {
			if (mCoord.x >= (mWinW / 2)) {
				mCamera1->set2D();
				mScene1->set2D(true);
			}
			else {
				mCamera->set2D();
				mScene->set2D(true);
			}
		}
		else {
			mCamera->set2D();
			mScene->set2D(true);
		}
		break;
	case 'u':
		if(mCoord.x >= (mWinW / 2))mScene1->update();
		else mScene->update();
		break;
	case 'k':
		m2Scenes = !m2Scenes;
		if (m2Vistas)m2Vistas = false;
		break;
	case 'j':
		m2Vistas = !m2Vistas;
		if (m2Scenes)m2Scenes = false;
		break;
	case 'm':
		//Rotar en el eje hortizontal
		mCamera->orbit(1, 0);;		
		break;
	case 'n':
		//Rotar en el eje hortizontal 
		mCamera->orbit(-1, 0);
		break;
	case 'c':
			//Eje Vertical
			mCamera->orbit(0, 40);
		break;	
	case 'v':
			//Eje Vertical
			mCamera->orbit(0, -40);
		break;
	case 'g':
		if(mScene->getMid() == 5)mScene->TIEsLightsOn(true);
		break;
	case 'y':
		if (mScene->getMid() == 5) mScene->orbita();
		break;
	case 'b':
		if (mScene->getMid() == 5) mScene->rota();
		break;
	case 't':
		if (mScene->getMid() == 5)mScene->TIEsLightsOn(false);
		break;
	case 'q':
		mScene->enableDirLight();
		break;
	case 'w':
		mScene->disableDirLight();
		break;	
	case 'e':
		mScene->darkScene();
		break;
	case 'r':
		mScene->brightScene();
		break;
	case 'a':
		mScene->enablePosLight();
		break;
	case 's':
		mScene->disablePosLight();	
		break;
	case 'z':
		mScene->enableSpotLight();
		break;
	case 'x':
		mScene->disableSpotLight();
		break;
	case '0':
		mScene->changeScene(0);
		break;
	case '1':
		mScene->changeScene(1);
		break;
	case '2':
		mScene->changeScene(2);
		break;
	case '3':
		mScene->changeScene(3);
		break;
	case '4':
		mScene->changeScene(4);
		break;
	case '5':
		mScene->changeScene(5);
		break;
	case 'p':
		if (m2Scenes) {
			if (mCoord.x >= (mWinW / 2)) {
				mCamera1->changePrj();
				mCamera1->setScale(0.00);
			}
			else {
				mCamera->changePrj();
				mCamera->setScale(0.00);
			}
		}
		else {
			mCamera->changePrj();
			mCamera->setScale(0.00);
		}
		break;
	default:
		need_redisplay = false;
		break;
	} //switch

	if (need_redisplay)
		glutPostRedisplay(); // marks the window as needing to be redisplayed -> calls to display()
}
//-------------------------------------------------------------------------

void IG1App::specialKey(int key, int x, int y) {
	bool need_redisplay = true;
	int mdf = glutGetModifiers(); // returns the modifiers (Shift, Ctrl, Alt)
	
	switch (key) {
	case GLUT_KEY_RIGHT:
		if (mdf == GLUT_ACTIVE_CTRL)
			//mCamera->pitch(-1);   // rotates -1 on the X axis
			mCamera->moveLR(-1);
		else
			//mCamera->pitch(1);    // rotates 1 on the X axis
			mCamera->moveLR(1);
		break;
	case GLUT_KEY_LEFT:
		if (mdf == GLUT_ACTIVE_CTRL)
			//mCamera->yaw(1);      // rotates 1 on the Y axis 
			mCamera->moveUD(1);
		else 
			//mCamera->yaw(-1);     // rotate -1 on the Y axis 
			mCamera->moveUD(-1);
		break;
	case GLUT_KEY_UP:
		//mCamera->roll(1);    // rotates 1 on the Z axis
		mCamera->moveFB(1);
		break;
	case GLUT_KEY_DOWN:
		//mCamera->roll(-1);   // rotates -1 on the Z axis
		mCamera->moveFB(-1);
		break;
	default:
		need_redisplay = false;
		break;
	}//switch

	if (need_redisplay)
		glutPostRedisplay(); // marks the window as needing to be redisplayed -> calls to display()
}

void IG1App::update() {
	if (glutGet(GLUT_ELAPSED_TIME) - GLuintmLastUpdateTime >= 60.0) {
		mScene->update();
	}

	GLuintmLastUpdateTime = glutGet(GLUT_ELAPSED_TIME);
}
void IG1App::mouse(int b, int s, int x, int y){
	mCoord = dvec2(x, y);
	mBot = b;
}

void IG1App::motion(int x, int y) {
	dvec2 newP(x, y);
	dvec2 displacement = mCoord - newP;
	mCoord = newP;

	if (mBot == GLUT_RIGHT_BUTTON) {
		if (m2Scenes) {
			if (mCoord.x >= (mWinW / 2)) {
				mCamera1->moveLR(displacement.x);
				mCamera1->moveUD(-displacement.y);

			}
			else{
				mCamera->moveLR(displacement.x);
				mCamera->moveUD(-displacement.y);
			}
		}
		else{
			mCamera->moveLR(displacement.x);
			mCamera->moveUD(-displacement.y);
		}
	}
	else if(mBot == GLUT_LEFT_BUTTON) {

		if (m2Scenes){
			if (mCoord.x >= (mWinW / 2)) {
				if(!mScene1->get2D())  
					mCamera1->orbit(displacement.x * 0.05f, -displacement.y);
			}
			else  if(!mScene->get2D()) 
				mCamera->orbit(displacement.x * 0.05f, -displacement.y);
		}
		else if(!mScene->get2D()){
			mCamera->orbit(displacement.x * 0.05f, -displacement.y);
		}

		//if(mCoord.x >= (mWinW / 2) && m2Vistas) mCamera1->orbit(displacement.x * 0.05f, -displacement.y);
		//else mCamera->orbit(displacement.x * 0.05f, -displacement.y);
	}
	glutPostRedisplay();//renderiza la escena
}

void IG1App::mouseWheel(int n, int d, int x, int y){
	if (!glutGetModifiers())
	{
		if (m2Scenes && mCoord.x >= (mWinW / 2))
			mCamera1->moveFB(d * 10);
		else mCamera->moveFB(d * 10);
	}
	else{
		if (GLUT_ACTIVE_CTRL){
			if (m2Scenes && mCoord.x >= (mWinW / 2)) mCamera1->setScale(d);
			else mCamera->setScale(d);
		}
	}

	glutPostRedisplay();
}

void IG1App::s_mouse(int button, int state, int x, int y){
	s_ig1app.mouse(button,state,x,y);
}

void IG1App::s_motion(int x, int y){
	s_ig1app.motion(x, y);
}
void IG1App::s_mouseWheel(int n, int d, int x, int y){
	s_ig1app.mouseWheel(n, d, x, y);
}
//-------------------------------------------------------------------------


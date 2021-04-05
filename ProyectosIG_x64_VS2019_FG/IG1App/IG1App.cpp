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
	mScene = new Scene;
	
	mCamera->set2D();
	mScene->init();

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

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

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
	
	cout << glGetString(GL_VERSION) << '\n';
	cout << glGetString(GL_VENDOR) << '\n';
}
//-------------------------------------------------------------------------

void IG1App::free() 
{  // release memory and resources
	delete mScene; mScene = nullptr;
	delete mCamera; mCamera = nullptr;
	delete mViewPort; mViewPort = nullptr;
}
//-------------------------------------------------------------------------

void IG1App::display() const   
{  // double buffering
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clears the back buffer

	if (m2Vistas) display2Vistas();

	mScene->render(*mCamera);  // uploads the viewport and camera to the GPU
	
	glutSwapBuffers();	// swaps the front and back buffer
}

void IG1App::display2Vistas() const
{
	Camera auxCam = *mCamera; //camara auxiliar para renderizar las vistas
	Viewport auxVP = *mViewPort; //se copia el puntero del puerto de vista para no alterar el original

	//Para que sea dos vistas tienen que tener la misma altura, pero anchura la mitad
	mViewPort->setSize(mWinW / 2, mWinH);

	auxCam.setSize(mViewPort->width(), mViewPort->height());

	//Asignamos el tamaño a la camara, segun el VP
	auxCam.setSize(mViewPort->width(), mViewPort->height());




	*mViewPort = auxVP; //restauramos el puntero de vista
}

//-------------------------------------------------------------------------

void IG1App::resize(int newWidth, int newHeight) 
{
	mWinW = newWidth; mWinH = newHeight;

	// Resize Viewport to the new window size
	mViewPort->setSize(newWidth, newHeight);

	// Resize Scene Visible Area such that the scale is not modified
	mCamera->setSize(mViewPort->width(), mViewPort->height()); 
}
//-------------------------------------------------------------------------

void IG1App::key(unsigned char key, int x, int y) 
{
	bool need_redisplay = true;
	
	switch (key) {
	case 27:  // Escape key 
		glutLeaveMainLoop();  // stops main loop and destroy the OpenGL context
	case '+':
		mCamera->setScale(+0.01);  // zoom in  (increases the scale)
		break;
	case '-':
		mCamera->setScale(-0.01);  // zoom out (decreases the scale)
		break;
	case 'l':
		mCamera->set3D();
		break;
	case 'o':
		mCamera->set2D();
		break;
	case 'u':
		mScene->update();
		break;
	case 'k':
		m2Vistas = !m2Vistas;
		break;
	case 's':
		//Rotar en el eje vertical
		mCamera->orbit(0,-40);
		break;
	case 'w':
		//Rotar en el eje vertical
		mCamera->orbit(0,40);
		break;
	case 'd':
		//Rotar en el eje hortizontal
		mCamera->orbit(1,0);
		break;
	case 'a':
		//Rotar en el eje hortizontal
		mCamera->orbit(-1,0);
		break;
	case '0':
		mScene->changeScene(0);
		break;
	case '1':
		mScene->changeScene(1);
		break;
	case 'p':
		mCamera->changePrj();
		mCamera->setScale(0.00);
		break;
	default:
		need_redisplay = false;
		break;
	} //switch

	if (need_redisplay)
		glutPostRedisplay(); // marks the window as needing to be redisplayed -> calls to display()
}
//-------------------------------------------------------------------------

void IG1App::specialKey(int key, int x, int y) 
{
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

void IG1App::update()
{
	if (glutGet(GLUT_ELAPSED_TIME) - GLuintmLastUpdateTime >= 60.0) {
		mScene->update();
	}

	GLuintmLastUpdateTime = glutGet(GLUT_ELAPSED_TIME);
}
//-------------------------------------------------------------------------


//#pragma once
#ifndef _H_IG1App_H_
#define _H_IG1App_H_

//#include <Windows.h>
//#include <gl/GL.h>    // OpenGL
//#include <gl/GLU.h>   // OpenGL Utility Library
//#include <GL/glut.h>  // OpenGL Utility Toolkit

#include <GL/freeglut.h>  // OpenGL Utility Toolkit
#include <glm.hpp>        // OpenGL Mathematics

#include "Viewport.h"
#include "Camera.h"
#include "Scene.h"

//-------------------------------------------------------------------------

class IG1App
{
public:  
	// static single instance (singleton pattern)
	static IG1App s_ig1app;

	IG1App(IG1App const & J) = delete; // no copy constructor
	void operator =(IG1App const & J) = delete; // no copy assignment
	
	// Viewport position and size
	Viewport const& viewPort() { return *mViewPort; };
	// Camera position, view volume and projection
	Camera const& camera() { return *mCamera; };
	// Graphics objects of the scene
	Scene const& scene() { return *mScene; };


	void run();    // the main event processing loop
	void close();  // the application

	int winWidth() { return mWinW; }
	int winheigth() { return mWinH; }
	
protected:

	IG1App() {};
	~IG1App() { close(); };

	void init();
	void iniWinOpenGL();
	void free();   
 
	void display() const;   // the scene
	void display2Vistas() const; //the scene divide en 2 viewports
	void resize(int newWidth, int newHeight);   // the viewport (without changing the scale) 
	void key(unsigned char key, int x, int y);  // keypress event
	void specialKey(int key, int x, int y);     // keypress event for special characters
	void update();
	void glutIdleFunc();
	
	

	void mouse(int b, int s, int x, int y);
	void motion(int x, int y);
	void mouseWheel(int n, int d, int x, int y);

	// static callbacks 
	static void s_display() { s_ig1app.display(); };
	static void s_resize(int newWidth, int newHeight) { s_ig1app.resize(newWidth, newHeight); };
	static void s_key(unsigned char key, int x, int y) { s_ig1app.key(key, x, y); };
	static void s_specialKey(int key, int x, int y) { s_ig1app.specialKey(key, x, y); };
	static void s_mouse(int button, int state, int x, int y);
	static void s_motion(int x, int y);
	static void s_mouseWheel(int n, int d, int x, int y);
	//static void s_update() { update(); };

	// Viewport position and size
	Viewport *mViewPort = nullptr;
	// Camera position, view volume and projection
	Camera *mCamera = nullptr;
	// Graphics objects of the scene
	Scene *mScene = nullptr;
	Scene* mScene1 = nullptr;

	bool mStop = false; // main event processing loop
	bool m2Vistas = false; //visualizar dos vistas
	int mWinId = 0;	    // window's identifier
	int mWinW = 800;    // window's width 
	int mWinH = 600;    // window's height

	//Atributos de rat�n
	dvec2 mCoord;
	int mBot;

private:
	float GLuintmLastUpdateTime;
	bool animActivated;
};
//-------------------------------------------------------------------------

#endif //_H_IG1App_H_

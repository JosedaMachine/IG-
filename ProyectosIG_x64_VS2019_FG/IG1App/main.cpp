
#include "IG1App.h"
#include <iostream>

#include <GL/freeglut.h> //OpenGL Utility Library
#include <glm.hpp>; //OpenGL Mathematics


#include "Viewport.h";
#include "Camera.h";
#include "Scene.h"; 

//-------------------------------------------------------------------------

int ctrl_handler(int event)   // callback
{
	if (event == CTRL_CLOSE_EVENT) { // when the user closes the console 
		IG1App::s_ig1app.close();
		return 1;
	}
	else return 0;
}
//-------------------------------------------------------------------------

int main(int argc, char *argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Check Memory Leaks
	SetConsoleCtrlHandler((PHANDLER_ROUTINE)(ctrl_handler), 1);   // callback registration
	system("chcp 1252"); // Change Code Page (identifier)  
	
	try {
		std::cout << "Starting application...\n";
		IG1App::s_ig1app.run();
		std::cout << "Closing application...\n";
	}
	catch (std::exception & e) {
		std::cout << e.what() << '\n';
		std::cin.ignore(INT_MAX, '\n');    
	}
	catch (...) { 
		std::cout << "ERROR: Closing application...\n"; 
	    std::cin.ignore(INT_MAX, '\n');    
	};

    return 0;
}
//-------------------------------------------------------------------------



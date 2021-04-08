//#pragma once
#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Camera.h"
#include "Entity.h"
#include "Texture.h"

#include <vector>

//-------------------------------------------------------------------------

class Scene	
{ 
public:
	Scene() {};
	~Scene() { free(); resetGL(); };

	Scene(const Scene& s) = delete;  // no copy constructor
	Scene& operator=(const Scene& s) = delete;  // no copy assignment
		
	void init();

	void render(Camera const& cam) const;

	void update();

	void changeScene(int id);
	void setMid(int scene) { mid = scene; }
	void set2D(bool dimension) { es2D = dimension; }
	bool get2D() { return es2D; }
	
protected:
	void free();
	void setGL();
	void resetGL();

	std::vector<Abs_Entity*> gObjects;  // Entities (graphic objects) of the scene
	std::vector<Abs_Entity*> gObjectsTrans;  // Entities (graphic objects) of the scene
	std::vector<Texture*> gTextures;

	int mid = 0;
	bool es2D = true;
};
//-------------------------------------------------------------------------

#endif //_H_Scene_H_


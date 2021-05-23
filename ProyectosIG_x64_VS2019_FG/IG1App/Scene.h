//#pragma once
#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Camera.h"
#include "Entity.h"
#include "Texture.h"
#include "Light.h"

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

	void enableDirLight();

	void disableDirLight();

	void chargeTextures();
	
protected:
	void free();
	void setGL();
	void resetGL();

	void sceneDirLight(Camera const& cam) const;

	std::vector<Entidad*> gObjects;  // Entities (graphic objects) of the scene
	std::vector<Entidad*> gObjectsTrans;  // Entities (graphic objects) of the scene
	std::vector<Texture*> gTextures;

	int mid = 0;
	DirLight* dirLight;
	bool es2D = true;
};
//-------------------------------------------------------------------------

#endif //_H_Scene_H_


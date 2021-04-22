#pragma once
#include "Mesh.h"
#include <vector>

class IndexMesh : public Mesh{

public:
	IndexMesh(){
		mPrimitive = GL_TRIANGLES;
	}

	~IndexMesh()K;

	virtual void render() const;
	virtual void draw() const;




protected:

	GLuint* vIndices = nullptr;
	GLuint nNumIndices = 0;


};
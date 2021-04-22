#pragma once
#include "Mesh.h"
#include <vector>

class IndexMesh : public Mesh{

public:
	IndexMesh()
	{
		mPrimitive = GL_TRIANGLES;
	}

	~IndexMesh(){
		delete[] vIndices;
	}

	virtual void rendexr() const;

protected:

	GLuint* vIndices = nullptr;
	GLuint nNumIndices = 0;


};
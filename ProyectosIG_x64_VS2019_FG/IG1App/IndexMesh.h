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

	virtual void render() const;
	virtual void draw() const;

	static IndexMesh* generaAnilloCuadradoIndexado(float outSide, float inSide);

	static IndexMesh* generaCuboConTapadIndexado(GLdouble l);

	static IndexMesh* generateGrid(GLdouble lado, GLuint nDiv);

	static IndexMesh* generaGridTex(GLdouble lado, GLuint numDiv);

	void buildNormalVectors();

protected:

	GLuint* vIndices = nullptr;
	GLuint nNumIndices = 0;

};
#pragma once
#include <GL/freeglut.h>
#include <glm.hpp>


#include "IndexMesh.h"
#include "Texture.h"
#include "CheckML.h"
#include "Entidad.h"

class EntityWithIndexMesh : public Entidad
{
public:
	EntityWithIndexMesh() : mModelMat(1.0) {};  // 4x4 identity matrix
	virtual ~EntityWithIndexMesh() {};

	EntityWithIndexMesh(const EntityWithIndexMesh& e) = delete;  // no copy constructor
	EntityWithIndexMesh& operator=(const EntityWithIndexMesh& e) = delete;  // no copy assignment

	virtual void render(glm::dmat4 const& modelViewMat) const = 0;  // abstract method
	void setColor(glm::dvec4 mCol) {
		mColor = mCol;
	}

	void setTexture(Texture* tex) { mTexture = tex; }

	// modeling matrix
	glm::dmat4 const& modelMat() const { return mModelMat; };
	void setModelMat(glm::dmat4 const& aMat) { mModelMat = aMat; };

	//M�todo update
	virtual void update() {};
protected:

	IndexMesh* mMesh = nullptr;   // the mesh
	glm::dmat4 mModelMat;    // modeling matrix //rotaciones, escalas, etc
	glm::dvec4 mColor;
	Texture* mTexture = nullptr;

	// transfers modelViewMat to the GPU
	virtual void upload(glm::dmat4 const& mModelViewMat) const;
};


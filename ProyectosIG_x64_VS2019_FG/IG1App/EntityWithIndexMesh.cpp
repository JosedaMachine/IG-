#include "EntityWithIndexMesh.h"
#include <gtc/type_ptr.hpp>

#include <gtc/matrix_transform.hpp>  
#include "IG1App.h"

void EntityWithIndexMesh::upload(glm::dmat4 const& mModelViewMat) const
{
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(mModelViewMat));  // transfers modelView matrix to the GPU
}

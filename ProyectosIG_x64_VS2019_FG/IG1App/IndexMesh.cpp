#include "IndexMesh.h"

IndexMesh::IndexMesh(){
	mPrimitive = GL_TRIANGLES;
}

IndexMesh::~IndexMesh()
{
	delete[] vIndices;
}

void IndexMesh::render() const{
	glEnableClientState(GL_VERTEX_ARRAY);

	if (vIndices != nullptr) {
		glEnableClientState(GL_INDEX_ARRAY); 
		glIndexPointer(GL_UNSIGNED_INT, 0, vIndices);
	}
	
	glDisableClientState(GL_INDEX_ARRAY);
}

void IndexMesh::draw() const{
	glDrawElements(mPrimitive, nNumIndices, GL_UNSIGNED_INT, vIndices);
}

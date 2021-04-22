#include "IndexMesh.h"

void IndexMesh::render() const
{
	//Comandos OnpenGl para enviar datos de arrays a Gpu
	//Nuevos comandos para la tabla de índices
	

	if (vVertices.size() > 0) {  // transfer data
   // transfer the coordinates of the vertices
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_DOUBLE, 0, vVertices.data());  // number of coordinates per vertex, type of each coordinate, stride, pointer 
		if (vColors.size() > 0) { // transfer colors
			glEnableClientState(GL_COLOR_ARRAY);
			glColorPointer(4, GL_DOUBLE, 0, vColors.data());  // components number (rgba=4), type of each component, stride, pointer  
		}

		if (vTexCoords.size() > 0) { // transfer texture  data
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glTexCoordPointer(2, GL_DOUBLE, 0, vTexCoords.data());  // components number (rgba=4), type of each component, stride, pointer  
		}
		// Comandos OpenGL para enviar datos de arrays a GPU
		// Nuevos comandos para la tabla de índices
		if (vIndices != nullptr) {
			glEnableClientState(GL_INDEX_ARRAY);
			glIndexPointer(GL_UNSIGNED_INT, 0, vIndices);
		}

		draw();

		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);

		//Comandos OpenGL para deshabilitar datos enviados
		//Nuevo comando para la tabla de índices
		glDisableClientState(GL_INDEX_ARRAY);
	}

}

void IndexMesh::draw() const 
{
	glDrawElements(mPrimitive, nNumIndices, GL_UNSIGNED_INT, vIndices);

}

IndexMesh* IndexMesh::generaAnilloCuadradoIndexado(float outSide, float inSide)
{
	IndexMesh* m = new IndexMesh();

	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(0.0, 0.0, 0.0); glVertex3f(outSide, outSide, 0.0);
	glColor3f(1.0, 0.0, 0.0); glVertex3f(outSide, outSide, 0.0);
	glColor3f(0.0, 1.0, 0.0); glVertex3f(outSide, outSide, 0.0);
	glColor3f(0.0, 0.0, 1.0); glVertex3f(outSide, outSide, 0.0);
	glColor3f(1.0, 1.0, 0.0); glVertex3f(outSide, outSide, 0.0);
	glColor3f(1.0, 0.0, 1.0); glVertex3f(inSide, inSide, 0.0);
	glColor3f(0.0, 1.0, 1.0); glVertex3f(inSide, inSide, 0.0);
	glColor3f(1.0, 0.0, 0.0); glVertex3f(inSide, inSide, 0.0);
	glColor3f(0.0, 0.0, 0.0); glVertex3f(inSide, inSide, 0.0);
	glColor3f(1.0, 0.0, 0.0); glVertex3f(inSide, 10.0, 0.0);
	glEnd();

	return m;
}

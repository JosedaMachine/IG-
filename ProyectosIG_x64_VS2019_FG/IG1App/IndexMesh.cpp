#include "IndexMesh.h"

void IndexMesh::render() const
{
	//Comandos OnpenGl para enviar datos de arrays a Gpu
	//Nuevos comandos para la tabla de índices
	
	
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

		static float vertices[] = {
			30.0, 30.0, 0.0,
			10.0, 10.0, 0.0,
			70.0, 30.0, 0.0,
			90.0, 10.0, 0.0,
			70.0, 70.0, 0.0,
			90.0, 90.0, 0.0,
			30.0, 70.0, 0.0,
			10.0, 90.0, 0.0
		};

		static float colors[] = {
			0.0, 0.0, 0.0,
			1.0, 0.0, 0.0,
			0.0, 1.0, 0.0,
			0.0, 0.0, 1.0,
			1.0, 1.0, 0.0,
			1.0, 0.0, 1.0,
			0.0, 1.0, 1.0,
			1.0, 0.0, 0.0
		};

		// Activación de los vertex arrays
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);

		// Especificación del lugar y formato de los datos
		glVertexPointer(3, GL_FLOAT, 0, vertices);
		glColorPointer(4, GL_FLOAT, 0, colors);


		draw();

		// Desactivación de los vertex arrays
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);

		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);

		//Comandos OpenGL para deshabilitar datos enviados
		//Nuevo comando para la tabla de índices
		glDisableClientState(GL_INDEX_ARRAY);

}

void IndexMesh::draw() const 
{
	unsigned int stripIndices[] = { 0,1, 2, 3, 4, 5, 6, 7, 0, 1 };

	glDrawElements(GL_TRIANGLE_STRIP, 10, GL_UNSIGNED_INT, stripIndices);

}

IndexMesh* IndexMesh::generaAnilloCuadradoIndexado(float outSide, float inSide)
{
	IndexMesh* m = new IndexMesh();


	glBegin(GL_TRIANGLE_STRIP);
	// Cuando se usa glArrayElement(i);
	// vertices[i] y colors[i] se recuperan a la vez
	for (int i = 0; i < 10; ++i) glArrayElement(i % 8);
	
	glEnd();


	//glBegin(GL_TRIANGLE_STRIP); 

	//glColor3f(0.0, 0.0, 0.0); glVertex3f(30.0, 30.0, 0.0); 
	//glColor3f(1.0, 0.0, 0.0); glVertex3f(10.0, 10.0, 0.0); 
	//glColor3f(0.0, 1.0, 0.0); glVertex3f(70.0, 30.0, 0.0); 
	//glColor3f(0.0, 0.0, 1.0); glVertex3f(90.0, 10.0, 0.0); 
	//glColor3f(1.0, 1.0, 0.0); glVertex3f(70.0, 70.0, 0.0); 
	//glColor3f(1.0, 0.0, 1.0); glVertex3f(90.0, 90.0, 0.0); 
	//glColor3f(0.0, 1.0, 1.0); glVertex3f(30.0, 70.0, 0.0); 
	//glColor3f(1.0, 0.0, 0.0); glVertex3f(10.0, 90.0, 0.0); 
	//glColor3f(0.0, 0.0, 0.0); glVertex3f(30.0, 30.0, 0.0); 
	//glColor3f(1.0, 0.0, 0.0); glVertex3f(10.0, 10.0, 0.0); 

	//glEnd();

	return m;
}

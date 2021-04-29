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

	if (vNormals.size() > 0) {
		glEnableClientState(GL_NORMAL_ARRAY);
		glNormalPointer(GL_DOUBLE, 0, vNormals.data());
	}

	draw();

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	//Comandos OpenGL para deshabilitar datos enviados
	//Nuevo comando para la tabla de índices
	glDisableClientState(GL_INDEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

void IndexMesh::draw() const
{

	glDrawElements(mPrimitive, nNumIndices, GL_UNSIGNED_INT, vIndices);

}

IndexMesh* IndexMesh::generaAnilloCuadradoIndexado(float outSide, float inSide)
{
	IndexMesh* m = new IndexMesh();

	m->mPrimitive = GL_TRIANGLE_STRIP;

	m->mNumVertices = 8;

	m->vVertices.reserve(m->mNumVertices);

	m->vColors.reserve(m->mNumVertices);

	//Colores								//Vértices								
	m->vColors.emplace_back(0.0, 0.0, 0.0, 1.0); m->vVertices.emplace_back(30.0, 30.0, 0.0);
	m->vColors.emplace_back(1.0, 0.0, 0.0, 1.0); m->vVertices.emplace_back(10.0, 10.0, 0.0);
	m->vColors.emplace_back(0.0, 1.0, 0.0, 1.0); m->vVertices.emplace_back(70.0, 30.0, 0.0);
	m->vColors.emplace_back(0.0, 0.0, 1.0, 1.0); m->vVertices.emplace_back(90.0, 10.0, 0.0);
	m->vColors.emplace_back(1.0, 1.0, 0.0, 1.0); m->vVertices.emplace_back(70.0, 70.0, 0.0);
	m->vColors.emplace_back(1.0, 0.0, 1.0, 1.0); m->vVertices.emplace_back(90.0, 90.0, 0.0);
	m->vColors.emplace_back(0.0, 1.0, 1.0, 1.0); m->vVertices.emplace_back(30.0, 70.0, 0.0);
	m->vColors.emplace_back(1.0, 0.0, 0.0, 1.0); m->vVertices.emplace_back(10.0, 90.0, 0.0);
	m->vColors.emplace_back(0.0, 0.0, 0.0, 1.0); m->vVertices.emplace_back(30.0, 30.0, 0.0);
	m->vColors.emplace_back(1.0, 0.0, 0.0, 1.0); m->vVertices.emplace_back(10.0, 10.0, 0.0);

	//Indices
	m->nNumIndices = 10;

	m->vIndices = new GLuint[m->nNumIndices];

	for (int i = 0; i < m->nNumIndices; i++) {
		m->vIndices[i] = i % 8;
	}

	//Normales

	m->vNormals.reserve(m->mNumVertices);

	for (int i = 0; i < m->mNumVertices; i++) {
		m->vNormals.push_back(glm::dvec3(0, 0, 0));
	}

	//Los tres vértices del triángulo y n la normal
	glm::dvec3 a, b, c, n;

	a = m->vVertices[m->vIndices[0]];
	b = m->vVertices[m->vIndices[1]];
	c = m->vVertices[m->vIndices[2]];

	//Producto vectorial para sacar la perpendicular
	n = glm::cross((b - a), (c - a));

	//Porque todos los triángulos tienen la misma normal
	for (int i = 0; i < m->mNumVertices; i++) {
		m->vNormals[i] = glm::normalize(n);
	}

	return m;
}

IndexMesh* IndexMesh::generaCuboConTapadIndexado(GLdouble l)
{
	IndexMesh* m = new IndexMesh();

	m->mPrimitive = GL_TRIANGLES;

	m->mNumVertices = 8;

	m->vVertices.reserve(m->mNumVertices);

	m->vColors.reserve(m->mNumVertices);
	//Vertices
	m->vVertices.emplace_back(-l / 2, l / 2, l / 2);
	m->vVertices.emplace_back(-l / 2, -l / 2, l / 2);
	m->vVertices.emplace_back(l / 2, l / 2, l / 2);
	m->vVertices.emplace_back(l / 2, -l / 2, l / 2);
	m->vVertices.emplace_back(l / 2, l / 2, -l / 2);
	m->vVertices.emplace_back(l / 2, -l / 2, -l / 2);
	m->vVertices.emplace_back(-l / 2, l / 2, -l / 2);
	m->vVertices.emplace_back(-l / 2, -l / 2, -l / 2);

	//Indices
	m->nNumIndices = 36;

	m->vIndices = new GLuint[m->nNumIndices]{ 
		0,1,2,
		2,1,3,
		2,3,4,
		4,3,5,
		5,6,4,
		5,7,6,
		6,7,1,
		0,6,1,
		6,0,4,
		4,0,2,
		7,1,5,
		5,1,3
	};

	m->vNormals.reserve(m->mNumVertices);

	/*for (int i = 0; i < m->mNumVertices; i++) {
		m->vNormals.push_back(glm::dvec3(0, 0, 0));
	}*/
	   
	m->vNormals.emplace_back(glm::normalize(glm::dvec3(-1, 1, 1)));
	m->vNormals.emplace_back(glm::normalize(glm::dvec3(-1, -1, 1)));
	m->vNormals.emplace_back(glm::normalize(glm::dvec3(1, 1, 1)));
	m->vNormals.emplace_back(glm::normalize(glm::dvec3(1, -1, 1)));
	m->vNormals.emplace_back(glm::normalize(glm::dvec3(1, 1, -1)));
	m->vNormals.emplace_back(glm::normalize(glm::dvec3(1, -1, -1)));
	m->vNormals.emplace_back(glm::normalize(glm::dvec3(-1, 1, -1)));
	m->vNormals.emplace_back(glm::normalize(glm::dvec3(-1, -1, -1)));

	return m;
}

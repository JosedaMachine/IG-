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


	//m->vVertices.emplace_back(-l / 2, l / 2, l / 2);    //V0     
	//m->vVertices.emplace_back(-l / 2, -l / 2, l / 2);   //V1
	//m->vVertices.emplace_back(l / 2, l / 2, l / 2);     //v2     
	//m->vVertices.emplace_back(l / 2, -l / 2, l / 2);    //V3     
	//m->vVertices.emplace_back(l / 2, l / 2, -l / 2);    //V4
	//m->vVertices.emplace_back(l / 2, -l / 2, -l / 2);   //v5
	//m->vVertices.emplace_back(-l / 2, l / 2, -l / 2);   //V6
	//m->vVertices.emplace_back(-l / 2, -l / 2, -l / 2);  //v7

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
		 //0,1,2,
		 //2,1,3,
		 //2,3,4,
		 //4,3,5,
		 //4,5,6,
		 //6,5,7,
		 //6,7,0,
		 //0,7,1,
		 //0,2,6,
		 //6,2,4,
		 //1,3,7,
		 //7,3,5
	};

	m->vNormals.reserve(m->mNumVertices);
	//Inicializa
	for (int i = 0; i < m->mNumVertices; i++) {
		m->vNormals.push_back(glm::dvec3(0, 0, 0));
	}

	//SEGUNDO:
	//m->vNormals.emplace_back(glm::normalize(glm::dvec3(-1, 1, 1)));
	//m->vNormals.emplace_back(glm::normalize(glm::dvec3(-1, -1, 1)));
	//m->vNormals.emplace_back(glm::normalize(glm::dvec3(1, 1, 1)));
	//m->vNormals.emplace_back(glm::normalize(glm::dvec3(1, -1, 1)));
	//m->vNormals.emplace_back(glm::normalize(glm::dvec3(1, 1, -1)));
	//m->vNormals.emplace_back(glm::normalize(glm::dvec3(1, -1, -1)));
	//m->vNormals.emplace_back(glm::normalize(glm::dvec3(-1, 1, -1)));
	//m->vNormals.emplace_back(glm::normalize(glm::dvec3(-1, -1, -1)));


	//UNA PERSONA DESARROLLADA MÁS ALLÁ DEL HOMO ERECTUS

	m->buildNormalVectors();

	return m;
}

IndexMesh* IndexMesh::generateGrid(GLdouble lado, GLuint nDiv){

	IndexMesh* m = new IndexMesh();

	GLdouble incr = lado / nDiv;  // incremento para la coordenada x, y la c. z
	GLuint numFC= nDiv + 1;    // número de vértices por filas y columnas
	// Generación de vértices
	m->mNumVertices= numFC* numFC;     
	m->vVertices.reserve(m->mNumVertices);

	GLint x = -lado / 2;
	GLint z = -lado / 2;

	for (size_t i = 0; i < numFC; i++)
		for (size_t j = 0; j < numFC; j++)
			m->vVertices.emplace_back(glm::dvec3(x + j * incr, 0, z + i * incr));
			//m->vVertices[i * numFC + j] = glm::dvec3(x + j * incr, 0, z + i * incr);

	// Generación de índices
	m->nNumIndices = nDiv * nDiv * 6;
	m->vIndices = new GLuint[m->nNumIndices];

	int indiceMayor = 0;
	for (size_t i = 0; i < nDiv; i++){
		for (size_t j = 0; j < nDiv; j++){
			size_t iv = i * numFC + j;

			m->vIndices[indiceMayor++] = iv;
			m->vIndices[indiceMayor++] = iv + numFC;
			m->vIndices[indiceMayor++] = iv + 1;

			m->vIndices[indiceMayor++] = iv + 1;
			m->vIndices[indiceMayor++] = iv + numFC;
			m->vIndices[indiceMayor++] = iv + numFC + 1;
		}
	}

	m->buildNormalVectors();
	
	return m;
}

IndexMesh* IndexMesh::generaGridTex(GLdouble lado, GLuint numDiv){


	IndexMesh* m = generateGrid(lado, numDiv);

	GLuint numFC = numDiv + 1;

	m->vTexCoords.reserve(m->mNumVertices);

	int s = 0;
	int t = 1;

	float incremento =  1.0f / numDiv;
	for (int f = 0; f < numFC; f++) {
		for (int c = 0; c < numFC; c++) {
			m->vTexCoords.emplace_back(s + incremento * c, t - incremento * f);
		}
	}

	return m;
}

void IndexMesh::buildNormalVectors()
{
	vNormals.reserve(mNumVertices);
	for (int i = 0; i < mNumVertices; i++)
		vNormals.push_back(glm::dvec3(0, 0, 0));

	for (int i = 0; i < nNumIndices; i += 3) {
		glm::dvec3 a, b, c;

		GLuint first, second, third;

		first = vIndices[i];
		second = vIndices[i + 1];
		third = vIndices[i + 2];

		a = vVertices[first];
		b = vVertices[second];
		c = vVertices[third];

		glm::dvec3 n = cross((b - a), (c - a));

		vNormals[first] += n;
		vNormals[second] += n;
		vNormals[third] += n;
	}

	for (int i = 0; i < mNumVertices; i++)
		vNormals[i] = glm::normalize(vNormals[i]);
}

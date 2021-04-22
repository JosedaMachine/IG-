#include "Mesh.h"
#include "CheckML.h"
#include <fstream>

using namespace std;
using namespace glm;

//-------------------------------------------------------------------------

void Mesh::draw() const 
{
  glDrawArrays(mPrimitive, 0, size());   // primitive graphic, first index and number of elements to be rendered
}
//-------------------------------------------------------------------------

void Mesh::render() const 
{
  if (vVertices.size() > 0) {  // transfer data
	// transfer the coordinates of the vertices
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_DOUBLE, 0, vVertices.data());  // number of coordinates per vertex, type of each coordinate, stride, pointer 
	if (vColors.size() > 0) { // transfer colors
	  glEnableClientState(GL_COLOR_ARRAY);
	  glColorPointer(4, GL_DOUBLE, 0, vColors.data());  // components number (rgba=4), type of each component, stride, pointer  
	}
	
	if (vNormals.size() > 0) { // transfer colors
	  glEnableClientState(GL_NORMAL_ARRAY);
	  glNormalPointer(GL_DOUBLE, 0, vNormals.data());  // components number (rgba=4), type of each component, stride, pointer  
	}
	
	if(vTexCoords.size() > 0) { // transfer texture  data
	  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	  glTexCoordPointer(2, GL_DOUBLE, 0, vTexCoords.data());  // components number (rgba=4), type of each component, stride, pointer  
	}

	draw();

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
  }
}
//-------------------------------------------------------------------------

Mesh * Mesh::createRGBAxes(GLdouble l)
{
  Mesh* mesh = new Mesh();

  mesh->mPrimitive = GL_LINES;

  mesh->mNumVertices = 6;
  mesh->vVertices.reserve(mesh->mNumVertices);

  // X axis vertices
  mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
  mesh->vVertices.emplace_back(l, 0.0, 0.0);
  // Y axis vertices
  mesh->vVertices.emplace_back(0, 0.0, 0.0);
  mesh->vVertices.emplace_back(0.0, l, 0.0);
  // Z axis vertices
  mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
  mesh->vVertices.emplace_back(0.0, 0.0, l);

  mesh->vColors.reserve(mesh->mNumVertices);
  // X axis color: red  (Alpha = 1 : fully opaque)
  mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
  mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
  // Y axis color: green
  mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
  mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
  // Z axis color: blue
  mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
  mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
 
  return mesh;
}

Mesh* Mesh::createTrianguloRGB(GLdouble rd) {
	//Mesh* mesh = new Mesh();
	Mesh* mesh = generaPoligono(3,rd);

	mesh->mPrimitive = GL_TRIANGLES;

	mesh->mNumVertices = 3;
	mesh->vVertices.reserve(mesh->mNumVertices);//REservamos vértices

	mesh->vColors.reserve(mesh->mNumVertices);//Reservamos colores

	//Vértices
	mesh->vVertices.emplace_back(0.0, 50.0, 0.0);
	mesh->vVertices.emplace_back(-50.0, -25.0, 0.0);
	mesh->vVertices.emplace_back(50.0, -25.0, 0.0);

	//Coloritos
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);

	return mesh;
}

Mesh* Mesh::generaPoligono(GLuint numL, GLdouble rd) {
	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_LINE_LOOP;

	mesh->mNumVertices = numL;
	mesh->vVertices.reserve(mesh->mNumVertices);//REservamos vértices

	//mesh->vColors.reserve(mesh->mNumVertices);//Reservamos colores

	float ang = (360.0 / numL) + 90;
	vec2 c(0, 0);

	for (int i = 0; i < numL; i++) {
		mesh->vVertices.emplace_back(c.x + rd * cos(radians(ang)), c.y + rd * sin(radians(ang)), 0);
		ang = ang + 360.0 / numL;
	}


	return mesh;
}

Mesh* Mesh::generaPoligonoTextCord(GLuint numL, GLdouble rd)
{
	Mesh* mesh = generaPoligono(numL,rd);

	mesh->mPrimitive = GL_TRIANGLE_FAN;

	mesh->mNumVertices = numL;
	mesh->vTexCoords.reserve(mesh->mNumVertices);//REservamos vértices

	//mesh->vColors.reserve(mesh->mNumVertices);//Reservamos colores

	float ang = (360.0 / numL) + 90;
	vec2 c(0, 0);

	for (int i = 0; i < numL; i++) {
		mesh->vTexCoords.emplace_back(c.x + rd * cos(radians(ang)), c.y + rd * sin(radians(ang)));
		ang = ang + 360.0 / numL;
	}


	return mesh;
}

Mesh* Mesh::generaSierpinski(GLdouble rd, GLuint numP) {
	Mesh* triangulo = generaPoligono(3, rd);

	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_POINTS;

	mesh->mNumVertices = numP;
	mesh->vVertices.reserve(mesh->mNumVertices);

	dvec3 p = triangulo->vertices()[rand() % 3];
	dvec3 p1;

	dvec3 vertices[3] = { triangulo->vertices()[0], triangulo->vertices()[1], triangulo->vertices()[2] };

	// An arbitrary initial point inside the triangle
	mesh->vVertices.emplace_back(p);
	// compute and store N-1 new points
	for (int i = 1; i < numP; ++i) {
		int j = rand() % 3; // pick a vertex at random
		// Compute the point halfway between the selected vertex
		// and the previous point
		p1 = (p + vertices[j]) / 2.0;
		mesh->vVertices.emplace_back(p1);
		p = p1;
	}

	delete triangulo; triangulo = nullptr;
	return mesh;
}

Mesh* Mesh::generaRectangulo(GLdouble w, GLdouble h) {
	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_TRIANGLE_STRIP;

	mesh->mNumVertices = 4;
	mesh->vVertices.reserve(mesh->mNumVertices);//REservamos vértices

	//mesh->vColors.reserve(mesh->mNumVertices);//Reservamos colores

	mesh->vVertices.emplace_back(-w/2, h/2, 0.0);
	mesh->vVertices.emplace_back(-w/2, -h/2, 0.0);
	mesh->vVertices.emplace_back(w/2, h/2, 0.0);
	mesh->vVertices.emplace_back(w / 2, -h / 2, 0.0);

	return mesh;
}

Mesh* Mesh::generaRectanguloRGB(GLdouble w, GLdouble h) {
	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_TRIANGLE_STRIP;

	mesh->mNumVertices = 4;
	mesh->vVertices.reserve(mesh->mNumVertices);//REservamos vértices

	mesh->vColors.reserve(mesh->mNumVertices);//Reservamos colores

	//mesh->vColors.reserve(mesh->mNumVertices);//Reservamos colores

	mesh->vVertices.emplace_back(-w / 2, h / 2, 0.0);
	mesh->vVertices.emplace_back(-w / 2, -h / 2, 0.0);
	mesh->vVertices.emplace_back(w / 2, h / 2, 0.0);
	mesh->vVertices.emplace_back(w / 2, -h / 2, 0.0);


	//Coloritos
	mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
	mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	return mesh;
}

Mesh* Mesh::generaEstrella3D(GLdouble re, GLuint np, GLdouble h)
{
	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_TRIANGLE_FAN;

	mesh->mNumVertices = 2 * np + 2;
	mesh->vVertices.reserve(mesh->mNumVertices);//REservamos vértices

	//mesh->vColors.reserve(mesh->mNumVertices);//Reservamos colores

	float ang = 90;
	vec2 c(0, 0);

	mesh->vVertices.emplace_back(c.x , c.y, 0);
	for (int i = 0; i < mesh->mNumVertices - 1 ; i++) {
		float newAng = radians(ang);
		if (i % 2 == 0) {
			mesh->vVertices.emplace_back(c.x + re * cos(newAng), c.y + re * sin(newAng), h + ((re*2.0f)/3.0f));}
		else mesh->vVertices.emplace_back(c.x + (re/2.0f) * cos(newAng), c.y + (re/ 2.0f) * sin(newAng), h + ((re * 2.0f) / 3.0f));
		ang = ang + 360.0 / (2.0f * np);
	}

	return mesh;
}
Mesh* Mesh::generaContCubo(GLdouble ld)
{
	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_TRIANGLE_STRIP;

	mesh->mNumVertices = 10;
	mesh->vVertices.reserve(mesh->mNumVertices);//REservamos vértices


	mesh->vVertices.emplace_back(-ld/2,ld/2,ld/2); //v0
	mesh->vVertices.emplace_back(-ld/2,-ld/2,ld/2); //v1
	mesh->vVertices.emplace_back(ld/2,ld/2,ld/2); //v2
	mesh->vVertices.emplace_back(ld/2,-ld/2,ld/2); //v3
	mesh->vVertices.emplace_back(ld/2,ld/2,-ld/2); //v4
	mesh->vVertices.emplace_back(ld/2,-ld/2,-ld/2); //v5
	mesh->vVertices.emplace_back(-ld/2,ld/2,-ld/2); //v6
	mesh->vVertices.emplace_back(-ld/2,-ld/2,-ld/2); //v7
	mesh->vVertices.emplace_back(-ld/2,ld/2,ld/2); //v8
	mesh->vVertices.emplace_back(-ld/2,-ld/2,ld/2); //v9

	return mesh;
}
Mesh* Mesh::generaRectanguloTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh)
{
	Mesh* m = Mesh::generaRectangulo(w, h);

	m->vTexCoords.reserve(m->mNumVertices); 
	m->vTexCoords.emplace_back(0, 1.0*rh);  
	m->vTexCoords.emplace_back(0, 0); 
	m->vTexCoords.emplace_back(1.0*rw, 1.0*rh);
	m->vTexCoords.emplace_back(1.0*rw, 0);
	return m;
}
Mesh* Mesh::generaEstrellaTexCor(GLdouble re, GLuint np, GLdouble h)
{
	Mesh* m = Mesh::generaEstrella3D(re, np, h);

	m->vTexCoords.reserve(m->mNumVertices);

	float ang = 90;
	vec2 c(0, 0);
	m->vTexCoords.emplace_back(0.5f, 0.5f);

	for (int i = 0; i < m->mNumVertices - 1; i++) {
		float newAng = radians(ang);
		float x, y;

		if (i % 2 == 0) {
			
			x = cos(newAng);
			y = sin(newAng);
			//Paso las coordenadas (x,y) de sus cuadrantes, a las coordenadas (u,v).
			y =+ y*0.5f + 0.5f;
			x =+ x*0.5f + 0.5f;
			m->vTexCoords.emplace_back(x, y);
		}
		else{
			x = cos(newAng) / 2;
			y = sin(newAng) / 2;
			y = +y * 0.5f + 0.5f;
			x = +x * 0.5f + 0.5f;
			m->vTexCoords.emplace_back(x, y);
		}
		ang = ang + 360.0 / (2.0f * np);
	}

	return m;
}

Mesh* Mesh::generaContCuboTexCor(GLdouble nl){
	Mesh* m = Mesh::generaContCubo(nl);
	m->vTexCoords.reserve(m->mNumVertices);

	float x = 0;
	for (int i = 0; i < m->mNumVertices; i++) {
		if (i % 2 == 0) {
			m->vTexCoords.emplace_back(x, 1);
		}
		else {
			m->vTexCoords.emplace_back(x, 0);
			x = x + 1;
		}
	}
	//m->vTexCoords.emplace_back(0, 1); //v0
	//m->vTexCoords.emplace_back(0, 0); //v1
	//m->vTexCoords.emplace_back(0.2, 1); //v2
	//m->vTexCoords.emplace_back(0.2, 0); //v3
	//m->vTexCoords.emplace_back(0.4, 1); //v4
	//m->vTexCoords.emplace_back(0.4, 0); //v5
	//m->vTexCoords.emplace_back(0.6, 1); //v6
	//m->vTexCoords.emplace_back(0.6, 0); //v7
	//m->vTexCoords.emplace_back(0.8, 1); //v8
	//m->vTexCoords.emplace_back(0.8, 0); //v9

	return m;
}
Mesh* Mesh::generaCristalera(GLdouble w, GLdouble h)
{
	Mesh* m = Mesh::generaCuboContTextIrregular(w,h);
	m->vTexCoords.reserve(m->mNumVertices);

	float x = 0;
	for (int i = 0; i < m->mNumVertices; i++) {
		if (i % 2 == 0) {
			m->vTexCoords.emplace_back(x, 1);
		}
		else {
			m->vTexCoords.emplace_back(x, 0);
			x = x + 1;
		}
	}

	return m;
}
Mesh* Mesh::generaCuboContTextIrregular(GLdouble w, GLdouble h)
{
	Mesh* mesh = new Mesh();

	mesh->mPrimitive = GL_TRIANGLE_STRIP;

	mesh->mNumVertices = 10;
	mesh->vVertices.reserve(mesh->mNumVertices);//REservamos vértices

	mesh->vVertices.emplace_back(-w / 2, h / 2, w / 2); //v0
	mesh->vVertices.emplace_back(-w / 2, -h / 2, w / 2); //v1
	mesh->vVertices.emplace_back(w / 2, h / 2, w / 2); //v2
	mesh->vVertices.emplace_back(w / 2, -h / 2, w / 2); //v3
	mesh->vVertices.emplace_back(w / 2, h / 2, -w / 2); //v4
	mesh->vVertices.emplace_back(w / 2, -h / 2, -w / 2); //v5
	mesh->vVertices.emplace_back(-w / 2, h / 2, -w / 2); //v6
	mesh->vVertices.emplace_back(-w / 2, -h / 2, -w / 2); //v7
	mesh->vVertices.emplace_back(-w / 2, h / 2, w / 2); //v8
	mesh->vVertices.emplace_back(-w / 2, -h / 2, w / 2); //v9

	return mesh;
}

Mesh* Mesh::generaPolygon3D(GLdouble re, GLuint np)
{
	Mesh* mesh = new Mesh();
	mesh->mPrimitive = GL_TRIANGLE_FAN;
	//Vertices
	mesh->mNumVertices = np + 2;
	//angulo inicial
	GLdouble ang = 0;

	mesh->vVertices.reserve(mesh->mNumVertices);
	mesh->vColors.reserve(mesh->mNumVertices);
	//Primer Vertice
	mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
	mesh->vColors.emplace_back(1.0, 1.0, 1.0, 1.0);
	//El resto
	for (int i = 0; i < mesh->mNumVertices - 1; i++) {
		GLdouble x = 0 + re * cos(radians(ang));
		GLdouble y = 0 + re * sin(radians(ang));
		ang -= 360.0 / np;

		mesh->vVertices.emplace_back(x, y, 0.0);

		mesh->vColors.emplace_back(1.0, 1.0, 1.0, 1.0);
	}
	return mesh;
}

Mesh* Mesh::generaPolygonTexCor(GLdouble re, GLuint np)
{
	Mesh* mesh = generaPolygon3D(re, np);

	mesh->vTexCoords.reserve(mesh->mNumVertices);

	float ang = 0;

	dvec2 center = dvec2(0.5, 0.5);


	float radio = 0.5f;
	mesh->vTexCoords.emplace_back(center);    //Origen de poligono

	for (int i = 0; i < mesh->mNumVertices - 1; i++) { //-1 pq el vertice inicial se declara antes
		float x = cos(radians(ang)) * radio + center.x;
		float y = sin(radians(ang)) * radio + center.y;
		ang -= 360.0 / np;

		mesh->vTexCoords.emplace_back(x, y);
	}

	return mesh;
}
//-------------------------------------------------------------------------


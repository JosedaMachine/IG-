#include "MbR.h"

MbR* MbR::generaIndexMeshByRevolution(int mm, int nn, glm::dvec3* perfil){	
	MbR* mesh = new MbR(mm, nn, perfil);
	mesh->mPrimitive = GL_TRIANGLES; 
	mesh->mNumVertices = nn * mm;
	//Vector auxiliar
	glm::dvec3* vertices = new glm::dvec3[mesh->mNumVertices];
	for (int i = 0; i < nn; i++) {
		// Generar la muestra i-ésima de vértices
		GLdouble theta = i * 360 / nn;
		GLdouble c = cos(glm::radians(theta));
		GLdouble s = sin(glm::radians(theta));
		// R_y(theta) es la matriz de rotación alrededor del eje Y
		for (int j = 0; j < mm; j++) {
			int indice = i * mm + j;
			GLdouble x = c * perfil[j].x + s * perfil[j].z;
			GLdouble z = -s * perfil[j].x + c * perfil[j].z + perfil[j].z;
			vertices[indice] = glm::dvec3(x, perfil[j].y, z);
		}
	}

	for (size_t i = 0; i < mesh->mNumVertices; i++)
		mesh->vVertices.emplace_back(vertices[i]);

	// Es 6*m*n - 6*n
	//  Al ser 6 vertices por cara, y dar m*n vueltas, esas son las caras que se construyen.
	// Como arriba y abajo no son 6 sino 3, pues hay que restarle esos vertices al total. 
	// Como se realiza n vueltas, y arriba y abajo son 6 en total, es -6*n
	mesh->nNumIndices = 6 * nn * (mm - 1);
	mesh->vIndices = new GLuint[mesh->nNumIndices];
	int indiceMayor = 0;	
	//El contador i recorre las muestras alrededor del eje Y
	for (int i = 0; i < nn; i++){
	    // El contador j recorre los v�rtices del perfil, 
	    // de abajo arriba. Las caras cuadrangulares resultan
	    // al unir la muestra i-�sima con la (i+1)%nn-�sima
	    for (int j = 0; j < mm - 1; j++){
	        // El contador indice sirve para llevar cuenta 
	        // de los �ndices generados hasta ahora. Se recorre
	        // la cara desde la esquina inferior izquierda 
	        int indice = i * mm + j;
	        //Primer triangulo de la cara
	        mesh->vIndices[indiceMayor++] = indice;
	        mesh->vIndices[indiceMayor++] = (indice + mm) % (nn * mm);
	        mesh->vIndices[indiceMayor++] = (indice + mm + 1) % (nn * mm);
	        //Segundo subnormal triangulo de la cara
	        mesh->vIndices[indiceMayor++] = (indice + mm + 1) % (nn * mm);
	        mesh->vIndices[indiceMayor++] = (indice + 1);
	        mesh->vIndices[indiceMayor++] = indice;
	    }
	}

	mesh->buildNormalVectors();
	return mesh;
}

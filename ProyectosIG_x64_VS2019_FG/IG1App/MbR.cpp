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
            GLdouble z = -s * perfil[j].x + c * perfil[j].z;
            vertices[indice] = glm::dvec3(x, perfil[j].y, z);
        }
    }

    //Metemos los vertices auxiliares en el vector de vertices
    for (size_t i = 0; i < mesh->mNumVertices; i++)
        mesh->vVertices.emplace_back(vertices[i]);

    mesh->nNumIndices = (((mm - 2 - 1) * nn * 2) * 6 + nn * 2 * 3)*2;

    mesh->vIndices = new GLuint[mesh->nNumIndices];
    // El contador i recorre las muestras alrededor del eje Y
    int indiceMayor = 0;
    for (int i = 0; i < nn; i++){
        // El contador j recorre los vértices del perfil, 
        // de abajo arriba. Las caras cuadrangulares resultan
        // al unir la muestra i-ésima con la (i+1)%nn-ésima
        for (int j = 0; j < mm - 1; j++){
            // El contador indice sirve para llevar cuenta 
            // de los índices generados hasta ahora. Se recorre
            // la cara desde la esquina inferior izquierda 
            int indice = i * mm + j;
            //Primer triangulo de la cara
            mesh->vIndices[indiceMayor++] = indice;
            mesh->vIndices[indiceMayor++] = (indice + mm) % (nn * mm);
            mesh->vIndices[indiceMayor++] = (indice + mm + 1) % (nn * mm);
            //Segundo triangulo de la cara
            mesh->vIndices[indiceMayor++] = (indice + mm + 1) % (nn * mm);
            mesh->vIndices[indiceMayor++] = (indice + 1);
            mesh->vIndices[indiceMayor++] = indice;
        }
    }

    mesh->vNormals.reserve(mesh->mNumVertices);
    //Inicializa
    for (int i = 0; i < mesh->mNumVertices; i++) {
        mesh->vNormals.push_back(glm::dvec3(0, 0, 0));
    }

    mesh->buildNormalVectors();
    //Angel es un poco imbecil
    return mesh;
}

GLuint MbR::getIndexNumberRevolution(int m, int n){
    return ((m - 2 - 1) * n * 2) * 6 + n * 2 * 3;
}

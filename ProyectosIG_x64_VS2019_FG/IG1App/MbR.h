#pragma once
#include "IndexMesh.h"
class MbR : public IndexMesh{
    
public:
    MbR() :samplesNumbers(), perfilPoints(), perfil() {};

    MbR(int m , int n, glm::dvec3* vertices)    {
        samplesNumbers = n;
        perfilPoints = m;
        perfil = vertices;
    }

    ~MbR() {

    };

    static MbR* generaIndexMeshByRevolution(int mm, int nn, glm::dvec3* perfil);

    GLuint getIndexNumberRevolution(int m , int n);

private:
    int samplesNumbers;
    int perfilPoints;
    glm::dvec3* perfil;
};


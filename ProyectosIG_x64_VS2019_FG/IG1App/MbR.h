#pragma once
#include "IndexMesh.h"
class MbR :
    public IndexMesh{
    
    MbR() :samplesNumbers(), perfilPoints(), perfil() {};

    MbR(int n, int m , glm::dvec3* vertices)    {
        samplesNumbers = n;
        perfilPoints = m;
        perfil = vertices;
    }

    ~MbR() {

    };

private:
    int samplesNumbers;
    int perfilPoints;
    glm::dvec3* perfil;
};


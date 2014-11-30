#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>
#include <string.h>


class point{
public:
    float x;
    float y;
    float z;
};


extern "C" void loadOBJ(char* path, int *numVertices, GLfloat **arrayVertices, GLfloat **arrayNormais)
{

    std::vector<point> vertices, normalVector, faces, facesNormals;
 
    FILE * file = fopen(path, "r");
    if (file == NULL){
        printf("Failed to open file!\n");
        return;
    }
 
    char firstChar[128];
    int res = fscanf(file, "%s", firstChar);
 
    point tmp, tmpN;
    while (res != EOF) {
        if (strcmp(firstChar, "v") == 0) {
            fscanf(file, "%f %f %f\n", &tmp.x, &tmp.y, &tmp.z);
            vertices.push_back(tmp);
        }
        else if (strcmp(firstChar, "vn") == 0) {
            fscanf(file, "%f %f %f\n", &tmp.x, &tmp.y, &tmp.z);
            normalVector.push_back(tmp);
        }
        else if (strcmp(firstChar, "f") == 0) {
            unsigned int vertexIndex[3], normalIndex[3];
            fscanf(file, "%d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0],
                        &vertexIndex[1], &normalIndex[1],
                        &vertexIndex[2], &normalIndex[2]);
            faces.push_back(vertices.at(vertexIndex[0] - 1));
            faces.push_back(vertices.at(vertexIndex[1] - 1));
            faces.push_back(vertices.at(vertexIndex[2] - 1));
 
            facesNormals.push_back(normalVector.at(normalIndex[0] - 1));
            facesNormals.push_back(normalVector.at(normalIndex[1] - 1));
            facesNormals.push_back(normalVector.at(normalIndex[2] - 1));
        }
        else {
 
        }
        res = fscanf(file, "%s", firstChar);
    }
 
    *numVertices = faces.size();
    *arrayVertices = (GLfloat *)malloc(3 * faces.size() * sizeof(GLfloat));
    *arrayNormais = (GLfloat *)malloc(3 * faces.size() * sizeof(GLfloat));
    GLfloat* coordenadas = *arrayVertices;
    GLfloat* normais = *arrayNormais;
    int sub = 0;
    for (std::vector<int>::size_type i = 0; i < faces.size(); i++) {
        tmp = faces.at(i);
        tmpN = facesNormals.at(i);
        normais[sub] = tmpN.x;
        coordenadas[sub++] = tmp.x;
        normais[sub] = tmpN.y;
        coordenadas[sub++] = tmp.y;
        normais[sub] = tmpN.z;
        coordenadas[sub++] = tmp.z;
    }
}


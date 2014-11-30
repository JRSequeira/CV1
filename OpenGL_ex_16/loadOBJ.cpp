#include <stdio.h>
#include <stdlib.h>
#include "loadOBJ.hpp"
#include <GL/glew.h>
#include <GL/freeglut.h>

extern void loadOBJ(const char* path,
             int * numvertices,
             std::vector < GLfloat > vertices,
             std::vector < GLfloat > normais){

    std::vector< unsigned int > vertexIndices, normalIndices;
    std::vector< GLfloat* > temp_vertices;
    std::vector< GLfloat* > temp_uvs;
    std::vector< GLfloat* > temp_normals;

    FILE * file = fopen(path, "r");
    if(file == NULL){
        printf("Couldn't open file\n");
        return;
    }

    while(1){
        char lineHeader[128];
        int res = fscanf(file, "%s", lineHeader);
        if(res == EOF){
            break;
        }
        if (strcmp(lineHeader, "v") == 0){
            GLfloat v1, v2, v3;
            fscanf(file, "%f %f %f\n", v1, v2, v3 );
            temp_vertices.push_back(v1);
            temp_vertices.push_back(v2);
            temp_vertices.push_back(v3);
            
        }
        else if ( strcmp( lineHeader, "vn" ) == 0 ){
            GLfloat n1, n2, n3;
            fscanf(file, "%f %f %f\n", n1, n2, n3 );
            temp_normals.push_back(n1);
            temp_normals.push_back(n2);
            temp_normals.push_back(n3);
            
        }
        else if ( strcmp( lineHeader, "f" ) == 0 ){
            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], normalIndex[3];
            int matches = fscanf(file, "%d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2] );
            if (matches != 9){
                printf("File can't be read by our simple parser : ( Try exporting with other options\n");
                return false;
            }
            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);
            normalIndices.push_back(normalIndex[0]);
            normalIndices.push_back(normalIndex[1]);
            normalIndices.push_back(normalIndex[2]);
    }
    for( unsigned int i=0; i<vertexIndices.size(); i++ ){
        unsigned int vertexIndex = vertexIndices[i];
        GLfloat v1 = temp_vertices[(vertexIndex-1)*3];
        GLfloat v2 = temp_vertices[(vertexIndex-1)*3+1];
        GLfloat v3 = temp_vertices[(vertexIndex-1)*
        vertices.push_back(v1);
        vertices.push_back(v1);
        vertices.push_back(v1);
    }
    for( unsigned int i=0; i<normalIndices.size(); i++ ){
        unsigned int normalIndices = normalIndices[i];
        GLfloat v1 = temp_normals[(normalIndices-1)*3];
        GLfloat v2 = temp_normals[(normalIndices-1)*3+1];
        GLfloat v3 = temp_normals[(normalIndices-1)*
        vertices.push_back(v1);
        vertices.push_back(v1);
        vertices.push_back(v1);
    }

}
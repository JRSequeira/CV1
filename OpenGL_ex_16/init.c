/*
 * init.c
 *
 * Ficheiro de implementacao do modulo INIT.
 *
 * J. Madeira - Out/2012
 */


#include <stdlib.h>

#include <stdio.h>

#include <string.h>



#define GLEW_STATIC /* Necessario se houver problemas com a lib */

#include <GL/glew.h>

#include <GL/freeglut.h>

#include "globals.h"

#include "loadOBJ.hpp"

#include "mathUtils.h"

#include "models.h"

#include "angteRotation.h"



void inicializarEstado( void )
{

    /* DOUBLE-BUFFERING + DEPTH-TESTING */

    glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );

    /* Definir a cor do fundo */

    glClearColor( 0.0, 0.0, 0.0, 1.0 );

    /* Atributos das primitivas */

    glPointSize( 4.0 );

    glLineWidth( 3.0 );

    /* Modo de desenho dos poligonos */

    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

    /* Back-Face Culling */

    glCullFace( GL_BACK );

    glEnable( GL_CULL_FACE );


    /* Matriz de projeccao é inicialmente a IDENTIDADE => Proj. Paralela Ortogonal */

    matrizProj = IDENTITY_MATRIX;

    matrizModelView = IDENTITY_MATRIX;

    /* Para rodar globalmente a cena */

    animacaoModelosON = 1;

    animacaoFocosON = 0;
}


void inicializarJanela( void )
{
    /* Caracteristicas da janela de saida */

    glutInitWindowSize( 600, 600 ); /* Usar variaveis GLOBAIS para estes parametros */

    glutInitWindowPosition( 100, 100 );

    /* Para terminar de modo apropriado */

    glutSetOption(

        GLUT_ACTION_ON_WINDOW_CLOSE,

        GLUT_ACTION_GLUTMAINLOOP_RETURNS

    );

    /* Criar a janela de saida */

    windowHandle = glutCreateWindow( "OpenGL_ex_16" );

    if ( windowHandle < 1 )
    {
        fprintf(

            stderr,

            "ERROR: Could not create a new rendering window.\n"

        );

        exit( EXIT_FAILURE );
    }
}

void inicializarFontesDeLuz( void )
{
    numFocos = 1;

    /* Criar o array */

    arrayFocos = (pontFoco *) malloc( numFocos * sizeof(pontFoco) );

    /* Foco 0 */

    arrayFocos[0] = (pontFoco) malloc( sizeof(Registo_Foco) );

    arrayFocos[0]->focoIsOn = 1;

    arrayFocos[0]->posicao[0] = 0.0;

    arrayFocos[0]->posicao[1] = 0.0;

    arrayFocos[0]->posicao[2] = 5.0;

    arrayFocos[0]->posicao[3] = 1.0; /* Foco PONTUAL */

    arrayFocos[0]->intensidade[0] = 0;

    arrayFocos[0]->intensidade[1] = 1.0;

    arrayFocos[0]->intensidade[2] = 0.0;

    arrayFocos[0]->intensidade[3] = 1.0;

    arrayFocos[0]->luzAmbiente[0] = 0.2;

    arrayFocos[0]->luzAmbiente[1] = 0.2;

    arrayFocos[0]->luzAmbiente[2] = 0.2;

    arrayFocos[0]->luzAmbiente[3] = 1.0;

    arrayFocos[0]->translX = 0.0;

    arrayFocos[0]->translY = 0.0;

    arrayFocos[0]->translZ = 0.0;

    arrayFocos[0]->angRotXX = 0.0;

    arrayFocos[0]->angRotYY = 0.0;

    arrayFocos[0]->angRotZZ = 0.0;

    arrayFocos[0]->rotacaoOnXX = 1;

    arrayFocos[0]->rotacaoOnYY = 0;

    arrayFocos[0]->rotacaoOnZZ = 0;
}

void inicializarModelos( void )
{
    numModelos = 12;

    /* Criar o array */

    arrayModelos = (pontModelo *) malloc( numModelos * sizeof(pontModelo) );

    // RELOGIO 0
    arrayModelos[0] = (pontModelo) malloc( sizeof(Registo_Modelo) );
    loadOBJ("simpleobj.obj", &(arrayModelos[0]->numVertices),
                   &(arrayModelos[0]->arrayVertices),
                   &(arrayModelos[0]->arrayNormais));

    /* Array vazio para guardar a cor calculada para cada vertice */

    arrayModelos[0]->arrayCores = (GLfloat *) calloc( 3 * arrayModelos[0]->numVertices, sizeof( GLfloat) );

    /* Propriedades do material */

    arrayModelos[0]->kAmb[0] = 0.2;

    arrayModelos[0]->kAmb[1] = 0.2;

    arrayModelos[0]->kAmb[2] = 0.2;

    arrayModelos[0]->kAmb[3] = 1.0;

    arrayModelos[0]->kDif[0] = 0.7;

    arrayModelos[0]->kDif[1] = 0.7;

    arrayModelos[0]->kDif[2] = 0.7;

    arrayModelos[0]->kDif[3] = 1.0;

    arrayModelos[0]->kEsp[0] = 0.7;

    arrayModelos[0]->kEsp[1] = 0.7;

    arrayModelos[0]->kEsp[2] = 0.7;

    arrayModelos[0]->kEsp[3] = 1.0;

    arrayModelos[0]->coefDePhong = 100;

    /* Parametros das transformacoes */

    arrayModelos[0]->deslX = -0.65;

    arrayModelos[0]->deslY = 0;

    arrayModelos[0]->deslZ = 0;

    arrayModelos[0]->angRotXX = 90;

    arrayModelos[0]->angRotYY = 0;

    arrayModelos[0]->angRotZZ = 0;

    arrayModelos[0]->factorEscX = 0.3;

    arrayModelos[0]->factorEscY = 0.3;

    arrayModelos[0]->factorEscZ = 0.3;

    arrayModelos[0]->rotacaoOnXX = 0;

    arrayModelos[0]->rotacaoOnYY = 1;

    arrayModelos[0]->rotacaoOnZZ = 0;

    // RELOGIO 1

    arrayModelos[1] = (pontModelo) malloc( sizeof(Registo_Modelo) );
    lerFicheiroOBJ("prismaHexagonal.OBJ", &(arrayModelos[1]->numVertices),
                   &(arrayModelos[1]->arrayVertices),
                   &(arrayModelos[1]->arrayNormais));

    /* Array vazio para guardar a cor calculada para cada vertice */

    arrayModelos[1]->arrayCores = (GLfloat *) calloc( 3 * arrayModelos[1]->numVertices, sizeof( GLfloat) );

    /* Propriedades do material */

    arrayModelos[1]->kAmb[0] = 0.2;

    arrayModelos[1]->kAmb[1] = 0.2;

    arrayModelos[1]->kAmb[2] = 0.2;

    arrayModelos[1]->kAmb[3] = 1.0;

    arrayModelos[1]->kDif[0] = 0.7;

    arrayModelos[1]->kDif[1] = 0.7;

    arrayModelos[1]->kDif[2] = 0.7;

    arrayModelos[1]->kDif[3] = 1.0;

    arrayModelos[1]->kEsp[0] = 0.7;

    arrayModelos[1]->kEsp[1] = 0.7;

    arrayModelos[1]->kEsp[2] = 0.7;

    arrayModelos[1]->kEsp[3] = 1.0;

    arrayModelos[1]->coefDePhong = 100;

    /* Parametros das transformacoes */

    arrayModelos[1]->deslX = 0;

    arrayModelos[1]->deslY = 0;

    arrayModelos[1]->deslZ = 0;

    arrayModelos[1]->angRotXX = 90;

    arrayModelos[1]->angRotYY = 0;

    arrayModelos[1]->angRotZZ = 0;

    arrayModelos[1]->factorEscX = 0.3;

    arrayModelos[1]->factorEscY = 0.3;

    arrayModelos[1]->factorEscZ = 0.3;

    arrayModelos[1]->rotacaoOnXX = 0;

    arrayModelos[1]->rotacaoOnYY = 1;

    arrayModelos[1]->rotacaoOnZZ = 0;

    
    // RELOGIO 2
    arrayModelos[2] = (pontModelo) malloc( sizeof(Registo_Modelo) );
    lerFicheiroOBJ("prismaHexagonal.OBJ", &(arrayModelos[2]->numVertices),
                   &(arrayModelos[2]->arrayVertices),
                   &(arrayModelos[2]->arrayNormais));

    /* Array vazio para guardar a cor calculada para cada vertice */

    arrayModelos[2]->arrayCores = (GLfloat *) calloc( 3 * arrayModelos[2]->numVertices, sizeof( GLfloat) );

    /* Propriedades do material */

    arrayModelos[2]->kAmb[0] = 0.2;

    arrayModelos[2]->kAmb[1] = 0.2;

    arrayModelos[2]->kAmb[2] = 0.2;

    arrayModelos[2]->kAmb[3] = 1.0;

    arrayModelos[2]->kDif[0] = 0.7;

    arrayModelos[2]->kDif[1] = 0.7;

    arrayModelos[2]->kDif[2] = 0.7;

    arrayModelos[2]->kDif[3] = 1.0;

    arrayModelos[2]->kEsp[0] = 0.7;

    arrayModelos[2]->kEsp[1] = 0.7;

    arrayModelos[2]->kEsp[2] = 0.7;

    arrayModelos[2]->kEsp[3] = 1.0;

    arrayModelos[2]->coefDePhong = 100;

    /* Parametros das transformacoes */

    arrayModelos[2]->deslX = 0.65;

    arrayModelos[2]->deslY = 0;

    arrayModelos[2]->deslZ = 0;

    arrayModelos[2]->angRotXX = 90;

    arrayModelos[2]->angRotYY = 0;

    arrayModelos[2]->angRotZZ = 0;

    arrayModelos[2]->factorEscX = 0.3;

    arrayModelos[2]->factorEscY = 0.3;

    arrayModelos[2]->factorEscZ = 0.3;

    arrayModelos[2]->rotacaoOnXX = 0;

    arrayModelos[2]->rotacaoOnYY = 1;

    arrayModelos[2]->rotacaoOnZZ = 0;


    int i = 0;
    // Ponteiro 0 --> Horas
    for (i = 0; i < 3; i++)
    {
        arrayModelos[3+i] = (pontModelo) malloc( sizeof(Registo_Modelo) );

        loadOBJ( "pointerV1.obj", &(arrayModelos[3+i]->numVertices),
                                                     &(arrayModelos[3+i]->arrayVertices),
                                                     &(arrayModelos[3+i]->arrayNormais) );


        /* Array vazio para guardar a cor calculada para cada vertice */

        arrayModelos[3+i]->arrayCores = (GLfloat*) calloc( 3 * arrayModelos[3+i]->numVertices, sizeof( GLfloat) );

        /* Propriedades do material */

        arrayModelos[3+i]->kAmb[0] = 1;

        arrayModelos[3+i]->kAmb[1] = 1;

        arrayModelos[3+i]->kAmb[2] = 1;

        arrayModelos[3+i]->kAmb[3] = 1.0;

        arrayModelos[3+i]->kDif[0] = 0;

        arrayModelos[3+i]->kDif[1] = 0;

        arrayModelos[3+i]->kDif[2] = 0.7;

        arrayModelos[3+i]->kDif[3] = 1.0;

        arrayModelos[3+i]->kEsp[0] = 0.7;

        arrayModelos[3+i]->kEsp[1] = 0.7;

        arrayModelos[3+i]->kEsp[2] = 0.7;

        arrayModelos[3+i]->kEsp[3] = 1.0;

        arrayModelos[3+i]->coefDePhong = 100;

        /* Parametros das transformacoes */

        arrayModelos[3+i]->deslY = 0.0;

        arrayModelos[3+i]->deslZ = 0.0;

        arrayModelos[3+i]->angRotXX = 0;

        arrayModelos[3+i]->angRotYY = 0;

        arrayModelos[3+i]->angRotZZ = 0;

        arrayModelos[3+i]->factorEscX = 0.3;

        arrayModelos[3+i]->factorEscY = 0.3;

        arrayModelos[3+i]->factorEscZ = 0.3;

        arrayModelos[3+i]->rotacaoOnXX = 0;

        arrayModelos[3+i]->rotacaoOnYY = 1;

        arrayModelos[3+i]->rotacaoOnZZ = 0;
    }
 
    arrayModelos[3]->deslX = -0.65;
    arrayModelos[4]->deslX = 0.00;
    arrayModelos[5]->deslX = 0.65;
    
    // Ponteiro 1 --> Minutos
    for (i = 0; i < 3; i++)
    {
        arrayModelos[6+i] = (pontModelo) malloc( sizeof(Registo_Modelo) );

        loadOBJ( "pointerV2.obj", &(arrayModelos[6+i]->numVertices),
                                                     &(arrayModelos[6+i]->arrayVertices),
                                                      &(arrayModelos[6+i]->arrayNormais)  );

        /* Array vazio para guardar a cor calculada para cada vertice */

        arrayModelos[6+i]->arrayCores = (GLfloat*) calloc( 3 * arrayModelos[6+i]->numVertices, sizeof( GLfloat) );

        /* Propriedades do material */

        arrayModelos[6+i]->kAmb[0] = 1;

        arrayModelos[6+i]->kAmb[1] = 1;

        arrayModelos[6+i]->kAmb[2] = 1;

        arrayModelos[6+i]->kAmb[3] = 1.0;

        arrayModelos[6+i]->kDif[0] = 0;

        arrayModelos[6+i]->kDif[1] = 0;

        arrayModelos[6+i]->kDif[2] = 0.7;

        arrayModelos[6+i]->kDif[3] = 1.0;

        arrayModelos[6+i]->kEsp[0] = 0.7;

        arrayModelos[6+i]->kEsp[1] = 0.7;

        arrayModelos[6+i]->kEsp[2] = 0.7;

        arrayModelos[6+i]->kEsp[3] = 1.0;

        arrayModelos[6+i]->coefDePhong = 100;

        /* Parametros das transformacoes */

        arrayModelos[6+i]->deslY = 0.0;

        arrayModelos[6+i]->deslZ = 0.0;

        arrayModelos[6+i]->angRotXX = 0;

        arrayModelos[6+i]->angRotYY = 0;

        arrayModelos[6+i]->angRotZZ = 0;

        arrayModelos[6+i]->factorEscX = 0.3;

        arrayModelos[6+i]->factorEscY = 0.3;

        arrayModelos[6+i]->factorEscZ = 0.3;

        arrayModelos[6+i]->rotacaoOnXX = 0;

        arrayModelos[6+i]->rotacaoOnYY = 1;

        arrayModelos[6+i]->rotacaoOnZZ = 0;
    }

    arrayModelos[6]->deslX = -0.65;
    arrayModelos[7]->deslX = 0.00;
    arrayModelos[8]->deslX = 0.65;

    // Ponteiro 2 --> Segundos

    for (i = 0; i < 3; i++)
    {
        arrayModelos[9+i] = (pontModelo) malloc( sizeof(Registo_Modelo) );

        loadOBJ( "pointerV3.obj", &(arrayModelos[9+i]->numVertices),
                                                     &(arrayModelos[9+i]->arrayVertices),
                                                      &(arrayModelos[9+i]->arrayNormais)  );


        /* Array vazio para guardar a cor calculada para cada vertice */

        arrayModelos[9+i]->arrayCores = (GLfloat*) calloc( 3 * arrayModelos[9+i]->numVertices, sizeof( GLfloat) );

        /* Propriedades do material */

        arrayModelos[9+i]->kAmb[0] = 1;

        arrayModelos[9+i]->kAmb[1] = 1;

        arrayModelos[9+i]->kAmb[2] = 1;

        arrayModelos[9+i]->kAmb[3] = 1.0;

        arrayModelos[9+i]->kDif[0] = 0;

        arrayModelos[9+i]->kDif[1] = 0;

        arrayModelos[9+i]->kDif[2] = 0.7;

        arrayModelos[9+i]->kDif[3] = 1.0;

        arrayModelos[9+i]->kEsp[0] = 0.7;

        arrayModelos[9+i]->kEsp[1] = 0.7;

        arrayModelos[9+i]->kEsp[2] = 0.7;

        arrayModelos[9+i]->kEsp[3] = 1.0;

        arrayModelos[9+i]->coefDePhong = 100;

        /* Parametros das transformacoes */

        arrayModelos[9+i]->deslY = 0.0;

        arrayModelos[9+i]->deslZ = 0.0;

        arrayModelos[9+i]->angRotXX = 0;

        arrayModelos[9+i]->angRotYY = 0;

        arrayModelos[9+i]->angRotZZ = 0;

        arrayModelos[9+i]->factorEscX = 0.3;

        arrayModelos[9+i]->factorEscY = 0.3;

        arrayModelos[9+i]->factorEscZ = 0.3;

        arrayModelos[9+i]->rotacaoOnXX = 1;

        arrayModelos[9+i]->rotacaoOnYY = 1;

        arrayModelos[9+i]->rotacaoOnZZ = 1;
    }
    arrayModelos[9]->deslX = -0.65;
    arrayModelos[10]->deslX = 0.00;
    arrayModelos[11]->deslX = 0.65;

}


void libertarArraysModelo( int i )
{
    free( arrayModelos[i]->arrayVertices );

    free( arrayModelos[i]->arrayNormais );

    free( arrayModelos[i]->arrayCores );
}


void libertarModelos( void )
{
    int i;

    for ( i = 0; i < numModelos; i++ )
    {
        free( arrayModelos[i]->arrayVertices );

        free( arrayModelos[i]->arrayNormais );

        free( arrayModelos[i]->arrayCores );

        free( arrayModelos[i] );
    }

    free( arrayModelos );

    numModelos = 0;
}

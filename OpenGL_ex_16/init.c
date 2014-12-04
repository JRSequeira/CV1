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

#include "angleRotation.h"

/* 
Matriz contendo os valores Kamb, Kdiff, Kesp e nPhong
*/

float mat[5][10] = 
    {
        {0.21, 0.13, 0.05, 0.71, 0.43, 0.18, 0.39, 0.27, 0.17, 25.6},
        {0.25, 0.25, 0.25, 0.4, 0.4, 0.4, 0.77, 0.77, 0.77, 76.8},
        {0.25, 0.20, 0.07, 0.75, 0.60, 0.23, 0.63, 0.56, 0.37, 51.2},
        {0.23, 0.23, 0.23, 0.28, 0.28, 0.28, 0.77, 0.77, 0.77, 89.6},
        {0.0, 0.0, 0.5, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 125.0}
    };

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

    windowHandle = glutCreateWindow( "Project_CV_64191_64645");

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
    numFocos = 3;

    /* Criar o array */

    arrayFocos = (pontFoco*) malloc( numFocos * sizeof(pontFoco) );

    /* Foco 0 Alarm */

    arrayFocos[0] = (pontFoco) malloc( sizeof(Registo_Foco) );

    arrayFocos[0]->focoIsOn = 0;

    arrayFocos[0]->posicao[0] = 0;

    arrayFocos[0]->posicao[1] = -10.0;

    arrayFocos[0]->posicao[2] = 2.0;

    arrayFocos[0]->posicao[3] = 0.0; /* Foco DIRECCIONAL */

    arrayFocos[0]->intensidade[0] = 1.0;

    arrayFocos[0]->intensidade[1] = 0.0;

    arrayFocos[0]->intensidade[2] = 0.0;

    arrayFocos[0]->intensidade[3] = 1.0;

    arrayFocos[0]->luzAmbiente[0] = 0.2;

    arrayFocos[0]->luzAmbiente[1] = 0.0;

    arrayFocos[0]->luzAmbiente[2] = 0.0;

    arrayFocos[0]->luzAmbiente[3] = 1.0;

    arrayFocos[0]->translX = 0.0;

    arrayFocos[0]->translY = 0.0;

    arrayFocos[0]->translZ = 0.0;

    arrayFocos[0]->angRotXX = 0.0;

    arrayFocos[0]->angRotYY = 0.0;

    arrayFocos[0]->angRotZZ = 0.0;

    arrayFocos[0]->rotacaoOnXX = 1;

    arrayFocos[0]->rotacaoOnYY = 1;

    arrayFocos[0]->rotacaoOnZZ = 1;

    /* Foco 1 - Alarm */

    arrayFocos[1] = (pontFoco) malloc( sizeof(Registo_Foco) );

    arrayFocos[1]->focoIsOn = 0;

    arrayFocos[1]->posicao[0] = 0;

    arrayFocos[1]->posicao[1] = 10.0;

    arrayFocos[1]->posicao[2] = -2.0;

    arrayFocos[1]->posicao[3] = 1.0; /* Foco PONTUAL */

    arrayFocos[1]->intensidade[0] = 1.0;

    arrayFocos[1]->intensidade[1] = 0.0;

    arrayFocos[1]->intensidade[2] = 0.0;

    arrayFocos[1]->intensidade[3] = 1.0;

    arrayFocos[1]->luzAmbiente[0] = 0.2;

    arrayFocos[1]->luzAmbiente[1] = 0.0;

    arrayFocos[1]->luzAmbiente[2] = 0.0;

    arrayFocos[1]->luzAmbiente[3] = 1.0;

    arrayFocos[1]->translX = 0.0;

    arrayFocos[1]->translY = 0.0;

    arrayFocos[1]->translZ = 0.0;

    arrayFocos[1]->angRotXX = 0.0;

    arrayFocos[1]->angRotYY = 0.0;

    arrayFocos[1]->angRotZZ = 0.0;

    arrayFocos[1]->rotacaoOnXX = 1;

    arrayFocos[1]->rotacaoOnYY = 1;

    arrayFocos[1]->rotacaoOnZZ = 1;

    /* Foco 2 - Normal */

    arrayFocos[2] = (pontFoco) malloc( sizeof(Registo_Foco) );

    arrayFocos[2]->focoIsOn = 1;

    arrayFocos[2]->posicao[0] = 0;

    arrayFocos[2]->posicao[1] = 2.0;

    arrayFocos[2]->posicao[2] = 2.0;

    arrayFocos[2]->posicao[3] = 1.0; /* Foco PONTUAL */

    arrayFocos[2]->intensidade[0] = 0.8;

    arrayFocos[2]->intensidade[1] = 0.8;

    arrayFocos[2]->intensidade[2] = 0.2;

    arrayFocos[2]->intensidade[3] = 1.0;

    arrayFocos[2]->luzAmbiente[0] = 0.4;

    arrayFocos[2]->luzAmbiente[1] = 0.4;

    arrayFocos[2]->luzAmbiente[2] = 0.4;

    arrayFocos[2]->luzAmbiente[3] = 1.0;

    arrayFocos[2]->translX = 0.0;

    arrayFocos[2]->translY = 0.0;

    arrayFocos[2]->translZ = 0.0;

    arrayFocos[2]->angRotXX = 0.0;

    arrayFocos[2]->angRotYY = 0.0;

    arrayFocos[2]->angRotZZ = 0.0;

    arrayFocos[2]->rotacaoOnXX = 1;

    arrayFocos[2]->rotacaoOnYY = 1;

    arrayFocos[2]->rotacaoOnZZ = 1;

    
}

void inicializarModelos( void )
{
    numModelos = 12;

    /* Criar o array */

    arrayModelos = (pontModelo *) malloc( numModelos * sizeof(pontModelo) );

    // RELOGIO 0
    arrayModelos[0] = (pontModelo) malloc( sizeof(Registo_Modelo) );
    
    loadOBJ("model_square.obj", &(arrayModelos[0]->numVertices),
                   &(arrayModelos[0]->arrayVertices),
                   &(arrayModelos[0]->arrayNormais));
                   
/*
    lerFicheiroOBJ("prismaHexagonal.OBJ", &(arrayModelos[0]->numVertices),
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

    arrayModelos[0]->deslX = -0.7;

    arrayModelos[0]->deslY = 0;

    arrayModelos[0]->deslZ = 0;

    arrayModelos[0]->angRotXX = 0;

    arrayModelos[0]->angRotYY = 0;

    arrayModelos[0]->angRotZZ = 0;

    arrayModelos[0]->factorEscX = 0.9;

    arrayModelos[0]->factorEscY = 0.9;

    arrayModelos[0]->factorEscZ = 0.9;

    arrayModelos[0]->rotacaoOnXX = 0;

    arrayModelos[0]->rotacaoOnYY = 1;

    arrayModelos[0]->rotacaoOnZZ = 0;

    // RELOGIO 1

    arrayModelos[1] = (pontModelo) malloc( sizeof(Registo_Modelo) );
    
    loadOBJ("model_circle.obj", &(arrayModelos[1]->numVertices),
                   &(arrayModelos[1]->arrayVertices),
                   &(arrayModelos[1]->arrayNormais));
/*
    lerFicheiroOBJ("prismaHexagonal.OBJ", &(arrayModelos[1]->numVertices),
                   &(arrayModelos[1]->arrayVertices),
                   &(arrayModelos[1]->arrayNormais));
*/
    /* Array vazio para guardar a cor calculada para cada vertice */

    arrayModelos[1]->arrayCores = (GLfloat *) calloc( 3 * arrayModelos[1]->numVertices, sizeof( GLfloat) );

    /* Propriedades do material */

    arrayModelos[1]->kAmb[0] = 0.21;

    arrayModelos[1]->kAmb[1] = 0.13;

    arrayModelos[1]->kAmb[2] = 0.05;

    arrayModelos[1]->kAmb[3] = 1.0;

    arrayModelos[1]->kDif[0] = 0.71;

    arrayModelos[1]->kDif[1] = 0.43;

    arrayModelos[1]->kDif[2] = 0.18;

    arrayModelos[1]->kDif[3] = 1.0;

    arrayModelos[1]->kEsp[0] = 0.39;

    arrayModelos[1]->kEsp[1] = 0.27;

    arrayModelos[1]->kEsp[2] = 0.17;

    arrayModelos[1]->kEsp[3] = 1.0;

    arrayModelos[1]->coefDePhong = 25.6;

    /* Parametros das transformacoes */

    arrayModelos[1]->deslX = -0.05;

    arrayModelos[1]->deslY = 0.05;

    arrayModelos[1]->deslZ = 0;

    arrayModelos[1]->angRotXX = 0;

    arrayModelos[1]->angRotYY = 0;

    arrayModelos[1]->angRotZZ = 0;

    arrayModelos[1]->factorEscX = 1;

    arrayModelos[1]->factorEscY = 1;

    arrayModelos[1]->factorEscZ = 1;

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

    arrayModelos[2]->kAmb[0] = 0.3;

    arrayModelos[2]->kAmb[1] = 0.0;

    arrayModelos[2]->kAmb[2] = 0.0;

    arrayModelos[2]->kAmb[3] = 1.0;

    arrayModelos[2]->kDif[0] = 0.6;

    arrayModelos[2]->kDif[1] = 0.0;

    arrayModelos[2]->kDif[2] = 0.0;

    arrayModelos[2]->kDif[3] = 1.0;

    arrayModelos[2]->kEsp[0] = 0.8;

    arrayModelos[2]->kEsp[1] = 0.6;

    arrayModelos[2]->kEsp[2] = 0.6;

    arrayModelos[2]->kEsp[3] = 1.0;

    arrayModelos[2]->coefDePhong = 32.0;

    /* Parametros das transformacoes */

    arrayModelos[2]->deslX = 0.65;

    arrayModelos[2]->deslY = 0;

    arrayModelos[2]->deslZ = 0;

    arrayModelos[2]->angRotXX = 90;

    arrayModelos[2]->angRotYY = 0;

    arrayModelos[2]->angRotZZ = 0;

    arrayModelos[2]->factorEscX = 0.35;

    arrayModelos[2]->factorEscY = 0.35;

    arrayModelos[2]->factorEscZ = 0.35;

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

/*
        lerVerticesDeFicheiro( "ponteiro.txt", &(arrayModelos[3+i]->numVertices),
                                                 &(arrayModelos[3+i]->arrayVertices) );
        /* Determinar as normais unitarias a cada triangulo */
/*
        arrayModelos[3+i]->arrayNormais = calcularNormaisTriangulos( arrayModelos[3+i]->numVertices,
                                                               arrayModelos[3+i]->arrayVertices );

*/
        /* Array vazio para guardar a cor calculada para cada vertice */

        arrayModelos[3+i]->arrayCores = (GLfloat*) calloc( 3 * arrayModelos[3+i]->numVertices, sizeof( GLfloat) );

        /* Propriedades do material */

        arrayModelos[3+i]->kAmb[0] = 0.25;

        arrayModelos[3+i]->kAmb[1] = 0.15;

        arrayModelos[3+i]->kAmb[2] = 0.06;

        arrayModelos[3+i]->kAmb[3] = 1.0;

        arrayModelos[3+i]->kDif[0] = 0.4;

        arrayModelos[3+i]->kDif[1] = 0.24;

        arrayModelos[3+i]->kDif[2] = 0.1;

        arrayModelos[3+i]->kDif[3] = 1.0;

        arrayModelos[3+i]->kEsp[0] = 0.77;

        arrayModelos[3+i]->kEsp[1] = 0.46;

        arrayModelos[3+i]->kEsp[2] = 0.20;

        arrayModelos[3+i]->kEsp[3] = 1.0;

        arrayModelos[3+i]->coefDePhong = 76.8;

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
 
    arrayModelos[3]->deslX = -0.7;
    arrayModelos[4]->deslX = -0.05;
    arrayModelos[4]->deslY = 0.05;
    arrayModelos[5]->deslX = 0.65;
    
    // Ponteiro 1 --> Minutos
    for (i = 0; i < 3; i++)
    {
        arrayModelos[6+i] = (pontModelo) malloc( sizeof(Registo_Modelo) );

        
        loadOBJ( "pointerV2.obj", &(arrayModelos[6+i]->numVertices),
                                                     &(arrayModelos[6+i]->arrayVertices),
                                                      &(arrayModelos[6+i]->arrayNormais)  );
   /*     lerVerticesDeFicheiro( "ponteiro.txt", &(arrayModelos[6+i]->numVertices),
                                                 &(arrayModelos[6+i]->arrayVertices) );
        arrayModelos[6+i]->arrayNormais = calcularNormaisTriangulos( arrayModelos[6+i]->numVertices,
                                                               arrayModelos[6+i]->arrayVertices );

        /* Array vazio para guardar a cor calculada para cada vertice */

        arrayModelos[6+i]->arrayCores = (GLfloat*) calloc( 3 * arrayModelos[6+i]->numVertices, sizeof( GLfloat) );

        /* Propriedades do material */

        arrayModelos[6+i]->kAmb[0] = 0.33;

        arrayModelos[6+i]->kAmb[1] = 0.22;

        arrayModelos[6+i]->kAmb[2] = 0.03;

        arrayModelos[6+i]->kAmb[3] = 1.0;

        arrayModelos[6+i]->kDif[0] = 0.78;

        arrayModelos[6+i]->kDif[1] = 0.57;

        arrayModelos[6+i]->kDif[2] = 0.11;

        arrayModelos[6+i]->kDif[3] = 1.0;

        arrayModelos[6+i]->kEsp[0] = 0.99;

        arrayModelos[6+i]->kEsp[1] = 0.94;

        arrayModelos[6+i]->kEsp[2] = 0.81;

        arrayModelos[6+i]->kEsp[3] = 1.0;

        arrayModelos[6+i]->coefDePhong = 27.9;

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

    arrayModelos[6]->deslX = -0.7;
    arrayModelos[7]->deslX = -0.05;
    arrayModelos[7]->deslY = 0.05;
    arrayModelos[8]->deslX = 0.65;

    // Ponteiro 2 --> Segundos

    for (i = 0; i < 3; i++)
    {
        arrayModelos[9+i] = (pontModelo) malloc( sizeof(Registo_Modelo) );

        
        loadOBJ( "pointerV3.obj", &(arrayModelos[9+i]->numVertices),
                                                     &(arrayModelos[9+i]->arrayVertices),
                                                      &(arrayModelos[9+i]->arrayNormais)  );
      /*  lerVerticesDeFicheiro( "ponteiro.txt", &(arrayModelos[9+i]->numVertices),
                                                 &(arrayModelos[9+i]->arrayVertices) );
        arrayModelos[9+i]->arrayNormais = calcularNormaisTriangulos( arrayModelos[9+i]->numVertices,
                                                               arrayModelos[9+i]->arrayVertices );


        /* Array vazio para guardar a cor calculada para cada vertice */

        arrayModelos[9+i]->arrayCores = (GLfloat*) calloc( 3 * arrayModelos[9+i]->numVertices, sizeof( GLfloat) );

        /* Propriedades do material */

        arrayModelos[9+i]->kAmb[0] = 0.25;

        arrayModelos[9+i]->kAmb[1] = 0.22;

        arrayModelos[9+i]->kAmb[2] = 0.06;

        arrayModelos[9+i]->kAmb[3] = 1.0;

        arrayModelos[9+i]->kDif[0] = 0.35;

        arrayModelos[9+i]->kDif[1] = 0.31;

        arrayModelos[9+i]->kDif[2] = 0.09;

        arrayModelos[9+i]->kDif[3] = 1.0;

        arrayModelos[9+i]->kEsp[0] = 0.8;

        arrayModelos[9+i]->kEsp[1] = 0.73;

        arrayModelos[9+i]->kEsp[2] = 0.21;

        arrayModelos[9+i]->kEsp[3] = 1.0;

        arrayModelos[9+i]->coefDePhong = 83.2;

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
    arrayModelos[9]->deslX = -0.7;
    arrayModelos[10]->deslX = -0.05;
    arrayModelos[10]->deslY = 0.05;
    arrayModelos[11]->deslX = 0.65;

}

void alterarModelo(int relogio, int op)
{
    arrayModelos[relogio]->kAmb[0] = mat[op][0];

    arrayModelos[relogio]->kAmb[1] = mat[op][1];

    arrayModelos[relogio]->kAmb[2] = mat[op][2];

    arrayModelos[relogio]->kAmb[3] = 1.0;

    arrayModelos[relogio]->kDif[0] = mat[op][3];

    arrayModelos[relogio]->kDif[1] = mat[op][4];

    arrayModelos[relogio]->kDif[2] = mat[op][5];

    arrayModelos[relogio]->kDif[3] = 1.0;

    arrayModelos[relogio]->kEsp[0] = mat[op][6];

    arrayModelos[relogio]->kEsp[1] = mat[op][7];

    arrayModelos[relogio]->kEsp[2] = mat[op][8];

    arrayModelos[relogio]->kEsp[3] = 1.0;

    arrayModelos[relogio]->coefDePhong = mat[op][9];

    glutPostRedisplay();
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

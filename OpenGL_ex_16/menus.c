/*
 * menus.c
 *
 * Ficheiro de implementacao do modulo MENUS.
 *
 * J. Madeira - Out/2012
 */


/* Incluir os ficheiros cabecalhos necessarios */

#include <stdlib.h>


#define GLEW_STATIC /* Necessario se houver problemas com a lib */

#include <GL/glew.h>

#include <GL/freeglut.h>


#include "consoleIO.h"

#include "globals.h"

#include "init.h"

#include "menus.h"

#include "models.h"


/* ----------------------------------------------------------------------- */

/* Definicao dos menus e sub-menus usando um tipo auxiliar e arrays */

/* Ref.: "OpenGL: A Primer" - p. 219-220 */

typedef struct menuItemStruct {

    char* item; /* O texto do item */

    char  val;  /* O valor retornado */

} menuItemStruct;

/* Menu 1 - Botao Esquerdo */

static menuItemStruct menu1[] = {

				{"Animar Focos ON/OFF",   'A'},
				{"Animar Modelos ON/OFF", 'B'},
				{"-------------------",   '-'},
				{"F. PONT./DIR. ON/OFF",  'F'},
				{"-------------------",   '-'},
                {"Posicao ORIGINAL",      'o'},
				{"-------------------",   '-'},
				{"Proj. Paralela",        'O'},
				{"Proj. Perspectiva",     'P'}
};

int numItensMenu1 = sizeof( menu1 ) / sizeof( menuItemStruct );

/* Menu 2 - Botao Direito */

static menuItemStruct menu2[] = {

				{"Ler Ficheiros TXT",   'L'},
				{"Ler Ficheiros OBJ",   'l'},
				{"-----------------",   '-'},
				{"Faces",               'F'},
				{"Arestas",             'A'},
				{"Vertices",            'V'},
				{"-----------------",   '-'},
				{"Sair",                '9'}
};

int numItensMenu2 = sizeof( menu2 ) / sizeof( menuItemStruct );


/* ----------------------------------------------------------------------- */

/* Callback function para o MENU 2 - Botao Direito */

static void myMenuEsq( int i )
{
	switch( menu1[i].val ) {

	case 'o' :

        /* Modelos */

        arrayModelos[0]->angRotXX = -10;

        arrayModelos[0]->angRotYY = -60;

        arrayModelos[0]->angRotZZ = 0;

        arrayModelos[1]->angRotXX = -10;

        arrayModelos[1]->angRotYY = +60;

        arrayModelos[1]->angRotZZ = 0;

        /* FOCOS */

        arrayFocos[0]->posicao[0] = 0.0;

        arrayFocos[0]->posicao[1] = 0.0;

        arrayFocos[0]->posicao[2] = 5.0;

        arrayFocos[0]->angRotXX = 0;

        arrayFocos[0]->angRotYY = 0;

        arrayFocos[0]->angRotZZ = 0;

        glutPostRedisplay();

        break;

	case 'O' :

        matrizProj = IDENTITY_MATRIX;

        glutPostRedisplay();

		break;

	case 'P' :

        matrizProj = CreateProjectionMatrix( 60, 1, 1, 40 );

        /* Posicionar no interior do View Volome */

        Translate( &matrizProj, 0, 0, -2 );

        glutPostRedisplay();

		break;

	case 'A' :

        if( animacaoFocosON )
        {
            animacaoFocosON = 0;
        }
        else
        {
            animacaoFocosON = 1;
        }

        glutPostRedisplay();

		break;

	case 'B' :

        if( animacaoModelosON )
        {
            animacaoModelosON = 0;
        }
        else
        {
            animacaoModelosON = 1;
        }

        glutPostRedisplay();

		break;

	case 'F' :

        if( arrayFocos[0]->posicao[3] == 0.0 )
        {
            arrayFocos[0]->posicao[3] = 1.0;
        }
        else
        {
            arrayFocos[0]->posicao[3] = 0.0;
        }

        glutPostRedisplay();

		break;
	}
}

static void myMenuDir( int i )
{
    char nomeF[40];

	switch( menu2[i].val ) {

	case 'L' :

        /* MODELO 0 */

        libertarArraysModelo( 0 );

        nomeFicheiro( nomeF );

        lerVerticesDeFicheiro( nomeF, &(arrayModelos[0]->numVertices), &(arrayModelos[0]->arrayVertices) );

        /* Determinar as normais unitarias a cada triangulo */

        arrayModelos[0]->arrayNormais = calcularNormaisTriangulos( arrayModelos[0]->numVertices, arrayModelos[0]->arrayVertices );

        /* Array vazio para guardar a cor atribuida a cada vertice */

        arrayModelos[0]->arrayCores = (GLfloat*) calloc( 3 * arrayModelos[0]->numVertices, sizeof( GLfloat) );

        /* MODELO 1 */

        libertarArraysModelo( 1 );

        nomeFicheiro( nomeF );

        lerVerticesDeFicheiro( nomeF, &(arrayModelos[1]->numVertices), &(arrayModelos[1]->arrayVertices) );

        /* Determinar as normais unitarias a cada triangulo */

        arrayModelos[1]->arrayNormais = calcularNormaisTriangulos( arrayModelos[1]->numVertices, arrayModelos[1]->arrayVertices );

        /* Array vazio para guardar a cor atribuida a cada vertice */

        arrayModelos[1]->arrayCores = (GLfloat*) calloc( 3 * arrayModelos[1]->numVertices, sizeof( GLfloat) );

        /* MANTER as propriedades do material */

        /* E os parametros das transformacoes */

        glutPostRedisplay();

		break;

	case 'l' :

        libertarArraysModelo( 0 );

        nomeFicheiro( nomeF );

        lerFicheiroOBJ( nomeF, &(arrayModelos[0]->numVertices), &(arrayModelos[0]->arrayVertices), &(arrayModelos[0]->arrayNormais) );

        /* Array vazio para guardar a cor atribuida a cada vertice */

        arrayModelos[0]->arrayCores = (GLfloat*) calloc( 3 * arrayModelos[0]->numVertices, sizeof( GLfloat) );

        libertarArraysModelo( 1 );

        nomeFicheiro( nomeF );

        lerFicheiroOBJ( nomeF, &(arrayModelos[1]->numVertices), &(arrayModelos[1]->arrayVertices), &(arrayModelos[1]->arrayNormais) );

        /* Array vazio para guardar a cor atribuida a cada vertice */

        arrayModelos[1]->arrayCores = (GLfloat*) calloc( 3 * arrayModelos[1]->numVertices, sizeof( GLfloat) );

        /* MANTER as propriedades do material */

        /* E os parametros das transformacoes */

        glutPostRedisplay();

		break;

	case 'F' :

        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

        glutPostRedisplay();

		break;

	case 'A' :

        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

        glutPostRedisplay();

		break;

	case 'V' :

        glPolygonMode( GL_FRONT_AND_BACK, GL_POINT );

        glutPostRedisplay();

		break;

	case '9' :

        exit( EXIT_SUCCESS );

		break;
	}
}

/* Criar os menus */

void criarMenus( void )
{
    int i;

    /* MENU 1 */

	glutCreateMenu( myMenuEsq );

    for( i=0; i<numItensMenu1; i++ )
    {
	    /* Os itens do menu e os valores devolvidos a funcao callback */

        glutAddMenuEntry( menu1[i].item, i );
	}

	/* O botao do rato associado */

	glutAttachMenu( GLUT_LEFT_BUTTON );

    /* MENU 2 */

	glutCreateMenu( myMenuDir );

    for( i=0; i<numItensMenu2; i++ )
    {
	    /* Os itens do menu e os valores devolvidos a funcao callback */

        glutAddMenuEntry( menu2[i].item, i );
	}

	/* O botao do rato associado */

	glutAttachMenu( GLUT_RIGHT_BUTTON );
}


/* ----------------------------------------------------------------------- */



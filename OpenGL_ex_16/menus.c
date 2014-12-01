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

#include "angteRotation.h"

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

				{"Definir alarme",   'A'},
                {"Fuso Horario", 'B'},
                {"Cronometro", 'C'}
};

int numItensMenu1 = sizeof( menu1 ) / sizeof( menuItemStruct );

/* ----------------------------------------------------------------------- */

/* Callback function para o MENU 2 - Botao Direito */

static void myMenuEsq( int i )
{
	switch( menu1[i].val ) {
        case 'A':{
            getUserAlarm();
            glutPostRedisplay();
            break;
        }
        case 'B':{
            getNewFusoHorario();
            glutPostRedisplay();
            break;
        }
        case 'C':{
            getTimerOption();
            break;
        }
    }	
}

static void myMenuDir( int i )
{
   
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

 }
/* ----------------------------------------------------------------------- */



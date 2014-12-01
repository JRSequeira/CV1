/*
 * callbacks.c
 *
 * J. Madeira - Nov/2012
 *
 */


#include <stdlib.h>

#include <stdio.h>

#include <string.h>

#include <math.h>


#define GLEW_STATIC /* Necessario se houver problemas com a lib */

#include <GL/glew.h>

#include <GL/freeglut.h>

#include <time.h>

#include "angteRotation.h"

#include "globals.h"

#include "callbacks.h"

#include "consoleIO.h"

#include "shading.h"


/* Callback functions */

void myDisplay( void )
{
    int m;

    /* Limpar a janela */

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    /* SHADERS */

    glUseProgram( programaGLSL );

    /* Para cada um dos modelos da cena */

    for( m = 0; m < numModelos; m++ )
    {

        /* Input para o Vertex-Shader */

        glEnableVertexAttribArray( attribute_coord3d );

        glEnableVertexAttribArray( attribute_corRGB );

        /* Caracteristicas do array de coordenadas */

        glVertexAttribPointer( attribute_coord3d, // attribute

                          3,                 // number of elements per vertex, here (x,y,z)

                          GL_FLOAT,          // the type of each element

                          GL_FALSE,          // take our values as-is

                          0,                 // no extra data between each position

                          arrayModelos[m]->arrayVertices );   // pointer to the C array

        /* Caracteristicas do array de cores */

        glVertexAttribPointer( attribute_corRGB, // attribute

                          3,                 // number of elements per vertex, here (R,G,B)

                          GL_FLOAT,          // the type of each element

                          GL_FALSE,          // take our values as-is

                          0,                 // no extra data between each position

                          arrayModelos[m]->arrayCores );    // pointer to the C array

        /* ATENCAO : Ordem das transformacoes !! */

        matrizModelView = IDENTITY_MATRIX;

        /* Deslocar para mais longe */

        Translate( &matrizModelView, arrayModelos[m]->deslX, arrayModelos[m]->deslY, arrayModelos[m]->deslZ );

        RotateAboutX( &matrizModelView, DegreesToRadians( arrayModelos[m]->angRotXX ) );

        RotateAboutY( &matrizModelView, DegreesToRadians( arrayModelos[m]->angRotYY ) );

        RotateAboutZ( &matrizModelView, DegreesToRadians( arrayModelos[m]->angRotZZ ) );


        /* Diminuir o tamanho do modelo para nao sair fora do view volume */

        Scale( &matrizModelView, arrayModelos[m]->factorEscX, arrayModelos[m]->factorEscY, arrayModelos[m]->factorEscZ );

        /* Matriz de projeccao */

        glUniformMatrix4fv( uniform_matriz_proj, 1, GL_FALSE, matrizProj.m);

        /* Matriz de transformacao */

        glUniformMatrix4fv( uniform_matriz_model_view, 1, GL_FALSE, matrizModelView.m);

        /* Aplicar o Modelo de Iluminação ao m-esimo modelo */

        smoothShading( m );

        glDrawArrays( GL_TRIANGLES, 0, arrayModelos[m]->numVertices );

        glDisableVertexAttribArray( attribute_coord3d );

        glDisableVertexAttribArray( attribute_corRGB );

    }

    /* Display the result */

    /* DOUBLE-BUFFERING */

    glutSwapBuffers();
}


void myKeyboard( unsigned char key, int x, int y )
{
    int i;

    switch( key )
    {
        case 'Q' :

        case 'q' :

        case 27  :  exit( EXIT_SUCCESS );

        
    }
}


void mySpecialKeys( int key, int x, int y )
{
	/* Usar as teclas de cursor para controlar as rotacoes */

    switch( key )
    {
        
    }
}


void myTimer( int value )
{
    int flag = 0;
    time_t epoch_time;
    epoch_time = time(NULL);
    struct tm *tm_struct;
    tm_struct = localtime(&epoch_time);
    int h = tm_struct->tm_hour;
    int m =tm_struct->tm_min;
    int s = tm_struct->tm_sec;

    int i = 0;
    for (i = 0; i < 3; i++)
    {
        arrayModelos[3+i]->angRotZZ = 360 - hour(h) ;
    }
    for (i = 0; i < 3; i++)
    {
        arrayModelos[6+i]->angRotZZ = 360 - minute(m);
    }
    for (i = 0; i < 3; i++)
    {
        arrayModelos[9+i]->angRotZZ = 360 - second(s);
    }
    flag = 1;

    int difh, difm;
    int ah = getAlarmHour();
    int am = getAlarmMinute();
    if(ah != -1){
        Dif(ah, am,h, m, &difh, &difm);
        if(difh == 0 && difm == 0){
            //ring alarm

        }
        else{
        printAlarm(difh, difm);
        }
    }

    if( animacaoModelosON )
    {
        /* MODELOS */


    }

    if( animacaoFocosON )
    {
        if( arrayFocos[0]->rotacaoOnXX )
        {
            arrayFocos[0]->angRotXX += 10.0;

            if( arrayFocos[0]->angRotXX > 360.0 )
            {
                arrayFocos[0]->angRotXX -= 360.0;
            }

            flag = 1;
        }
    }

    if( flag )
    {
        glutPostRedisplay();
    }

    glutTimerFunc( 250, myTimer, 0 );
}


void registarCallbackFunctions( void )
{
   glutDisplayFunc( myDisplay );

   glutTimerFunc( 250, myTimer, 0 );

   glutKeyboardFunc( myKeyboard );

   glutSpecialFunc( mySpecialKeys );
}

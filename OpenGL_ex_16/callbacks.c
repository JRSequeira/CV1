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
static int freq = 0;

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

        case 'Z' :

        case 'z' :

            arrayModelos[0]->angRotZZ += 5.0;

            if( arrayModelos[0]->angRotZZ > 360.0 )
            {
                arrayModelos[0]->angRotZZ -= 360.0;
            }

            arrayModelos[1]->angRotZZ -= 5.0;

            if( arrayModelos[1]->angRotZZ < 0.0 )
            {
                arrayModelos[1]->angRotZZ += 360.0;
            }

            glutPostRedisplay();

            break;

        case 'X' :

        case 'x' :

            arrayModelos[0]->angRotZZ -= 5.0;

            if( arrayModelos[0]->angRotZZ < 0.0 )
            {
                arrayModelos[0]->angRotZZ += 360.0;
            }

            arrayModelos[1]->angRotZZ += 5.0;

            if( arrayModelos[1]->angRotZZ > 360.0 )
            {
                arrayModelos[1]->angRotZZ -= 360.0;
            }

            glutPostRedisplay();

            break;

        case '+' :

            arrayFocos[0]->posicao[0] *= 1.2;

            arrayFocos[0]->posicao[1] *= 1.2;

            arrayFocos[0]->posicao[2] *= 1.2;

            glutPostRedisplay();

            break;

        case '-' :

            arrayFocos[0]->posicao[0] *= 0.8;

            arrayFocos[0]->posicao[1] *= 0.8;

            arrayFocos[0]->posicao[2] *= 0.8;

            glutPostRedisplay();

            break;

        case 'A' :

            for( i = 0; i < 3; i++ )
            {
                if( ( arrayModelos[0]->kAmb[i] += 0.1 ) > 1.0 )
                {
                    arrayModelos[0]->kAmb[i] = 1.0;
                }
            }

            for( i = 0; i < 3; i++ )
            {
                if( ( arrayModelos[1]->kAmb[i] += 0.1 ) > 1.0 )
                {
                    arrayModelos[1]->kAmb[i] = 1.0;
                }
            }

            glutPostRedisplay();

            break;

        case 'a' :

            for( i = 0; i < 3; i++ )
            {
                if( ( arrayModelos[0]->kAmb[i] -= 0.1 ) < 0.0 )
                {
                    arrayModelos[0]->kAmb[i] = 0.0;
                }
            }

            for( i = 0; i < 3; i++ )
            {
                if( ( arrayModelos[1]->kAmb[i] -= 0.1 ) < 0.0 )
                {
                    arrayModelos[1]->kAmb[i] = 0.0;
                }
            }

            glutPostRedisplay();

            break;

        case 'D' :

            for( i = 0; i < 3; i++ )
            {
                if( ( arrayModelos[0]->kDif[i] += 0.1 ) > 1.0 )
                {
                    arrayModelos[0]->kDif[i] = 1.0;
                }
            }

            for( i = 0; i < 3; i++ )
            {
                if( ( arrayModelos[1]->kDif[i] += 0.1 ) > 1.0 )
                {
                    arrayModelos[1]->kDif[i] = 1.0;
                }
            }

            glutPostRedisplay();

            break;

        case 'd' :

            for( i = 0; i < 3; i++ )
            {
                if( ( arrayModelos[0]->kDif[i] -= 0.1 ) < 0.0 )
                {
                    arrayModelos[0]->kDif[i] = 0.0;
                }
            }

            for( i = 0; i < 3; i++ )
            {
                if( ( arrayModelos[1]->kDif[i] -= 0.1 ) < 0.0 )
                {
                    arrayModelos[1]->kDif[i] = 0.0;
                }
            }

            glutPostRedisplay();

            break;

        case 'E' :

            for( i = 0; i < 3; i++ )
            {
                if( ( arrayModelos[0]->kEsp[i] += 0.1 ) > 1.0 )
                {
                    arrayModelos[0]->kEsp[i] = 1.0;
                }
            }

            for( i = 0; i < 3; i++ )
            {
                if( ( arrayModelos[1]->kEsp[i] += 0.1 ) > 1.0 )
                {
                    arrayModelos[1]->kEsp[i] = 1.0;
                }
            }

            glutPostRedisplay();

            break;

        case 'e' :

            for( i = 0; i < 3; i++ )
            {
                if( ( arrayModelos[0]->kEsp[i] -= 0.1 ) < 0.0 )
                {
                    arrayModelos[0]->kEsp[i] = 0.0;
                }
            }

            for( i = 0; i < 3; i++ )
            {
                if( ( arrayModelos[1]->kEsp[i] -= 0.1 ) < 0.0 )
                {
                    arrayModelos[1]->kEsp[i] = 0.0;
                }
            }

            glutPostRedisplay();

            break;

        case 'P' :

            if( ( arrayModelos[0]->coefDePhong += 10 ) >= 256 )
            {
                arrayModelos[0]->coefDePhong = 255;
            }

            if( ( arrayModelos[1]->coefDePhong += 10 ) >= 256 )
            {
                arrayModelos[1]->coefDePhong = 255;
            }

            glutPostRedisplay();

            break;

        case 'p' :

            if( ( arrayModelos[0]->coefDePhong -= 10 ) <= 0 )
            {
                arrayModelos[0]->coefDePhong = 1;
            }

            if( ( arrayModelos[1]->coefDePhong -= 10 ) <= 0 )
            {
                arrayModelos[1]->coefDePhong = 1;
            }

            glutPostRedisplay();

            break;
    }
}


void mySpecialKeys( int key, int x, int y )
{
	/* Usar as teclas de cursor para controlar as rotacoes */

    switch( key )
    {
        case GLUT_KEY_LEFT :

            /*arrayModelos[0]->angRotYY += 5.;

            if( arrayModelos[0]->angRotYY >= 360.0 )
            {
                arrayModelos[0]->angRotYY -= 360.0;
            }
            */
            arrayModelos[1]->angRotZZ += 5.;

            if( arrayModelos[1]->angRotZZ >= 360.0 )
            {
                arrayModelos[1]->angRotZZ -= 360.0;
            }

            glutPostRedisplay();

            break;

        case GLUT_KEY_RIGHT :
            /*
             arrayModelos[0]->angRotYY -= 5.;

            if( arrayModelos[0]->angRotYY <= 360.0 )
            {
                arrayModelos[0]->angRotYY += 360.0;
            }
            */
            arrayModelos[1]->angRotZZ -= 5.;

            if( arrayModelos[1]->angRotZZ <= 360.0 )
            {
                arrayModelos[1]->angRotZZ += 360.0;
            }

            glutPostRedisplay();

            break;

        case GLUT_KEY_UP :

            arrayModelos[0]->angRotXX -= 5.0;

            if( arrayModelos[0]->angRotXX <= 0.0 )
            {
                arrayModelos[0]->angRotXX += 360.0;
            }

            arrayModelos[1]->angRotXX = -arrayModelos[0]->angRotXX + 90;

            if( arrayModelos[1]->angRotXX <= 0.0 )
            {
                arrayModelos[1]->angRotXX += 360.0;
            }

            glutPostRedisplay();

            break;

        case GLUT_KEY_DOWN :

            arrayModelos[0]->angRotXX += 5.0;

            if( arrayModelos[0]->angRotXX >= 360.0 )
            {
                arrayModelos[0]->angRotXX -= 360.0;
            }


            arrayModelos[1]->angRotXX = -arrayModelos[0]->angRotXX + 90;

            if( arrayModelos[1]->angRotXX >= 360.0 )
            {
                arrayModelos[1]->angRotXX -= 360.0;
            }

            glutPostRedisplay();

            break;
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

    if (freq == 4)
    {
        freq = 0;
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
    }
    freq++;

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
            arrayFocos[0]->translX += 2;
            if (arrayFocos[0]->translX > 10.0)
            {
                arrayFocos[0]->translX = 0;
            }
            flag = 1;

        }
        if( arrayFocos[1]->rotacaoOnXX )
        {
            arrayFocos[1]->angRotXX -= 10.0;

            if( arrayFocos[1]->angRotXX <= 0.0 )
            {
                arrayFocos[1]->angRotXX += 360.0;
            }
            arrayFocos[1]->translX -= 2;
            if (arrayFocos[1]->translX <= 0)
            {
                arrayFocos[1]->translX = 10.0;
            }
            flag = 1;
        }
    }

    if( flag )
    {
        glutPostRedisplay();
    }

    glutTimerFunc( 250/4, myTimer, 0 );
}


void registarCallbackFunctions( void )
{
   glutDisplayFunc( myDisplay );

   glutTimerFunc( 250/4, myTimer, 0 );

   glutKeyboardFunc( myKeyboard );

   glutSpecialFunc( mySpecialKeys );
}

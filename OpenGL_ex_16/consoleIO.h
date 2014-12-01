/*
 * consoleIO.h
 *
 * Ficheiro cabecalho do modulo CONSOLEIO.
 *
 * J. Madeira - Out/2012
 */


#ifndef _consoleIO_h
#define _consoleIO_h


#define GLEW_STATIC /* Necessario se houver problemas com a lib */

#include <GL/glew.h>

#include <GL/freeglut.h>


void infosConsola( void );

void getUserAlarm(void);

void getNewFusoHorario(void);

void printAlarm(int difh, int difm);


void infosModelo( int numVertices, GLfloat* arrayVertices, GLfloat* arrayNormais );

void infosVector( GLfloat* v );

void anguloRotacao( float *ang );

void parametrosTransl3D( float *dx, float *dy, float *dz );

void parametrosVarEscala3D( float *sx, float *sy, float *sz );

void nomeFicheiro( char *nome );

#endif

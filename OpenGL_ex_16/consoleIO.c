/*
 * consoleIO.c
 *
 * Ficheiro de implementacao do modulo CONSOLEIO.
 *
 * J. Madeira - Out/2012
 */


/* Incluir os ficheiros cabecalhos necessarios */


#include <stdio.h>

#include "consoleIO.h"

#include "angteRotation.h"

/* Escrever algumas informacoes na consola */

void infosConsola( void )
{
	fprintf( stdout, "\n Para Terminar: usar as teclas Q ou ESC\n\n");
}


void infosModelo( int numVertices, GLfloat* arrayVertices, GLfloat* arrayNormais )
{
    int i;

    int j;

    fprintf( stdout, "Numero de Vertices = %d\n", numVertices );

    for( i = 0; i < numVertices; i++ )
    {
        fprintf( stdout, "v[%d] = ", i );

        for( j = 0; j < 3; j++ )
        {
            fprintf( stdout, "%f ", arrayVertices[ 3 * i + j ] );
        }

        fprintf( stdout, "\n" );

        fprintf( stdout, "n[%d] = ", i );

        for( j = 0; j < 3; j++ )
        {
            fprintf( stdout, "%f ", arrayNormais[ 3 * i + j ] );
        }

        fprintf( stdout, "\n" );
    }
}


void infosVector( GLfloat* v )
{
    int j;

        for( j = 0; j < 3; j++ )
        {
            fprintf( stdout, "%f ", v[ j ] );
        }

        fprintf( stdout, "\n" );
}

/* Recolher os parametros das transformacoes */

void anguloRotacao( float *ang )
{
    fprintf( stdout, "\n\n Angulo de Rotacao em GRAUS : " );

    fscanf( stdin, "%f", ang );

    fprintf( stdout, "\n" );

}

void getUserAlarm(){
    int h, m;
    fprintf(stdout, "Hora: (Formato HH:MM)\n");
    fscanf(stdin, "%d:%d", &h, &m);
    setAlarm(h, m);
}

void getNewFusoHorario()
{
    int h, op, relogio;
    do{
        fprintf(stdout, "Fuso Horario:\n1) Lisboa / Londres\n2) Madrid / Paris / Berlin\n");
        fprintf(stdout, "3) Kiev / Tallinn\n4) Moscovo / Kuwait\n5) Pequim\n6) Toquio\n7) Sidney\n");
        fprintf(stdout, "8) Buenos Aires\n9) Nova Iorque\nEscolher opcao:");
    fscanf(stdin, "%d", &op);
    }while (op > 9 || op < 1);

    switch(op)
    {
        case 1:
            h = 0;
            break;
        case 2:
            h = 1;
            break;
        case 3:
            h = 2;
            break;
        case 4:
            h = 3;
            break;
        case 5:
            h = 8;
            break;
        case 6:
            h = 9;
            break;
        case 7:
            h = 10;
            break;
        case 8:
            h = -3;
            break;
        case 9:
            h = -5;
            break;
        default:
            h = 0;
    }
    fprintf(stdout, "Fuso Horario: %d Hora(s)\n", h);
    do{
        fprintf(stdout, "Relogio a alterar (0 --> Esquerda; 1 --> Direita): ");
        fscanf(stdin, "%d", &relogio);
    }while(relogio != 0 && relogio != 1);

    setFusoHorario(h, relogio);
}

void getTimerOption()
{
    int op;
    int relogio;
    do{
        fprintf(stdout, "Relogio a alterar (0 --> Esquerda; 1 --> Direita): ");
        fscanf(stdin, "%d", &relogio);
    }while(relogio != 1 && relogio != 0);
    do{
        fprintf(stdout, "Timer (1 --> start and press s to stop): ");
        fscanf(stdin, "%d", &op);
    }while(op != 1);
    setTimer(relogio, 1);

}

void printAlarm(int difh, int difm){
    fprintf(stdout, "Time Missing -> %d:%d\n", difh, difm);
}



void parametrosTransl3D( float *dx, float *dy, float *dz )
{
    fprintf( stdout, "\n\n Translacao ( dx dy dz ) : " );

    fscanf( stdin, "%f%f%f", dx, dy, dz );

    fprintf( stdout, "\n" );
}


void parametrosVarEscala3D( float *sx, float *sy, float *sz )
{
    fprintf( stdout, "\n\n Variacao de Escala ( sx xy sz ) : " );

    fscanf( stdin, "%f%f%f", sx, sy, sz );

    fprintf( stdout, "\n" );
}


void nomeFicheiro( char *nome )
{
    fprintf( stdout, "Escreva o nome do ficheiro, incluindo a extensao:\n" );

    gets( nome );
}






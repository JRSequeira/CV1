/*
 * angleRotation.h
 *
 * Ficheiro cabecalho do modulo de rotacao dos ponteiros
 */


#ifndef _angleRotation_h
#define _angleRotation_h


/* ----------------------------------------------------------------------- */
typedef struct{
    int h;
    int m;
}Alarm;

void setTimer(int i, int res);

float hour(int h, int i);

float minute(int m);

float second(int s);

int getAlarmHour();

int getAlarmMinute();

void setAlarm(int h, int m);

int getFusoHorario();

void setFusoHorario(int h, int relogio);

void Dif(int h1, int m1, int h2, int m2, int* rh, int* rm);

void resetAlarm();


/* ----------------------------------------------------------------------- */


#endif
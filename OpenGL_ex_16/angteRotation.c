#include "angteRotation.h"
#include "stdio.h"



static Alarm alarm = {-1, -1};
static int fusoHorario = 0;

float second(int s)
{
    return  6*s;

}

float minute(int m)
{
    return 6 * m;
}

float hour(int h)
{
    float res = 30 * ((h + fusoHorario)%12);
    return res;
}


int getAlarmHour(){
    return alarm.h;
}

int getAlarmMinute(){
    return alarm.m;
}

void setAlarm(int h, int m){
    alarm.h = h;
    alarm.m = m;
}

int getFusoHorario()
{
    return fusoHorario;
}

void setFusoHorario(int h)
{
    fusoHorario = h;
}


void Dif(int h1, int m1, int h2, int m2, int* rh, int* rm){
    if(h2 > h1){
        --h1;
        m1+=60;
    }
    *rm = m1-m2;
    *rh = h1-h2;
   

}

void resetAlarm(){
    alarm.h = -1;
    alarm.m = -1;
}
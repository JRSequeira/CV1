#include "angteRotation.h"
#include "stdio.h"



static Alarm alarm = {-1, -1};
static int fusoHorario[2] = {0, 0};

float second(int s)
{
    return  6*s;

}

float minute(int m)
{
    return 6 * m;
}

float hour(int h, int i)
{
    float res = 0;
    if (i == 0)
    {
        res = 30 * ((h + fusoHorario[0])%12);
    }
    else if (i == 1)
    {
        res = 30 * (h%12);
    }
    else if (i == 2)
    {
        res = 30 * ((h + fusoHorario[1])%12);
    }
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

int getFusoHorario(int i)
{
    return fusoHorario[i];
}

void setFusoHorario(int h, int relogio)
{
    fusoHorario[relogio] = h;
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
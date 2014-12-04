#include "angleRotation.h"
#include "stdio.h"

static Alarm alarm = {-1, -1};
static int fusoHorario[2] = {0, 0};
static int timer[3] = {0, 0, 0};
static int timerOk[3] = {0, 0, 0};
static int timerValues[3] = {-1, -1, -1};

void setTimer(int i, int res)
{
    if (i == 1)
    {
        i = 2;
        fprintf(stdout, "Fuso Horario: Hora(s)\n");
    }

        fprintf(stdout, "Fuso Horario: Hora(s)\n");
    fprintf(stdout, " %d Hora(s)\n", i);
    timer[i] = res;
    int j = 0;
    for (j = 0; j < 3; j++)
    {
        timerOk[j] = 0;
        timerValues[j] = 0;
    }
}

float second(int s, int i)
{
    if ((timer[i] == 1))
    {
        if (timerOk[0] == 0)
        {
            timerOk[0] = 1;
            timerValues[0] = s;
            return 0;
        }
        else if (s == 0)
        {
            return timerValues[0];
        }

        else if (s > timerValues[0])
        {
            return 6*(s-timerValues[0]);
        }
        else if (s < timerValues[0])
        {
            return 6*(s+timerValues[0]);
        }
        return 0;
        
    }
    return  6*s;

}

float minute(int m, int i)
{
    if((timer[i] == 1))
    {
        if (timerOk[1] == 0)
        {
            timerOk[1] = 1;
            timerValues[1] = m;
            return 0;
        }
        else if (m == 0)
        {
            return timerValues[1];
        }
        else if (m > timerValues[1])
        {
            return 6*(m-timerValues[1]);
        }
        else if (m < timerValues[1])
        {
            return 6*(m+timerValues[1]);
        }
        return 0;
    }
    return 6 * m;
}

float hour(int h, int i)
{
    float res = 0;
    if((timer[i] == 1))
    {
        if (timerOk[2] == 0)
        {
            timerOk[2] = 1;
            timerValues[2] = h;
            return 0;
        }
        else if (h == 0)
        {
            return timerValues[2];
        }
        else if (h > timerValues[2])
        {
            return 6*(h-timerValues[2]);
        }
        else if (h < timerValues[2])
        {
            return 6*(h+timerValues[2]);
        }
        return 0;
    }
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
    if (relogio == 1)
    {
        relogio = 2;
    }
    timer[relogio] = 0;
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
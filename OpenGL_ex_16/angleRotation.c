#include "angleRotation.h"
#include "stdio.h"

/*
Variaveis auxiliares responsaveis por controlar as varias funcionalidades.
*/

static Alarm alarm = {-1, -1};
static int fusoHorario[2] = {0, 0};
static int timer[3] = {0, 0, 0};
static int timerOk[3] = {0, 0, 0};
static int timerValues[3] = {-1, -1, -1};

/*
Funcao que permite activar ou desactivar o timer (recorrendo ao res)
de um determinado relogio (recorrendo ao i).
*/

void setTimer(int i, int res)
{
    int j = 0;
    if (i == 1)
    {
        timer[2] = res;
    }
    else
    {
        timer[0] = res;
    }
    for (j = 0; j < 3; j++)
    {
        timerOk[j] = 0;
        timerValues[j] = 0;
    }
}

/*
Funcao que calcula qual o angulo de rotacao do ponteiro dos 
segundos para um determinado reĺogio recorrendo ao valor dos 
segundos ou do timer.
*/

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

/*
Funcao que calcula qual o angulo de rotacao do ponteiro dos 
minutos para um determinado reĺogio recorrendo ao valor dos 
minutos ou do timer.
*/

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

/*
Funcao que calcula qual o angulo de rotacao do ponteiro das 
horas para um determinado reĺogio recorrendo ao valor das 
horas ou do timer e considerando o fuso horario activo
*/

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

/*
Funcao responsavel por retornar a hora em que o alarme esta definido
*/

int getAlarmHour(){
    return alarm.h;
}

/*
Funcao responsavel por retornar os minutos em que o alarme esta definido
*/

int getAlarmMinute(){
    return alarm.m;
}

/*
Funcao responsavel por inicializar o alarme
*/

void setAlarm(int h, int m){
    alarm.h = h;
    alarm.m = m;
}

/*
Funcao responsavel por retornaro fuso horario definido para 
um determinado relogio
*/

int getFusoHorario(int i)
{
    return fusoHorario[i];
}

/*
Funcao responsavel por inicializar o fuso horario num
determinado relogio
*/

void setFusoHorario(int h, int relogio)
{
    fusoHorario[relogio] = h;
    if (relogio == 1)
    {
        relogio = 2;
    }
    timer[relogio] = 0;
}

/*
Funcao responsavel por calcular a diferenca entre a hora
actual e a hora que o alrme esta definido
*/

void Dif(int h1, int m1, int h2, int m2, int* rh, int* rm){
    if(h2 > h1){
        --h1;
        m1+=60;
    }
    *rm = m1-m2;
    *rh = h1-h2;
   
}

/*
Funcao responsavel por desligar o alarme
*/

void resetAlarm(){
    alarm.h = -1;
    alarm.m = -1;
}
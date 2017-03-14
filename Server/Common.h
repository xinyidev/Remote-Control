#pragma once
#include <windows.h>
#define SYSINFO  0x01

typedef struct tagMSGINFO //传输消息结构体
{
    int Msg_id;
    BYTE context[1024*5];
}MSGINFO_S;

typedef struct tagSYSTEMINFO
{
    int os;
    bool Cam; //摄像头
    double ver;
}SYSTEMINFO_S;
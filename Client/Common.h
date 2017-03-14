#pragma once
#include "stdafx.h"
#define SYSINFO  0x01

#define ID_ONLINE WM_USER+1
#define ID_OFFLINE WM_USER+2

typedef struct tagMSGINFO //传输消息结构体
{
    int Msg_id;
    BYTE context[1024*5];
}MSGINFO;

typedef struct tagSYSTEMINFO //上线信息
{
    int os;
    bool Cam; //摄像头
    double ver;
}SYSTEMINFO;


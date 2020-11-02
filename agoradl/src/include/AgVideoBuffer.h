#pragma once
#include "types.h"
#define VIDEO_BUF_SIZE 4*4*1920*1080//
class CAgVideoBuffer
{
public:
    CAgVideoBuffer();
    ~CAgVideoBuffer();


    bool writeBuffer(BYTE* buffer, int w, int h);
    bool readBuffer(BYTE* buffer, int& ts, int &w, int &h);

    static CAgVideoBuffer* GetInstance();
private:
    static BYTE videoBuffer[VIDEO_BUF_SIZE];
    int                 timestamp;
    int                 m_w;
    int                 m_h;
};


#include "AgVideoBuffer.h"
#include <mutex>
#include <chrono>

std::mutex buf_mutex;
BYTE CAgVideoBuffer::videoBuffer[VIDEO_BUF_SIZE] = { 0 };

CAgVideoBuffer* CAgVideoBuffer::GetInstance()
{
    static CAgVideoBuffer agVideoBuffer;
    return &agVideoBuffer;
}

CAgVideoBuffer::CAgVideoBuffer()
{

}

CAgVideoBuffer::~CAgVideoBuffer()
{

}

bool CAgVideoBuffer::writeBuffer(BYTE* buffer, int w, int h)
{
    std::lock_guard<std::mutex> buf_lock(buf_mutex);
 
	memcpy(videoBuffer, buffer, w*h*1.5);
    timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
    m_w = w;
    m_h = h;
    return true;
}
bool CAgVideoBuffer::readBuffer(BYTE* buffer, int& ts, int &w, int &h)
{
    std::lock_guard<std::mutex> buf_lock(buf_mutex);
    memcpy(buffer, videoBuffer, m_w*m_h*1.5);
    ts = timestamp;
    w = m_w;
    h = m_h;
    return true;
}
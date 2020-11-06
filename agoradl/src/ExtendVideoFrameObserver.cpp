#include "ExtendVideoFrameObserver.h"

#include <iostream>

VIDEO_BUFFER		buffer;
CExtendVideoFrameObserver::CExtendVideoFrameObserver()
{
	m_lpImageBuffer = new BYTE[VIDEO_BUF_SIZE];
}


CExtendVideoFrameObserver::~CExtendVideoFrameObserver()
{
    if (m_lpImageBuffer) {
        delete[] m_lpImageBuffer;
        m_lpImageBuffer = nullptr;
    }
}

bool CExtendVideoFrameObserver::onCaptureVideoFrame(VideoFrame& videoFrame)
{
	memset(videoFrame.yBuffer, 0, videoFrame.height*videoFrame.width);
	memset(videoFrame.uBuffer, 128, videoFrame.height*videoFrame.width/4);
	memset(videoFrame.vBuffer, 128, videoFrame.height*videoFrame.width/4);
    if (CAgVideoBuffer::GetInstance()->readBuffer(m_lpImageBuffer, buffer.timestamp, videoFrame.width, videoFrame.height)) {
        int bufSize = videoFrame.width*videoFrame.height * 1.5;
        memcpy_s(buffer.m_lpImageBuffer, bufSize, m_lpImageBuffer, bufSize);
    }
    else
        std::cout<<"readBuffer failed"<<std::endl;

	/*BOOL bSuccess = CVideoPackageQueue::GetInstance()->PopVideoPackage(m_lpImageBuffer, &nBufferSize);
	if (!bSuccess)
		return false;*/

	memcpy_s(videoFrame.yBuffer, videoFrame.height*videoFrame.width, buffer.m_lpImageBuffer, videoFrame.height*videoFrame.width);
	videoFrame.yStride = videoFrame.width;

	memcpy_s(videoFrame.uBuffer, videoFrame.height*videoFrame.width / 4, buffer.m_lpImageBuffer + videoFrame.height*videoFrame.width, 
		videoFrame.height*videoFrame.width / 4);
	videoFrame.uStride = videoFrame.width / 2;

	memcpy_s(videoFrame.vBuffer, videoFrame.height*videoFrame.width / 4, buffer.m_lpImageBuffer + 5 * videoFrame.height*videoFrame.width / 4, 
		videoFrame.height*videoFrame.width / 4);
	videoFrame.vStride = videoFrame.width / 2;

	videoFrame.type = agora::media::base::VIDEO_PIXEL_I420;
	videoFrame.rotation = 0;

	return true;
}

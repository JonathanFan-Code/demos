#pragma once
#include "../agora/include/IAgoraMediaEngine.h"
#include "types.h"
//#include "VideoPackageQueue.h"
#include "AgVideoBuffer.h"
typedef struct _VIDEO_BUFFER {
    BYTE m_lpImageBuffer[VIDEO_BUF_SIZE];
    int  timestamp;
}VIDEO_BUFFER, *PVIDEO_BUFFER;
class CExtendVideoFrameObserver :
	public agora::media::IVideoFrameObserver
{
public:
	CExtendVideoFrameObserver();
	~CExtendVideoFrameObserver();

	virtual bool onCaptureVideoFrame(VideoFrame& videoFrame);
    virtual VIDEO_FRAME_TYPE getVideoFormatPreference() { return FRAME_TYPE_YUV420; }
	virtual bool onRenderVideoFrame(unsigned int uid, VideoFrame& videoFrame);

private:
    BYTE*				m_lpImageBuffer;
};


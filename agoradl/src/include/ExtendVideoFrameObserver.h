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
	virtual agora::media::base::VIDEO_PIXEL_FORMAT getVideoPixelFormatPreference() { return agora::media::base::VIDEO_PIXEL_I420; };
	virtual bool onRenderVideoFrame(agora::rtc::uid_t uid, agora::rtc::conn_id_t connectionId, VideoFrame& videoFrame) { return true; };
	virtual bool onScreenCaptureVideoFrame(VideoFrame& videoFrame) { return true; };

private:
    BYTE*				m_lpImageBuffer;
};


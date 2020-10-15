#pragma once

#include "../zego/include/ZegoExpressSDK.h"
#include "./ZegoCustomVideoSourceContext.h"
using namespace ZEGO::EXPRESS;


class CZegoEventHandler : public IZegoEventHandler
{
public:
	CZegoEventHandler(void);
	~CZegoEventHandler(void);

	void SetMsgReceiver(HWND hWnd = NULL);
	HWND GetMsgReceiver() { return m_hMainWnd; };

	virtual void onDebugError(int errorCode, const std::string& funcName, const std::string& info)override;
	virtual void onEngineStateUpdate(ZegoEngineState state);
	virtual void onRoomStateUpdate(const std::string& roomID, ZegoRoomState state, int errorCode, const std::string& extendedData);
	virtual void onRoomUserUpdate(const std::string& roomID, ZegoUpdateType updateType, const std::vector<ZegoUser>& userList);
	virtual void onRoomStreamUpdate(const std::string &roomID, ZegoUpdateType updateType, const std::vector<ZegoStream> &streamList);
	virtual void onPublisherVideoSizeChanged(int, int, ZegoPublishChannel);
	virtual void onPlayerVideoSizeChanged(const std::string &, int width, int height);
	virtual void onPublisherQualityUpdate(const std::string &streamID, const ZegoPublishStreamQuality& quality);
	virtual void onPlayerQualityUpdate(const std::string &streamID, const ZegoPlayStreamQuality& quality);

private:
	HWND  m_hMainWnd;
};


class CZegoCustomVideoRenderer : public IZegoCustomVideoRenderHandler {
public:

	void onCapturedVideoFrameRawData(unsigned char ** data, unsigned int* dataLength, ZegoVideoFrameParam param, ZegoVideoFlipMode flipMode, ZegoPublishChannel channel) override {
			//dataInterface->onCapturedVideoFrameRawData(data, dataLength, param, flipMode);
		int i = 0;
	}
	void onRemoteVideoFrameRawData(unsigned char ** data, unsigned int* dataLength, ZegoVideoFrameParam param, const std::string& streamID) override {
		//dataInterface->onRemoteVideoFrameRawData(data, dataLength, param, streamID);
		int i = 0;
	}

	void onRemoteVideoFrameEncodedData(const unsigned char* data, unsigned int dataLength, ZegoVideoEncodedFrameParam param, unsigned long long referenceTimeMillisecond, const std::string& streamID) override {
		//dataInterface->onRemoteVideoFrameEncodedData(data, dataLength, param, referenceTimeMillisecond, streamID);
		int i = 0;
	}
};

class CustomVideoCapturer: public IZegoCustomVideoCaptureHandler, public ZegoCustomVideoSourceContext{

public:
    void onStart(ZegoPublishChannel channel) override;
    void onStop(ZegoPublishChannel channel) override;

private:
    void collectVideoFrameAndSendToEngine();

private:
    std::atomic<bool> mVideoCaptureRunning = {false};
    std::thread mVideoCaptureThread;
};


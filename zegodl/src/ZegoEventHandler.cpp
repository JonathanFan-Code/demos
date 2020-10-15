#include "ZegoEventHandler.h"
#include "ZegoObject.h"
#include <iostream>

CZegoEventHandler::CZegoEventHandler(void)
{
}

CZegoEventHandler::~CZegoEventHandler(void)
{
}

void CZegoEventHandler::SetMsgReceiver(HWND hWnd)
{
	m_hMainWnd = hWnd;
}


void CZegoEventHandler::onDebugError(int errorCode, const std::string& funcName, const std::string& info)
{
}

void CZegoEventHandler::onEngineStateUpdate(ZegoEngineState state)
{

}

void CZegoEventHandler::onRoomStateUpdate(const std::string& roomID, ZegoRoomState state, int errorCode, const std::string& extendedData)
{
	std::string sroomID = roomID;
}

void CZegoEventHandler::onRoomUserUpdate(const std::string& roomID, ZegoUpdateType updateType, const std::vector<ZegoUser>& userList)
{
	std::string sroomID = roomID;
}

void CZegoEventHandler::onRoomStreamUpdate(const std::string &roomID, ZegoUpdateType updateType, const std::vector<ZegoStream> &streamList)
{
	CZegoObject::GetZegoObject()->onRoomStreamUpdate(roomID, updateType, streamList);
}

void CZegoEventHandler::onPublisherVideoSizeChanged(int width, int height, ZegoPublishChannel channel)
{
	std::cout << "zego capture w:" << width << " h:" << height << " channel" << channel << std::endl;
}

void CZegoEventHandler::onPlayerVideoSizeChanged(const std::string & streamID, int width, int height)
{
	std::cout << "zego play streamID:" << streamID <<" w:"<< width << " h:" << height << std::endl;
}

void CZegoEventHandler::onPublisherQualityUpdate(const std::string &streamID, const ZegoPublishStreamQuality& quality)
{
	std::cout << "zego Publisher Quality streamID:" << streamID << " vcap fps:" << quality.videoCaptureFPS //<< std::endl
		<< " venc fps:" << quality.videoEncodeFPS << " vsend fps:" << quality.videoSendFPS << " vsend kbps:" << quality.videoKBPS //<< std::endl
		<< " acap fps:" << quality.audioCaptureFPS << " asend fps:" << quality.audioSendFPS << " asend kbps:" << quality.audioKBPS// << std::endl
		<< " rtt(ms):" << quality.rtt << " packetLostRate fps:" << quality.packetLostRate << " quality level:" << quality.level //<< std::endl
		<< " isHardwareEncode:" << quality.isHardwareEncode << " totalSendBytes:" << quality.totalSendBytes << " audioSendBytes:" << quality.audioSendBytes
		<< " videoSendBytes:" << quality.videoSendBytes << std::endl;

}

void CZegoEventHandler::onPlayerQualityUpdate(const std::string &streamID, const ZegoPlayStreamQuality& quality)
{
	std::cout << "zego Play Quality streamID:" << streamID << " vRecv fps:" << quality.videoRecvFPS //<< std::endl
		<< " vdec fps:" << quality.videoDecodeFPS << " vRend fps:" << quality.videoRenderFPS << " v kbps:" << quality.videoKBPS //<< std::endl
		<< " aRecv fps:" << quality.audioRecvFPS << " aDec fps:" << quality.audioDecodeFPS << " aRend fps:" << quality.audioRenderFPS 
		<<" aKBPS:"<< quality.audioKBPS //<< std::endl
		<< " rtt(ms):" << quality.rtt << " packetLostRate fps:" << quality.packetLostRate << " peerToPeerDelay:" 
		<< quality.peerToPeerDelay << " peerToPeerPacketLostRate:" << quality.peerToPeerPacketLostRate << " quality level:" << quality.level //<< std::endl
		<< " delay:" << quality.delay << " isHardwareDecode:" << quality.isHardwareDecode
		<< " totalRecvBytes:" << quality.totalRecvBytes << " audioRecvBytes:" << quality.audioRecvBytes
		<< " videoRecvBytes:" << quality.videoRecvBytes << std::endl;
}

void CustomVideoCapturer::onStart(ZegoPublishChannel channel)
{
    if (!mVideoCaptureRunning)
    {
        mVideoCaptureRunning = true;
        mVideoCaptureThread = std::thread(std::bind(&CustomVideoCapturer::collectVideoFrameAndSendToEngine, this));
    }
}

void CustomVideoCapturer::onStop(ZegoPublishChannel channel)
{ 
    if (mVideoCaptureRunning)
    {
        mVideoCaptureRunning = false;
        mVideoCaptureThread.join();
    }
}

void CustomVideoCapturer::collectVideoFrameAndSendToEngine()
{
    while (true)
    {
        if(!mVideoCaptureRunning){
            break;
        }

        std::shared_ptr<ZegoCustomVideoFrame> videoFrame;
        this->getVideoFrame(videoFrame);
        if (videoFrame)
        {
            CZegoObject::GetZegoObject()->getEngine()->sendCustomVideoCaptureRawData(videoFrame->data.get(), videoFrame->dataLength, videoFrame->param, videoFrame->referenceTimeMillsecond);
        }

		std::shared_ptr<ZegoCustomAudioFrame> audioFrame;
        this->getAudioFrame(audioFrame);
        if (audioFrame)
        {
            CZegoObject::GetZegoObject()->getEngine()->sendCustomAudioCapturePCMData(audioFrame->data.get(), audioFrame->dataLength, 
			audioFrame->param);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}
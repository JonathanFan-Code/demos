#pragma once
#include "../agora/include/IAgoraRtcEngine.h"
#include "../agora/include/IAgoraMediaEngine.h"
//#include "../agora/include/IAgoraRtcChannel.h"
#ifdef _M_IX86
#pragma comment(lib, "../agora/lib/agora_rtc_sdk.lib")
#elif defined _M_X64
#pragma comment(lib, "../agora/lib/x64/agora_rtc_sdk.lib")
#endif


#include "AGEngineEventHandler.h"
#include "ExtendVideoFrameObserver.h"
#include "ExtendAudioFrameObserver.h"


//#include "AgoraAudInputManager.h"
//#include "AgoraPlayoutManager.h"
//#include "AgoraCameraManager.h"
//#include "ExtendVideoFrameObserver.h"
#include <atlcoll.h>
//#include "AudioPlayPackageQueue.h"
#include <map>
#include <string>
#include <atomic>

using std::map;
using std::string;
// #define ENABLE_CODEC	1

using namespace agora::rtc;
using namespace agora::util;


using namespace agora::media;
using namespace agora::rtc;
using namespace agora;


using namespace agora::rtc;

extern std::atomic<bool> g_Logon;

class CAgoraObject
{
public:
	~CAgoraObject(void);

	void SetMsgHandlerWnd(AHANDLE hWnd);
	AHANDLE GetMsgHandlerWnd();

	BOOL JoinChannel(const char* lpChannelName, UINT nUID = 0, const char* lpToken = NULL);
	BOOL LeaveChannel();
	string GetChanelName();

	BOOL EnableVideo(BOOL bEnable = TRUE);
	BOOL IsVideoEnabled();

	BOOL setVideoEncoderConfig(const VideoEncoderConfiguration &config);

	BOOL MuteLocalAudio(BOOL bMuted = TRUE);
	BOOL IsLocalAudioMuted();

	BOOL MuteLocalVideo(BOOL bMuted = TRUE);
	BOOL IsLocalVideoMuted();

	static IRtcEngine *GetEngine();

	static string GetSDKVersion();

protected:
	CAgoraObject(void);

private:
	DWORD	m_dwEngineFlag;
	static  CAgoraObject	*m_lpAgoraObject;
	static	IRtcEngine		*m_lpAgoraEngine;

	string		m_strChannelName;
	BOOL		m_bVideoEnable;

	BOOL		m_bLocalAudioMuted;
	BOOL		m_bLocalVideoMuted;

	void*       m_localView = nullptr;

public:
	static CAgoraObject *GetAgoraObject(char* lpVendorKey);
	static void CloseAgoraObject();

	static CAGEngineEventHandler m_EngineEventHandler;
    static CExtendVideoFrameObserver m_CExtendVideoFrameObserver;
	static CExtendAudioFrameObserver m_CExtendAudioFrameObserver;
};
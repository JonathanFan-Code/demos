#include "AgoraObject.h"
#include "AGExtInfoManager.h"
//#include "../agora/include/IAgoraRtcChannel.h"

//#include "Base64.h"

#include <stdlib.h>
#include <json/json.h>

#include <stdio.h>


CAgoraObject *CAgoraObject::m_lpAgoraObject = NULL;
IRtcEngine *CAgoraObject::m_lpAgoraEngine = NULL;
CAGEngineEventHandler CAgoraObject::m_EngineEventHandler;
CExtendVideoFrameObserver CAgoraObject::m_CExtendVideoFrameObserver;
CExtendAudioFrameObserver CAgoraObject::m_CExtendAudioFrameObserver;

std::atomic<bool> g_Logon = true;


CAgoraObject::CAgoraObject(void)
	: m_dwEngineFlag(0)
	, m_bVideoEnable(FALSE)
	, m_bLocalAudioMuted(FALSE)
{
	m_strChannelName.clear();
	m_bLocalVideoMuted = FALSE;
}

CAgoraObject::~CAgoraObject(void)
{
}

/**
   gets current SDK version number string
*/
string CAgoraObject::GetSDKVersion()
{
	int nBuildNumber = 0;
	const char *lpszEngineVer = getAgoraRtcEngineVersion(&nBuildNumber);

	string strEngineVer(lpszEngineVer);

//#ifdef UNICODE
//	::MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, lpszEngineVer, -1, strEngineVer.GetBuffer(256), 256);
//	strEngineVer.ReleaseBuffer();
//#endif

	return strEngineVer;
}

/**
	gets the Agora Engine instance
*/
IRtcEngine *CAgoraObject::GetEngine()
{
	if (m_lpAgoraEngine == NULL)
		m_lpAgoraEngine = (IRtcEngine *)createAgoraRtcEngine();

	return m_lpAgoraEngine;
}

/**
	create or return existing AgoraObject
*/
CAgoraObject *CAgoraObject::GetAgoraObject(char* lpAppId)
{
	if (m_lpAgoraObject == NULL)
		m_lpAgoraObject = new CAgoraObject();

	if (m_lpAgoraEngine == NULL)
		m_lpAgoraEngine = (IRtcEngine *)createAgoraRtcEngine();

	if (lpAppId == NULL)
		return m_lpAgoraObject;

	RtcEngineContext ctx;

	ctx.eventHandler = &m_EngineEventHandler;
#if 0//UNICODE
	char szAppId[128];

	::WideCharToMultiByte(CP_ACP, 0, lpAppId, -1, szAppId, 128, NULL, NULL);
	ctx.appId = szAppId;
#else
	ctx.appId = lpAppId;
#endif

	m_lpAgoraEngine->initialize(ctx);

	return m_lpAgoraObject;
}

/**
	clean up the AgoraObject
*/
void CAgoraObject::CloseAgoraObject()
{
	if (m_lpAgoraEngine != NULL)
		m_lpAgoraEngine->release();

	if (m_lpAgoraObject != NULL)
		delete m_lpAgoraObject;

	m_lpAgoraEngine = NULL;
	m_lpAgoraObject = NULL;
}

/**
  Setting Message Handler
Parameters:
	@param hWnd     A handle to the handler
 */
void CAgoraObject::SetMsgHandlerWnd(AHANDLE hWnd)
{
	m_EngineEventHandler.SetMsgReceiver((HWND)hWnd);
}

/**
	retrieve the handle of the message handler
*/
AHANDLE CAgoraObject::GetMsgHandlerWnd()
{
	return (AHANDLE)m_EngineEventHandler.GetMsgReceiver();
}

/**
   Join a channel for streaming or communication.
Parameters:
@param lpChannelName    name of the channel to join
@param uUID     User ID
@param lpToken  token key
*/
BOOL CAgoraObject::JoinChannel(const char* lpChannelName, UINT nUID, const char* lpToken)
{

	VideoCanvas canvas;
	canvas.renderMode = agora::media::base::RENDER_MODE_FIT;
	CAGExtInfoManager *lpExtInfoManager = CAGExtInfoManager::GetAGExtInfoManager();
	canvas.uid = nUID;
	
	canvas.view = lpExtInfoManager->GetFirstView();

	m_localView = canvas.view;
	int nRet = GetEngine()->setupLocalVideo(canvas);


	if (!lpToken || 0 == _tcslen(lpToken))
		nRet = m_lpAgoraEngine->joinChannel(NULL, lpChannelName, NULL, nUID);
	else
		nRet = m_lpAgoraEngine->joinChannel(lpToken, lpChannelName, NULL, nUID);

	if (nRet == 0)
		m_strChannelName = (char*)lpChannelName;

	m_lpAgoraEngine->startPreview();
	return nRet == 0 ? TRUE : FALSE;
}

/**
	Leave the channel
*/
BOOL CAgoraObject::LeaveChannel()
{
	CAGExtInfoManager::GetAGExtInfoManager()->FreeView((AHANDLE)m_localView);
	m_lpAgoraEngine->stopPreview();
	int nRet = m_lpAgoraEngine->leaveChannel();

	return nRet == 0 ? TRUE : FALSE;
}

/**
	get current channel name
*/
string CAgoraObject::GetChanelName()
{
	return m_strChannelName;
}

/**
	turn video on/off
 Parameters:
	@param bEnable true if turn on else turn off
*/
BOOL CAgoraObject::EnableVideo(BOOL bEnable)
{
	int nRet = 0;

	if (bEnable)
	{
		nRet = m_lpAgoraEngine->enableVideo();
	}	
	else
		nRet = m_lpAgoraEngine->disableVideo();

	if (nRet == 0)
		m_bVideoEnable = bEnable;

	return nRet == 0 ? TRUE : FALSE;
}

/**
	check if video enabled
*/
BOOL CAgoraObject::IsVideoEnabled()
{
	return m_bVideoEnable;
}

BOOL CAgoraObject::setVideoEncoderConfig(const VideoEncoderConfiguration &config)
{
	int nRet = 0;

	nRet = m_lpAgoraEngine->setVideoEncoderConfiguration(config);

	return nRet == 0 ? TRUE : FALSE;
}
/**
	mute local audio on/off
 Parameters:
	@param bMuted true if muted else not muted
*/
BOOL CAgoraObject::MuteLocalAudio(BOOL bMuted)
{
	if (m_lpAgoraEngine == NULL)
		return false;

	agora::base::AParameter msp(GetEngine());
	auto ret = 0;
	if (bMuted == TRUE)
	{
		ret = msp->setParameters("{\"rtc.audio.mute_me\": \"true\",\"che.audio.mute_me\":\"true\"}");
	}
	else 
	{
		ret = msp->setParameters("{\"rtc.audio.mute_me\": \"false\",\"che.audio.mute_me\":\"false\"}");
	}
	if(ret == 0)
		m_bLocalAudioMuted = bMuted;

	return ret == 0 ? TRUE : FALSE;
}

/**
	check if local audio is muted
*/
BOOL CAgoraObject::IsLocalAudioMuted()
{
	return m_bLocalAudioMuted;
}

/**
	mute local video on/off
 Parameters:
	@param bMuted true if muted else not muted
*/
BOOL CAgoraObject::MuteLocalVideo(BOOL bMuted)
{
	if (m_lpAgoraEngine == NULL)
		return false;

	agora::base::AParameter msp(GetEngine());
	auto ret = 0;
	if (bMuted == TRUE)
	{
		ret = msp->setParameters("{\"rtc.video.mute_me\": \"true\",\"che.video.local.send\":\"true\"}");
	}
	else
	{
		ret = msp->setParameters("{\"rtc.video.mute_me\": \"false\",\"che.video.local.send\":\"false\"}");
	}

	if (ret == 0)
		m_bLocalVideoMuted = bMuted;

	return ret == 0 ? TRUE : FALSE;
}
/**
	check if local video is muted
*/
BOOL CAgoraObject::IsLocalVideoMuted()
{
	return m_bLocalVideoMuted;
}		
// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "types.h"
#ifdef ZEGODL_EXPORTS	
#define ZEGODL_API __declspec(dllexport)  
#else
#define ZEGODL_API __declspec(dllimport)  
#endif

#include <iostream>
#include "ZegoObject.h"
#include "AGExtInfoManager.h"
using namespace std;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
	{
		/*
		// AppID 和 AppSign 由 ZEGO 分配给各 App；其中，为了安全考虑，建议将 AppSign 存储在 App 的业务后台，需要使用时从后台获取
		unsigned int appID = 928464678;
		std::string appSign = "2a485d1d1fe964eb7255d3c65ab1131fc8ad374a12231a1c7566827912096770";

		// 创建引擎实例
		g_lpZegoEngine = ZegoExpressSDK::createEngine(appID, appSign, true, ZEGO_SCENARIO_GENERAL, nullptr);*/
		break;
	}
    case DLL_THREAD_ATTACH:break;
    case DLL_THREAD_DETACH:break;
    case DLL_PROCESS_DETACH:
	{/*
		if (g_lpZegoEngine)
		{
			ZegoExpressSDK::destroyEngine(g_lpZegoEngine);
			g_lpZegoEngine = nullptr;
		}*/
		break;
	}
        
    }
    return TRUE;
}


extern "C" void ZEGODL_API HelloWorld()
{
	cout << "hello world" << endl;
}

extern "C" void ZEGODL_API enableCustomVideoCapture()
{
	cout << "enableCustomVideoCapture" << endl;
	CZegoObject::GetZegoObject()->enableCustomVideoCapture();
}

extern "C" void ZEGODL_API enableCustomAudioIO()
{
	cout << "enableCustomAudioIO" << endl;
	CZegoObject::GetZegoObject()->enableCustomAudioIO();
}


extern "C" void ZEGODL_API startCapMedia(LPVOID lpExtInfo)
{
	cout << "startCapMedia:" << lpExtInfo << endl;
	CZegoObject::GetZegoObject()->startCapMedia((char*)lpExtInfo);
}

extern "C" void ZEGODL_API stopPreview()
{
	cout << "stopPreview:" << endl;
	CZegoObject::GetZegoObject()->getEngine()->stopPreview(ZEGO::EXPRESS::ZEGO_PUBLISH_CHANNEL_MAIN);
}

extern "C" void ZEGODL_API stopPlayingStream()
{
	cout << "stopPlayingStream:" << endl;
	CZegoObject::GetZegoObject()->stopPlayingStream();
}

extern "C" void ZEGODL_API muteSpeaker()
{
	cout << "muteSpeaker:" << endl;
	CZegoObject::GetZegoObject()->getEngine()->muteSpeaker(true);
}

extern "C" void ZEGODL_API createEngine()
{
	cout << "createEngine" << endl;
	string out;
	CZegoObject::GetZegoObject()->createEngine(nullptr, out);
	cout << out << endl;

    cout <<"zego version:" << ZegoExpressSDK::getVersion() << endl;
}

extern "C" void ZEGODL_API destroyZegoEngine()
{
	CZegoObject::GetZegoObject()->destroyZegoEngine();
}

extern "C" void ZEGODL_API joinChannel(LPVOID lpExtInfo)
{
	string strOutput;
	cout << lpExtInfo << endl;
	CZegoObject::GetZegoObject()->joinChannel(lpExtInfo, strOutput);
	cout << strOutput << endl;
}

extern "C" void ZEGODL_API leaveChannel(LPVOID lpExtInfo)
{
	string strOutput;
	CZegoObject::GetZegoObject()->leaveChannel(lpExtInfo, strOutput);
	cout << strOutput << endl;
}

extern "C" void ZEGODL_API enableVideo(LPVOID lpExtInfo)
{
	string strOutput;
	CZegoObject::GetZegoObject()->enableVideo(lpExtInfo, strOutput);
	cout << strOutput << endl;
}

extern "C" void ZEGODL_API disableVideo()
{
	cout << "disableVideo" << endl;
	CZegoObject::GetZegoObject()->disableVideo();
}

extern "C" void ZEGODL_API disableAudio()
{
	cout << "disableAudio" << endl;
	CZegoObject::GetZegoObject()->disableAudio();
}

extern "C" void ZEGODL_API setVideoProfile(LPVOID lpExtInfo)
{
	string strOutput;
	CZegoObject::GetZegoObject()->setVideoProfile(lpExtInfo, strOutput);
	cout << strOutput << endl;
}

extern "C" void ZEGODL_API addView(LPVOID lpExtInfo, int i)
{
	string strOutput;
	CAGExtInfoManager::GetAGExtInfoManager()->AddView((HWND)lpExtInfo);
	cout << strOutput << endl;
}

extern "C" void ZEGODL_API enumerateRecordingDevices()
{
	auto adl = CZegoObject::GetZegoObject()->getEngine()->getAudioDeviceList(ZEGO_AUDIO_DEVICE_TYPE_INPUT);
	SetConsoleOutputCP(65001);
	cout << "Audio Recording Devices" << endl;
	for (auto i : adl)
	{
		cout << "deviceName:" << i.deviceName << " deviceId:" << i.deviceID << endl;
	}
}

extern "C" void ZEGODL_API setRecordingDevice(LPVOID lpExtInfo)
{
	CZegoObject::GetZegoObject()->getEngine()->useAudioDevice(ZEGO_AUDIO_DEVICE_TYPE_INPUT, (char*)lpExtInfo);
}

extern "C" void ZEGODL_API enumerateVideoDevices()
{
	auto vdl = CZegoObject::GetZegoObject()->getEngine()->getVideoDeviceList();
	SetConsoleOutputCP(65001);
	cout << "Video Recording Devices" << endl;
	for (auto i : vdl)
	{
		cout << "deviceName:" << i.deviceName << " deviceId:" << i.deviceID << endl;
	}
}

extern "C" void ZEGODL_API setVideoDevice(LPVOID lpExtInfo)
{
	CZegoObject::GetZegoObject()->getEngine()->useVideoDevice((char*)lpExtInfo);
}

extern "C" void ZEGODL_API enableHardwareEncoder()
{
	CZegoObject::GetZegoObject()->getEngine()->enableHardwareEncoder(true);
}

extern "C" void ZEGODL_API enableHardwareDecoder()
{
	CZegoObject::GetZegoObject()->getEngine()->enableHardwareDecoder(true);
}

extern "C" void ZEGODL_API disableAEC()
{
	CZegoObject::GetZegoObject()->getEngine()->enableAEC(false);
}

extern "C" void ZEGODL_API disableANS()
{
	CZegoObject::GetZegoObject()->getEngine()->enableANS(false);
}

extern "C" void ZEGODL_API disableeAGC()
{
	CZegoObject::GetZegoObject()->getEngine()->enableAGC(false);
}

extern "C" void ZEGODL_API muteMicrophone()
{
	CZegoObject::GetZegoObject()->getEngine()->muteMicrophone(true);
}

extern "C" void ZEGODL_API setAudioConfig(int profile, int codecid)
{
	ZegoAudioConfig audioConfig = ZegoAudioConfig((ZegoAudioConfigPreset)profile);
	audioConfig.codecID = (ZegoAudioCodecID)codecid;
	CZegoObject::GetZegoObject()->getEngine()->setAudioConfig(audioConfig);
}

extern "C" void ZEGODL_API logOff()
{
	g_Logon = false;
}




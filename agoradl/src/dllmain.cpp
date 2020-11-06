// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "types.h"
#include "AgVideoBuffer.h"

#ifdef AGORADL_EXPORTS	
#define AGORADL_API __declspec(dllexport)  
#else
#define AGORADL_API __declspec(dllimport)  
#endif

#include <iostream>
#include "AgoraObject.h"
#include "AGExtInfoManager.h"
#include "json/json.h"
using namespace std;

//#define APP_ID _T("aab8b8f5a8cd4469a63042fcfafe7063") 
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
	{
		break;
	}
    case DLL_THREAD_ATTACH:break;
    case DLL_THREAD_DETACH:break;
    case DLL_PROCESS_DETACH:
	{
		break;
	}
        
    }
    return TRUE;
}


extern "C" void AGORADL_API HelloWorld()
{
	cout << "hello world" << endl;
}

extern "C" void AGORADL_API createEngine(LPVOID lpExtInfo)
{
	cout << "createEngine" << endl;
	string out;
	CAgoraObject::GetAgoraObject((char*)lpExtInfo);
	cout << out << endl;
}

extern "C" void AGORADL_API destroyEngine()
{
	cout << "destroyEngine" << endl;
	string out;
	CAgoraObject::CloseAgoraObject();
	cout << out << endl;
}

bool ParseJson(LPVOID lpExtInfo, Json::Value &root)
{
	string rawJson((char*)lpExtInfo);
	Json::CharReaderBuilder builder;
	JSONCPP_STRING err;

	const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
	if (!reader->parse(rawJson.c_str(), rawJson.c_str() + rawJson.length(), &root,
		&err)) {
		return false;
	}
	return true;
}
extern "C" void AGORADL_API joinChannel(LPVOID lpExtInfo)
{
	Json::Value root;
	ParseJson(lpExtInfo, root);
	
	auto channelName = root["channelId"].asString();
	auto nUID = stoul(root["uid"].asString());
	CAgoraObject::GetAgoraObject(nullptr)->JoinChannel(channelName.c_str(), nUID, nullptr);
}

extern "C" void AGORADL_API leaveChannel()
{
	CAgoraObject::GetAgoraObject(nullptr)->LeaveChannel();
}

extern "C" void AGORADL_API enableVideo(LPVOID lpExtInfo)
{
	Json::Value root;
	ParseJson(lpExtInfo, root);

	auto enable = root["enable"].asString();
	auto bEnable = enable == "true";
	CAgoraObject::GetAgoraObject(nullptr)->EnableVideo(bEnable);

}

extern "C" void AGORADL_API enableAudio(LPVOID lpExtInfo)
{
	Json::Value root;
	ParseJson(lpExtInfo, root);

	auto enable = root["enable"].asString();
	auto bEnable = enable == "true";
	if (bEnable)
	{
		CAgoraObject::GetAgoraObject(nullptr)->GetEngine()->enableAudio();
	}
	else
	{
		CAgoraObject::GetAgoraObject(nullptr)->GetEngine()->disableAudio();
	}
	
}

extern "C" void AGORADL_API setParameters(LPVOID lpExtInfo)
{
	std::cout<<"setParameters:"<<(char*)lpExtInfo<<endl;
	agora::base::AParameter msp(CAgoraObject::GetAgoraObject(nullptr)->GetEngine());
	msp->setParameters((char*)lpExtInfo);
}


extern "C" void AGORADL_API setVideoProfile(LPVOID lpExtInfo)
{
	Json::Value root;
	ParseJson(lpExtInfo, root);

	VideoEncoderConfiguration vec;
	vec.dimensions.width = 360;
	vec.dimensions.height = 640;
	vec.frameRate = static_cast<FRAME_RATE>(15);
	vec.bitrate = 600;

	if (!root["resolution"].isNull()) {
		std::string sDimensions = root["resolution"].asString();
		string::size_type pos = sDimensions.find("*");
		if (pos < sDimensions.size())
		{
			std::string swidth = sDimensions.substr(0, pos);
			std::string sheight = sDimensions.substr(pos + 1, sDimensions.size() - 1);
			vec.dimensions.width = atoi(swidth.c_str());
			vec.dimensions.height = atoi(sheight.c_str());
		}
	}

	if (!root["bitrate"].isNull())
	{
		vec.bitrate = stoi(root["bitrate"].asString());
	}
	if (!root["fps"].isNull())
	{
		vec.frameRate = static_cast<FRAME_RATE>(stoi(root["fps"].asString()));
	}
	
	CAgoraObject::GetAgoraObject(nullptr)->setVideoEncoderConfig(vec);

}

extern "C" void AGORADL_API addView(LPVOID lpExtInfo)
{
	CAGExtInfoManager::GetAGExtInfoManager()->AddView((AHANDLE)lpExtInfo);
}

extern "C" void AGORADL_API setChannelProfile(LPVOID lpExtInfo)
{
	
	Json::Value root;
	ParseJson(lpExtInfo, root);

	CHANNEL_PROFILE_TYPE profile = CHANNEL_PROFILE_LIVE_BROADCASTING;
	if (!root["channelprofile"].isNull())
	{
		profile = (CHANNEL_PROFILE_TYPE)stoi(root["channelprofile"].asString());
	}
	
	CAgoraObject::GetAgoraObject(nullptr)->GetEngine()->setChannelProfile(profile);
}

extern "C" void AGORADL_API setClientRole(LPVOID lpExtInfo)
{
	Json::Value root;
	ParseJson(lpExtInfo, root);

	CLIENT_ROLE_TYPE role = CLIENT_ROLE_BROADCASTER;
	if (!root["clientrole"].isNull())
	{
		role = (CLIENT_ROLE_TYPE)stoi(root["clientrole"].asString());
	}

	CAgoraObject::GetAgoraObject(nullptr)->GetEngine()->setClientRole(role);
}

extern "C" void AGORADL_API enumerateRecordingDevices()
{
	IRtcEngine *rtcEngine = CAgoraObject::GetAgoraObject(nullptr)->GetEngine();
	AAudioDeviceManager *adm= new AAudioDeviceManager(rtcEngine);
	IAudioDeviceCollection* adc = adm->get()->enumerateRecordingDevices();
	char deviceName[MAX_DEVICE_ID_LENGTH] = { 0 };
	char deviceId[MAX_DEVICE_ID_LENGTH] = { 0 };
	SetConsoleOutputCP(65001);
	cout <<"Audio Recording Devices"<<endl;
	for (auto i = 0; i < adc->getCount(); i++)
	{
		adc->getDevice(i, deviceName, deviceId);
		cout << "deviceName:" << deviceName << " deviceId:" << deviceId << endl;
	}
}

extern "C" void AGORADL_API setRecordingDevice(LPVOID lpExtInfo)
{
	IRtcEngine *rtcEngine = CAgoraObject::GetAgoraObject(nullptr)->GetEngine();
	AAudioDeviceManager *adm = new AAudioDeviceManager(rtcEngine);
	if (auto res=adm->get()->setRecordingDevice((const char*)lpExtInfo) !=0 )
	{
		cout << "[error] setRecordingDevice failed :%d"<< res << endl;
	}
}


extern "C" void AGORADL_API enumerateVideoDevices()
{
	IRtcEngine *rtcEngine = CAgoraObject::GetAgoraObject(nullptr)->GetEngine();
	AVideoDeviceManager *vdm = new AVideoDeviceManager(rtcEngine);
	IVideoDeviceCollection* adc = vdm->get()->enumerateVideoDevices();
	char deviceName[MAX_DEVICE_ID_LENGTH] = { 0 };
	char deviceId[MAX_DEVICE_ID_LENGTH] = { 0 };
	SetConsoleOutputCP(65001);
	cout << "Video Devices" << endl;
	for (auto i = 0; i < adc->getCount(); i++)
	{
		adc->getDevice(i, deviceName, deviceId);
		cout << "deviceName:" << deviceName << " deviceId:" << deviceId << endl;
	}
}

extern "C" void AGORADL_API setVideoDevice(LPVOID lpExtInfo)
{
	IRtcEngine *rtcEngine = CAgoraObject::GetAgoraObject(nullptr)->GetEngine();
	AVideoDeviceManager *vdm = new AVideoDeviceManager(rtcEngine);
	if (auto res = vdm->get()->setDevice((const char*)lpExtInfo) != 0)
	{
		cout << "[error] Video setDevice failed :%d" << res << endl;
	}
}

extern "C" void AGORADL_API setExternalVideoSource()
{
    
    agora::util::AutoPtr<agora::media::IMediaEngine> mediaEngine;
    mediaEngine.queryInterface(CAgoraObject::GetAgoraObject(nullptr)->GetEngine(), agora::rtc::AGORA_IID_MEDIA_ENGINE);
    /*
    mediaEngine->setExternalVideoSource(true, false);
    */
	agora::base::AParameter apm(CAgoraObject::GetAgoraObject(nullptr)->GetEngine());

    apm->setParameters("{\"che.video.local.camera_index\":1024}");
	mediaEngine->registerVideoFrameObserver(&CAgoraObject::m_CExtendVideoFrameObserver);
}

extern "C" void AGORADL_API pushVideoFrame(char *buff, int w, int h)
{
    CAgVideoBuffer::GetInstance()->writeBuffer((BYTE*)buff, w, h);
}





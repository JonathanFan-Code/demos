#pragma once
#include "../zego/include/ZegoExpressSDK.h"
#include "ZegoEventHandler.h"
#include <string>

#ifdef _M_IX86
#pragma comment(lib, "../zego/lib/x86/ZegoExpressEngine.lib")
#elif defined _M_X64
#pragma comment(lib, "../zego/lib/x64/ZegoExpressEngine.lib")
#endif

#include "types.h"

using namespace ZEGO::EXPRESS;
using namespace ZEGO;
using namespace std;


class CZegoObject 
{
public:
	~CZegoObject(void);

	static CZegoObject *GetZegoObject();
	void destroyZegoEngine();

	void SetMainWnd(HWND hMainWnd);

	virtual int createEngine(LPVOID lpExtInfo, string  &strOutput);
	virtual int sharedEngine(LPVOID lpExtInfo, string &strOutput);
	virtual int enableVideo(LPVOID lpExtInfo, string &strOutput);
	virtual int setVideoProfile(LPVOID lpExtInfo, string &strOutput);
	virtual int joinChannel(LPVOID lpExtInfo, string &strOutput);
	virtual int leaveChannel(LPVOID lpExtInfo, string &strOutput);
	virtual int stopLocal(LPVOID lpExtInfo, string &strOutput);
	virtual int removeAllViews(LPVOID lpExtInfo, string &strOutput);
	virtual int destroy(LPVOID lpExtInfo, string &strOutput);
	virtual int enableEncoder(LPVOID lpExtInfo, string &strOutput);
	virtual int enableDecoder(LPVOID lpExtInfo, string &strOutput);
	virtual int disableAudio(LPVOID lpExtInfo, string &strOutput);
	virtual int disableVideo(LPVOID lpExtInfo, string &strOutput);
	virtual int videoDrawing(LPVOID lpExtInfo, string &strOutput);

public:
	void createZegoEngine();
	int initialize(string &strOutput);
	int destroyEngine();

	int setVideoConfig(LPVOID lpExtInfo, string &strOutput);
	//int startLocalAudio();
	int loginRoom(LPVOID lpExtInfo, string &strOutput);
	int startPreview();

	int logoutRoom();

	void onRoomStreamUpdate(const std::string &roomID, ZegoUpdateType updateType, const std::vector<ZegoStream> &streamList);


	IZegoExpressEngine* getEngine();
protected:
	CZegoObject(void);
private:
	static  CZegoObject	*m_lpZegoObject;

	IZegoExpressEngine*  m_lpZegoEngine = nullptr;

	std::shared_ptr<CZegoEventHandler> m_pgEventHandler;
	std::shared_ptr<CZegoCustomVideoRenderer> m_pgVideoRenderer;

	std::string  m_roomId;
	std::string  m_localUserID;
	std::vector<ZegoStream> m_zegoStreamList;
};


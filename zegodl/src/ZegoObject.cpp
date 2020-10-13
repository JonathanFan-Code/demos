#include "ZegoObject.h"
#include "AGExtInfoManager.h"

#include "json/json.h"
#include <tchar.h>


CZegoObject *CZegoObject::m_lpZegoObject = NULL;

CZegoObject::CZegoObject(void)
{
	m_pgEventHandler = std::make_shared<CZegoEventHandler>();
	m_pgVideoRenderer = std::make_shared<CZegoCustomVideoRenderer>();
}

CZegoObject::~CZegoObject(void)
{
}

void CZegoObject::destroyZegoEngine()
{
	if (m_lpZegoEngine) {
		ZegoExpressSDK::destroyEngine(m_lpZegoEngine);
		m_lpZegoEngine = nullptr;
	}
	if (m_lpZegoObject) {
		delete m_lpZegoObject;
		m_lpZegoObject = NULL;
	}
}

CZegoObject *CZegoObject::GetZegoObject()
{
	if (m_lpZegoObject == NULL)
	{
		m_lpZegoObject = new CZegoObject();
	}

	return m_lpZegoObject;
}

void CZegoObject::SetMainWnd(HWND hMainWnd)
{
	m_pgEventHandler->SetMsgReceiver(hMainWnd);
}

int CZegoObject::createEngine(LPVOID lpExtInfo, string &strOutput)
{
	createZegoEngine();
	return 0;
}

IZegoExpressEngine* CZegoObject::getEngine()
{
	if (nullptr == m_lpZegoEngine)
	{
		createZegoEngine();
	}
	return m_lpZegoEngine; 
}

int CZegoObject::sharedEngine(LPVOID lpExtInfo, string &strOutput)
{
	initialize(strOutput);
	return 0;
}
int CZegoObject::enableVideo(LPVOID lpExtInfo, string &strOutput)
{
	m_lpZegoEngine->enableCamera(true);
	m_lpZegoEngine->mutePublishStreamVideo(false);
	return 0;
}
int CZegoObject::setVideoProfile(LPVOID lpExtInfo, string &strOutput)
{
	return setVideoConfig(lpExtInfo, strOutput);
}
int CZegoObject::joinChannel(LPVOID lpExtInfo, string &strOutput)
{
	return loginRoom(lpExtInfo, strOutput);
}
int CZegoObject::leaveChannel(LPVOID lpExtInfo, string &strOutput)
{
	return logoutRoom();
}
int CZegoObject::stopLocal(LPVOID lpExtInfo, string &strOutput)
{
	return 0;
}
int CZegoObject::removeAllViews(LPVOID lpExtInfo, string &strOutput)
{
	return 0;
}
int CZegoObject::destroy(LPVOID lpExtInfo, string &strOutput)
{
	return 0;
}
int CZegoObject::enableEncoder(LPVOID lpExtInfo, string &strOutput)
{
	string rawJson((char*)lpExtInfo);
	Json::CharReaderBuilder builder;
	JSONCPP_STRING err;
	Json::Value root;

	const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
	if (!reader->parse(rawJson.c_str(), rawJson.c_str() + rawJson.length(), &root,
		&err)) {
		strOutput = "error";
		return EXIT_FAILURE;
	}

	bool bEnable = root["enableEncoder"].asBool();

	m_lpZegoEngine->enableHardwareEncoder(bEnable);
	return 0;
}
int CZegoObject::enableDecoder(LPVOID lpExtInfo, string &strOutput)
{
	string rawJson((char*)lpExtInfo);
	Json::CharReaderBuilder builder;
	JSONCPP_STRING err;
	Json::Value root;

	const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
	if (!reader->parse(rawJson.c_str(), rawJson.c_str() + rawJson.length(), &root,
		&err)) {
		strOutput = "error";
		return EXIT_FAILURE;
	}

	bool bEnable = root["enableDecoder"].asBool();

	m_lpZegoEngine->enableHardwareDecoder(bEnable);
	return 0;
}


void CZegoObject::createZegoEngine()
{
	if (!m_lpZegoEngine)
	{
		unsigned int appID = 928464678;
		std::string appSign = "2a485d1d1fe964eb7255d3c65ab1131fc8ad374a12231a1c7566827912096770";
		bool isTest = true;
		m_lpZegoEngine = ZegoExpressSDK::createEngine(appID, appSign, isTest, ZEGO_SCENARIO_GENERAL, nullptr);

		m_lpZegoEngine->setEventHandler(m_pgEventHandler);
	}
}

int CZegoObject::initialize(string &strOutput)
{
	if (!m_lpZegoEngine) {
		strOutput = "has not createAgoraRctEngine";
		return 3;
	}

	return 0;
}

int CZegoObject::destroyEngine()
{
	if (m_lpZegoEngine) {
		ZegoExpressSDK::destroyEngine(m_lpZegoEngine);
		m_lpZegoEngine = NULL;
	}
	
	return 0;
}


int CZegoObject::loginRoom(LPVOID lpExtInfo, string &strOutput)
{
	//API_CHECK_ENGINE_INITIAZE(m_lpAgoraEngine, bInitialize, strOutput);
	string rawJson((char*)lpExtInfo);
	Json::CharReaderBuilder builder;
	JSONCPP_STRING err;
	Json::Value root;

	const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
	if (!reader->parse(rawJson.c_str(), rawJson.c_str() + rawJson.length(), &root,
		&err)) {
		strOutput = "error";
		return EXIT_FAILURE;
	}

	auto channelId = root["channelId"].asString();
	auto cuid = root["uid"].asString();

	std::string roomId = channelId;
	m_roomId = roomId;
	ZegoUser user;
	user.userID = cuid;
	user.userName = cuid;
	m_localUserID = user.userID;

	m_lpZegoEngine->loginRoom(roomId, user);

	startPreview();

	m_lpZegoEngine->startPublishingStream(user.userID);
	return 0;
}

int CZegoObject::startPreview()
{
	CAGExtInfoManager *lpExtInfoManager = CAGExtInfoManager::GetAGExtInfoManager();
	int iUid = atoi(m_localUserID.c_str());
	HWND hWnd = 0;
	
	hWnd = (HWND)lpExtInfoManager->GetFirstView();
	
	ZegoCanvas canvas(hWnd, ZEGO_VIEW_MODE_ASPECT_FIT);
	m_lpZegoEngine->startPreview(&canvas);
	return 0;
}

int CZegoObject::setVideoConfig(LPVOID lpExtInfo, string &strOutput)
{
	//API_CHECK_ENGINE_INITIAZE(m_lpAgoraEngine, bInitialize, strOutput);
	string rawJson((char*)lpExtInfo);
	Json::CharReaderBuilder builder;
	JSONCPP_STRING err;
	Json::Value root;

	const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
	if (!reader->parse(rawJson.c_str(), rawJson.c_str() + rawJson.length(), &root,
		&err)) {
		strOutput =  "error";
		return EXIT_FAILURE;
	}

	ZegoVideoConfig videoConfig;
	auto cbitrate = root["bitrate"].asString();
	videoConfig.bitrate = stoi(cbitrate);
	auto cframeRate = root["fps"].asString();
	videoConfig.fps = stoi(cframeRate);
	std::string sDimensions = root["resolution"].asString();

	string::size_type pos = sDimensions.find("*");
	if (pos < sDimensions.size())
	{
		std::string swidth = sDimensions.substr(0, pos);
		std::string sheight = sDimensions.substr(pos + 1, sDimensions.size() - 1);
		videoConfig.captureWidth = atoi(swidth.c_str());
		videoConfig.captureHeight = atoi(sheight.c_str());
		videoConfig.encodeWidth = videoConfig.captureWidth;
		videoConfig.encodeHeight = videoConfig.captureHeight;
	}
	
	m_lpZegoEngine->setVideoConfig(videoConfig);
	return 0;
}


int CZegoObject::logoutRoom()
{
	m_lpZegoEngine->logoutRoom(m_roomId);
	m_zegoStreamList.clear();
	return 0;
}

void CZegoObject::onRoomStreamUpdate(const std::string &roomID, ZegoUpdateType updateType, const std::vector<ZegoStream> &streamList)
{
	if (m_roomId != roomID)
		return;

	int size = streamList.size();
	for ( int i = 0; i < size; i++ ) {
		ZegoStream stream = streamList.at(i);
		auto it = std::find_if(m_zegoStreamList.begin(), m_zegoStreamList.end(), [&](ZegoStream const &_stream) {
			return _stream.streamID == stream.streamID;
		});

		if (updateType == ZEGO_UPDATE_TYPE_ADD && it == m_zegoStreamList.end()) {
			m_zegoStreamList.push_back(stream);
		}

		if (updateType == ZEGO_UPDATE_TYPE_DELETE && it != m_zegoStreamList.end()) {
			m_lpZegoEngine->stopPlayingStream(stream.streamID);
			m_zegoStreamList.erase(it);
		}
	}

	CAGExtInfoManager *lpExtInfoManager = CAGExtInfoManager::GetAGExtInfoManager();

	HWND hWnd = NULL;
	int nViewPos = 1;//0 for local view
	for( int j = 0; j < m_zegoStreamList.size(); j++) {
		auto stream = m_zegoStreamList.at(j);

		HWND hWnd = (HWND)lpExtInfoManager->GetViewAt(nViewPos);
		if (hWnd != NULL)
		{
			ZegoCanvas canvas(hWnd, ZEGO_VIEW_MODE_ASPECT_FIT);
			m_lpZegoEngine->startPlayingStream(stream.streamID, &canvas);
			nViewPos++;
		}
	}
}

int CZegoObject::disableAudio(LPVOID lpExtInfo, string &strOutput)
{
	string rawJson((char*)lpExtInfo);
	Json::CharReaderBuilder builder;
	JSONCPP_STRING err;
	Json::Value root;

	const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
	if (!reader->parse(rawJson.c_str(), rawJson.c_str() + rawJson.length(), &root,
		&err)) {
		strOutput = "error";
		return EXIT_FAILURE;
	}

	bool bMute = root["muted"].asBool();

	m_lpZegoEngine->enableAudioCaptureDevice(!bMute);
	m_lpZegoEngine->mutePublishStreamAudio(bMute);
	return 0;
}

int CZegoObject::disableVideo(LPVOID lpExtInfo, string &strOutput)
{
	string rawJson((char*)lpExtInfo);
	Json::CharReaderBuilder builder;
	JSONCPP_STRING err;
	Json::Value root;

	const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
	if (!reader->parse(rawJson.c_str(), rawJson.c_str() + rawJson.length(), &root,
		&err)) {
		strOutput = "error";
		return EXIT_FAILURE;
	}

	bool bMute = root["muted"].asBool();

	m_lpZegoEngine->mutePublishStreamVideo(bMute);
	m_lpZegoEngine->enableCamera(!bMute);
	return 0;
}

int CZegoObject::videoDrawing(LPVOID lpExtInfo, string &strOutput)
{
	string rawJson((char*)lpExtInfo);
	Json::CharReaderBuilder builder;
	JSONCPP_STRING err;
	Json::Value root;

	const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
	if (!reader->parse(rawJson.c_str(), rawJson.c_str() + rawJson.length(), &root,
		&err)) {
		strOutput = "error";
		return EXIT_FAILURE;
	}


	bool bMute = root["muted"].asBool();
	int nType = root["type"].asInt();

	ZegoCustomVideoRenderConfig customVideoRenderConfig;
	customVideoRenderConfig.bufferType = (ZegoVideoBufferType)nType;
	customVideoRenderConfig.enableEngineRender = bMute;
	
	m_lpZegoEngine->enableCustomVideoRender(bMute, &customVideoRenderConfig);
	m_lpZegoEngine->setCustomVideoRenderHandler(m_pgVideoRenderer);

	return 0;
}

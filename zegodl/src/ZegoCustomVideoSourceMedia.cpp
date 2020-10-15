#include "ZegoCustomVideoSourceMedia.h"
#include "ZegoObject.h"

ZegoCustomVideoSourceMedia::ZegoCustomVideoSourceMedia()
{
    auto engine = ZegoExpressSDK::getEngine();
    if(engine == nullptr){
        return;
    }

    mediaPlayer = CZegoObject::GetZegoObject()->getEngine()->createMediaPlayer();

    auto mediaPlayerCallbackCenter = std::make_shared<ZegoExpressMediaPlayerCallbackCenter>();
    mediaPlayerCallbackCenter->setCallback(this);

    mediaPlayer->setEventHandler(mediaPlayerCallbackCenter);
	mediaPlayer->setAudioHandler(mediaPlayerCallbackCenter);
    mediaPlayer->setVideoHandler(mediaPlayerCallbackCenter, ZEGO_VIDEO_FRAME_FORMAT_BGRA32);
    
}

ZegoCustomVideoSourceMedia::~ZegoCustomVideoSourceMedia()
{
    auto engine = ZegoExpressSDK::getEngine();
    if(engine){
        engine->destroyMediaPlayer(mediaPlayer);
    }
}

ZegoCustomVideoSourceType ZegoCustomVideoSourceMedia::videoSourceType()
{
    return ZegoCustomVideoSourceType_Media;
}

void ZegoCustomVideoSourceMedia::getVideoFrame(std::shared_ptr<ZegoCustomVideoFrame> &videoFrame)
{
    std::lock_guard<std::mutex> lock(mediaMutex);
    if(mVideoFrameQueue.size()>0){
         videoFrame = mVideoFrameQueue.front();
         mVideoFrameQueue.pop();
    }else{
        videoFrame = nullptr;
    }
}
#include "AGExtInfoManager.h"
IZegoMediaPlayer *mediaPlayer3 = nullptr;
void ZegoCustomVideoSourceMedia::startPlayMedia(std::string path)
{
    if(mediaPlayer == nullptr){
        return;
    }
	
    mediaPath = path;
    mediaPlayer->loadResource(mediaPath, [=](int errorCode){
        if(errorCode==0){
		//	ZegoCanvas canvas(ZegoView(CAGExtInfoManager::GetAGExtInfoManager()->GetOneFreeView()));
		//	mediaPlayer->setPlayerCanvas(&canvas);
		//	mediaPlayer->setVolume(50);
			mediaPlayer->enableAux(true);
            mediaPlayer->enableRepeat(true);
            mediaPlayer->start();
        }
    });
}

void ZegoCustomVideoSourceMedia::stopPlayMedia()
{
    if(mediaPlayer == nullptr){
        return;
    }
    mediaPlayer->stop();
}

void ZegoCustomVideoSourceMedia::onMediaPlayerStateUpdate(IZegoMediaPlayer *mediaPlayer, ZegoMediaPlayerState state, int errorCode)
{

}

void ZegoCustomVideoSourceMedia::onVideoFrame(IZegoMediaPlayer *mediaPlayer, const unsigned char **data, unsigned int *dataLength, ZegoVideoFrameParam param)
{
    std::lock_guard<std::mutex> lock(mediaMutex);
    if(mVideoFrameQueue.size() <= 2 ){
        auto videoFrame = std::make_shared<ZegoCustomVideoFrame>();
        videoFrame->dataLength = dataLength[0];
        videoFrame->data = std::unique_ptr<unsigned char[]>(new unsigned char[dataLength[0]]);
        memcpy(videoFrame->data.get(), data[0], videoFrame->dataLength);
        videoFrame->param = param;
        videoFrame->referenceTimeMillsecond = this->getCurrentTimestampMS();

        mVideoFrameQueue.push(videoFrame);
    }
}

void ZegoCustomVideoSourceMedia::onAudioFrame(IZegoMediaPlayer* mediaPlayer, const unsigned char* data, unsigned int dataLength, ZegoAudioFrameParam param)
{
    std::lock_guard<std::mutex> lock(audioMutex);
    if(mAudioFrameQueue.size() <= 2 ){
        auto audioFrame = std::make_shared<ZegoCustomAudioFrame>();
        audioFrame->dataLength = dataLength;
        audioFrame->data = std::unique_ptr<unsigned char[]>(new unsigned char[dataLength]);
        memcpy(audioFrame->data.get(), data, audioFrame->dataLength);
        audioFrame->param = param;
        audioFrame->referenceTimeMillsecond = this->getCurrentTimestampMS();

        mAudioFrameQueue.push(audioFrame);
    }
}

void ZegoCustomVideoSourceMedia::getAudioFrame(std::shared_ptr<ZegoCustomAudioFrame> &audioFrame)
{
    std::lock_guard<std::mutex> lock(mediaMutex);
    if(mAudioFrameQueue.size()>0){
         audioFrame = mAudioFrameQueue.front();
         mAudioFrameQueue.pop();
    }else{
        audioFrame = nullptr;
    }
}


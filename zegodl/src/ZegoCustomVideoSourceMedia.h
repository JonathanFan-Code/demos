#ifndef ZEGOCUSTOMVIDEOSOURCEMEDIA_H
#define ZEGOCUSTOMVIDEOSOURCEMEDIA_H

#include "ZegoCustomVideoSourceBase.h"

#include "../../zego/include/ZegoExpressSDK.h"
using namespace ZEGO::EXPRESS;
#include <queue>
#include<iostream>
class IMediaPlayerCallback {
public:
    virtual ~IMediaPlayerCallback() = default;
	
    virtual void onMediaPlayerStateUpdate(IZegoMediaPlayer* /*mediaPlayer*/, ZegoMediaPlayerState /* state */, int /* errorCode */) {
	}

    virtual void onMediaPlayerNetworkEvent(IZegoMediaPlayer* /*mediaPlayer*/, ZegoMediaPlayerNetworkEvent /* networkEvent */) {
	}

    virtual void onMediaPlayerPlayingProgress(IZegoMediaPlayer* /*mediaPlayer*/, unsigned long long /* progress */) {
	}

    virtual void onVideoFrame(IZegoMediaPlayer* /*mediaPlayer*/, const unsigned char** /* buffer */, unsigned int* /*dataLenght*/, ZegoVideoFrameParam /* param */) {
    }

    virtual void onAudioFrame(IZegoMediaPlayer* /*mediaPlayer*/, const unsigned char * /* buffer */, unsigned int /*dataLenght*/, ZegoAudioFrameParam /* param */) {
    }
};

class ZegoExpressMediaPlayerCallbackCenter :
    public IZegoMediaPlayerEventHandler,
    public IZegoMediaPlayerVideoHandler,
    public IZegoMediaPlayerAudioHandler{

public:
    ~ZegoExpressMediaPlayerCallbackCenter() override{

    }
    void setCallback(IMediaPlayerCallback* cb){
        this->cb = cb;
    }

    void onMediaPlayerStateUpdate(IZegoMediaPlayer* mediaPlayer, ZegoMediaPlayerState state, int errorCode) override {
        if(cb){
            cb->onMediaPlayerStateUpdate(mediaPlayer, state, errorCode);
        }
	}
	
    void onMediaPlayerNetworkEvent(IZegoMediaPlayer* mediaPlayer, ZegoMediaPlayerNetworkEvent networkEvent)  override {
        if(cb){
            cb->onMediaPlayerNetworkEvent(mediaPlayer, networkEvent);
        }
	}

    void onMediaPlayerPlayingProgress(IZegoMediaPlayer* mediaPlayer, unsigned long long progress) override {
        if(cb){
            cb->onMediaPlayerPlayingProgress(mediaPlayer, progress);
        }
	}

    void onAudioFrame(IZegoMediaPlayer* mediaPlayer, const unsigned char* data, unsigned int dataLenght, ZegoAudioFrameParam param) override {
		if (cb) {
            cb->onAudioFrame(mediaPlayer, data, dataLenght, param);
		}
	}

    void onVideoFrame(IZegoMediaPlayer* mediaPlayer, const unsigned char**data, unsigned int* dataLenght, ZegoVideoFrameParam param)  override {
        if (cb) {
            cb->onVideoFrame(mediaPlayer, data, dataLenght, param);
		}
	}

private:
    IMediaPlayerCallback* cb = nullptr;
};

class ZegoCustomVideoSourceMedia: public ZegoCustomVideoSourceBase, public IMediaPlayerCallback
{
public:
    ZegoCustomVideoSourceMedia();
    ~ZegoCustomVideoSourceMedia() override;

    ZegoCustomVideoSourceType videoSourceType() override;
    void getVideoFrame(std::shared_ptr<ZegoCustomVideoFrame> & videoFrame) override;
    void getAudioFrame(std::shared_ptr<ZegoCustomAudioFrame>  &audioFrame) override;

    void startPlayMedia(std::string path);
    void stopPlayMedia();

    void onMediaPlayerStateUpdate(IZegoMediaPlayer* mediaPlayer, ZegoMediaPlayerState state, int errorCode) override;
    void onVideoFrame(IZegoMediaPlayer* mediaPlayer, const unsigned char** data, unsigned int* dataLength, ZegoVideoFrameParam param) override;
    void onAudioFrame(IZegoMediaPlayer* mediaPlayer, const unsigned char* data, unsigned int dataLength, ZegoAudioFrameParam param) override;
private:
    std::mutex mediaMutex;
    std::mutex audioMutex;
    std::queue<std::shared_ptr<ZegoCustomVideoFrame>> mVideoFrameQueue;
    std::queue<std::shared_ptr<ZegoCustomAudioFrame>> mAudioFrameQueue;
    ZEGO::EXPRESS::IZegoMediaPlayer *mediaPlayer = nullptr;
    std::string mediaPath;
};

#endif // ZEGOCUSTOMVIDEOSOURCEMEDIA_H

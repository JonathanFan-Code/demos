#include "ExtendAudioFrameObserver.h"
#include <chrono>


CExtendAudioFrameObserver::CExtendAudioFrameObserver()
{
}


CExtendAudioFrameObserver::~CExtendAudioFrameObserver()
{
}

bool CExtendAudioFrameObserver::onRecordAudioFrame(AudioFrame& audioFrame)
{
	CircleBuffer::GetInstance()->getAudioInfo(audioFrame.samplesPerSec, audioFrame.channels);
	unsigned int nSize = audioFrame.channels*audioFrame.samples * 2;
    unsigned int readByte = 0;
    int timestamp = timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
    CircleBuffer::GetInstance()->readBuffer(audioFrame.buffer, nSize, &readByte, timestamp);
    audioFrame.renderTimeMs = timestamp;
	return true;
}

bool CExtendAudioFrameObserver::onPlaybackAudioFrame(AudioFrame& audioFrame)
{
	return true;
}

bool CExtendAudioFrameObserver::onMixedAudioFrame(AudioFrame& audioFrame)
{
	return true;
}

bool CExtendAudioFrameObserver::onPlaybackAudioFrameBeforeMixing(unsigned int uid, AudioFrame& audioFrame)
{
	return true;
}

#pragma once
#include "types.h"
#include <queue>
#include <mutex>
#include <condition_variable>

#define CIC_WAITTIMEOUT		0
#define AUDIO_CALLBACK_TIMES  100
#define MAX_AUDIO_SAMPLE_SIZE (48000*2*2/AUDIO_CALLBACK_TIMES)*10//sampleRate*sizeof(16bit)*channel+ AUDIO_CALLBACK_TIMES*sizeof(timestamp)=max_s

class Semaphore {
public:
	Semaphore(int count, int maxcount) :m_count(count), m_maxcount(maxcount){

	}
	~Semaphore() {}
	int acquire(int count=1) {
		std::unique_lock<std::mutex> locker(m_mutex);
		m_condition.wait(locker, [this, count] {return m_count >= count; });
		m_count -= count;
		auto cursor = m_cursor;
		m_cursor += count;
		m_cursor %= m_maxcount;
		return cursor;
	}
	void release(int count=1) {
		{
			std::lock_guard<std::mutex> locker(m_mutex);
			m_count += count;
		}
		m_condition.notify_one();
	}
	unsigned int getCursor(){
		std::lock_guard<std::mutex> locker(m_mutex);
		return m_cursor;
	}

	unsigned int getCount() {
		std::lock_guard<std::mutex> locker(m_mutex);
		return m_count;
	}
private:
	unsigned int m_cursor = 0;
	int m_count;
	int m_maxcount;
	std::mutex m_mutex;
	std::condition_variable m_condition;
};

class CircleBuffer
{
private:
	BYTE* m_pBuffer;
	unsigned int m_iBufferSize;

	Semaphore freeSpace;  
	Semaphore usedSpace;
	std::mutex m_mutex;

	bool m_bComplete;
	int wait_timeout;
	int m_nSampleRate = 44100;
	int m_nChannels = 2;
    std::queue<int> audioTimeQueue;
public:
    CircleBuffer(const unsigned int iBufferSize,int waittimeout);
	~CircleBuffer(void);
	bool IsComplete();
	void SetComplete();
	unsigned int getFreeSize();
	unsigned int getUsedSize();
	void writeBuffer(const void* pSourceBuffer, const unsigned int iNumBytes);
	bool readBuffer(void* pDestBuffer, const unsigned int iBytesToRead, unsigned int* pbBytesRead, int& audioTime);
	void setAudioInfo(int nSampleRate, int nChannels) 
	{ 
		m_nSampleRate = nSampleRate;
		m_nChannels = nChannels;
	};
	void getAudioInfo(int &nSampleRate, int &nChannels)
	{
		nSampleRate = m_nSampleRate;
		nChannels = m_nChannels;
	};

    static CircleBuffer* GetInstance();
    static void CloseInstance();
};


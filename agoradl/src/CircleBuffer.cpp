
#include "CircleBuffer.h"
#include <iostream>
CircleBuffer* CircleBuffer::GetInstance()
{
	static CircleBuffer circleBuffer(MAX_AUDIO_SAMPLE_SIZE, 0);
    return &circleBuffer;
}

void CircleBuffer::CloseInstance()
{
}

CircleBuffer::CircleBuffer(const unsigned int iBufferSize,int waittimeout)
	:freeSpace(iBufferSize, iBufferSize),
	usedSpace(0, iBufferSize)
{
	this->m_iBufferSize = iBufferSize;
	this->m_pBuffer = (BYTE*)malloc(iBufferSize);
	this->m_bComplete = false;
	this->wait_timeout=waittimeout;
}

CircleBuffer::~CircleBuffer(void)
{
	free(this->m_pBuffer);
}

bool CircleBuffer::IsComplete()
{
	return this->m_bComplete;
}

void CircleBuffer::SetComplete()
{
	std::lock_guard<std::mutex> buf_lock(m_mutex);
	this->m_bComplete = true;
}

unsigned int CircleBuffer::getFreeSize()
{
	return freeSpace.getCount();
}

unsigned int CircleBuffer::getUsedSize()
{
	return usedSpace.getCount();
}


void CircleBuffer::writeBuffer(const void* pSourceBuffer, const unsigned int iNumBytes)
{
	if (iNumBytes > this->m_iBufferSize / 2)
	{
		std::cout << "error iNumBytes: "<< iNumBytes <<" is greater than half of buffer size" << std::endl;
		return;
	}
		
	unsigned int iBytesToWrite = iNumBytes;
	BYTE* pSourceReadCursor = (BYTE*)pSourceBuffer;

	auto cur = freeSpace.acquire(iNumBytes);

	unsigned int iChunkSize = this->m_iBufferSize - cur;
	if (iChunkSize > iBytesToWrite)
		iChunkSize = iBytesToWrite;

	memcpy(this->m_pBuffer + cur, pSourceReadCursor, iChunkSize);
	pSourceReadCursor += iChunkSize;
	iBytesToWrite -= iChunkSize;
	cur += iChunkSize;

	cur %= this->m_iBufferSize;

	if (iBytesToWrite)
	{
		memcpy(this->m_pBuffer + cur, pSourceReadCursor, iBytesToWrite);
	}

	usedSpace.release(iNumBytes);
}

bool CircleBuffer::readBuffer(void* pDestBuffer, const unsigned int _iBytesToRead, unsigned int* pbBytesRead, int& audioTime)
{
	if (_iBytesToRead > this->m_iBufferSize/2 )
	{
		std::cout << "error _iBytesToRead: " << _iBytesToRead << " is greater than half of buffer size" << std::endl;
		return false;
	}

	unsigned int iBytesToRead = _iBytesToRead;
	unsigned int iBytesRead = 0;

	auto cur = usedSpace.acquire(_iBytesToRead);

	unsigned int iChunkSize = this->m_iBufferSize - cur;
	if (iChunkSize > iBytesToRead)
		iChunkSize = iBytesToRead;

	memcpy((BYTE*)pDestBuffer + iBytesRead, this->m_pBuffer + cur, iChunkSize);

	iBytesRead += iChunkSize;
	iBytesToRead -= iChunkSize;
	cur += iChunkSize;
	cur %= this->m_iBufferSize;

	if (iBytesToRead)
	{
		memcpy((BYTE*)pDestBuffer + iBytesRead, this->m_pBuffer + cur, iBytesToRead);
	}

	freeSpace.release(_iBytesToRead);
	
	*pbBytesRead = iBytesRead;
	return true;
}


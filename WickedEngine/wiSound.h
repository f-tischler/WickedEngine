#pragma once
#include "CommonInclude.h"

#include <xaudio2.h>
#pragma comment(lib,"xaudio2.lib")

#include <string>
#include <thread>


#ifdef _XBOX //Big-Endian
#define fourccRIFF 'RIFF'
#define fourccDATA 'data'
#define fourccFMT 'fmt '
#define fourccWAVE 'WAVE'
#define fourccXWMA 'XWMA'
#define fourccDPDS 'dpds'
#endif

#ifndef _XBOX //Little-Endian
#define fourccRIFF 'FFIR'
#define fourccDATA 'atad'
#define fourccFMT ' tmf'
#define fourccWAVE 'EVAW'
#define fourccXWMA 'AMWX'
#define fourccDPDS 'sdpd'
#endif

class wiAudioEngine
{
public:
	wiAudioEngine();
	~wiAudioEngine();

	IXAudio2MasteringVoice* pMasterVoice;
	IXAudio2* pXAudio2;
	bool INITIALIZED;

	void SetVolume(float);
	float GetVolume();

	HRESULT Initialize();
};

class wiSound
{
protected:
	WAVEFORMATEX wfx;
	XAUDIO2_BUFFER buffer;
	IXAudio2SourceVoice* pSourceVoice;

	HRESULT FindChunk(HANDLE hFile, DWORD fourcc, DWORD & dwChunkSize, DWORD & dwChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void * buffer, DWORD buffersize, DWORD bufferoffset);
	HRESULT OpenFile(const TCHAR*);

	HRESULT PlaySound(wiAudioEngine* engine);
	void StopSound();
public:
	wiSound();
	virtual ~wiSound();
	virtual void Initialize();
	
	HRESULT Load(std::wstring);
	HRESULT Load(std::string);
	virtual HRESULT Play(DWORD delay = 0) = 0;
	void Stop();
};

class wiSoundEffect : public wiSound
{
private:
	static wiAudioEngine* audioEngine;
public:
	wiSoundEffect();
	wiSoundEffect(std::wstring);
	wiSoundEffect(std::string);
	~wiSoundEffect();
	static HRESULT Initialize();

	static void SetVolume(float);
	static float GetVolume();
	HRESULT Play(DWORD delay = 0) override;
};

class wiMusic : public wiSound
{
private:
	static wiAudioEngine* audioEngine;
public:
	wiMusic();
	wiMusic(std::wstring);
	wiMusic(std::string);
	~wiMusic();
	static HRESULT Initialize();

	static void SetVolume(float);
	static float GetVolume();
	HRESULT Play(DWORD delay = 0) override;
};


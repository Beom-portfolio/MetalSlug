#pragma once
class SoundManager : public Singleton<SoundManager>
{
public:
	SoundManager();
	~SoundManager();

public:
	void Initialize();
	void LoadSoundFile();
	void PlaySound(TCHAR* SoundKey, CHANNEL id);
	void PlayBGM(TCHAR* SoundKey, CHANNEL id);
	void UpdateSound();
	void StopSound(CHANNEL id);
	void StopAll();
	void Release();

private:
	FMOD_SYSTEM* m_System;
	FMOD_CHANNEL* m_ChannelArr[CH_END]; // 채널은 중첩되지 않게 준비.

	map<const TCHAR*, FMOD_SOUND*>	m_mapSound;
};


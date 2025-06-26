#include "Stdafx.h"
#include "SoundManager.h"

SoundManager::SoundManager() : _system(nullptr)
{
}

HRESULT SoundManager::init()
{
	// ���� �ý��� ����
	System_Create(&_system);

	// �ý��� �ʱ�ȭ
	FMOD_RESULT fr = _system->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, NULL);
	if (fr == FMOD_ERR_OUTPUT_INIT)
	{
		_system->release();

		System_Create(&_system);
		_system->setOutput(FMOD_OUTPUTTYPE_NOSOUND);
		fr = _system->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, NULL);
	}

	return S_OK;
}

void SoundManager::release()
{
	mapSoundIter soundIter = _mSoundList.begin();

	for (int i = 0; i < _mActiveChannels.size(); ++i)
	{
		_mActiveChannels[i].chaneel->stop();
	}

	for (; soundIter != _mSoundList.end(); ++soundIter)
	{
		soundIter->second->release();
	}

	// �ý��� ����
	if (_system != nullptr)
	{
		_system->release();
		_system->close();
	}
}

void SoundManager::update()
{
	_system->update();

	bool isPaused;
	bool isPlaying;

	for (int i = 0; i < _mActiveChannels.size(); ++i)
	{
		_mActiveChannels[i].chaneel->getPaused(&isPaused);
		if (isPaused)return;

		_mActiveChannels[i].chaneel->isPlaying(&isPlaying);
		if (isPlaying == false)
		{
			_mActiveChannels[i].chaneel->stop();
			_mActiveChannels.erase(_mActiveChannels.begin() + i);
			--i;
		}
	}
}

void SoundManager::addSound(string strKey, const char* fileName, bool bgm, bool loop)
{
	mapSoundIter iter = _mSoundList.find(strKey);
	if (iter != _mSoundList.end()) return;

	Sound* sound = nullptr;

	if (loop)
	{
		if (bgm)
		{
			// ��θ� ������ֱ� ������ createStream
			// 1 : 1 ��Ī
			// createStream(���ϸ�, ���带 ���� ���� ���, ���� ���� ��ȯ, �ּҰ�)
			_system->createStream(fileName, FMOD_LOOP_NORMAL, NULL, &sound);
		}
		else
		{
			// �������� ���������� ���ÿ� ���� ���� ���� ��� ����
			_system->createSound(fileName, FMOD_LOOP_NORMAL, NULL, &sound);
		}
	}
	else
	{
		if (bgm)
		{
			_system->createStream(fileName, FMOD_DEFAULT, NULL, &sound);
		}
		else
		{
			_system->createSound(fileName, FMOD_DEFAULT, NULL, &sound);
		}
	}

	if (sound != nullptr)
	{
		_mSoundList.insert(make_pair(strKey, sound));
	}
}

void SoundManager::play(string strKey, float volume)
{
	//�Ͻ����� �Ǿ� �ִ� ���� ���� �Ǵ�
	for (int i = 0; i < _mActiveChannels.size(); ++i)
	{
		if (_mActiveChannels[i].soundName == strKey)
		{
			bool isPaused;
			_mActiveChannels[i].chaneel->getPaused(&isPaused);
			if (isPaused)
			{
				_mActiveChannels[i].chaneel->setPaused(false);
				return;
			}
		}
	}

	if (_mActiveChannels.size() >= TOTALSOUNDBUFFER) return;

	//�ش� �̸��� ���尡 ���ٸ� return 
	mapSoundIter iter = _mSoundList.find(strKey);
	if (iter == _mSoundList.end()) return;

	Channel* channel;
	Sound* sound = iter->second;

	_system->playSound(FMOD_CHANNEL_FREE, sound, false, &channel);
	channel->setVolume(volume);

	ChannelInfo channelInfo;
	channelInfo.chaneel = channel;
	channelInfo.soundName = strKey;
	_mActiveChannels.push_back(channelInfo);
}

void SoundManager::stop(string strKey)
{
	for (int i = 0; i < _mActiveChannels.size(); ++i)
	{
		if (_mActiveChannels[i].soundName == strKey)
		{
			_mActiveChannels[i].chaneel->stop();
			_mActiveChannels.erase(_mActiveChannels.begin() + i);
			break;
		}
	}
}

void SoundManager::pause(string strKey)
{
	for (int i = 0; i < _mActiveChannels.size(); ++i)
	{
		if (_mActiveChannels[i].soundName == strKey)
		{
			_mActiveChannels[i].chaneel->setPaused(true);
			break;
		}
	}
}
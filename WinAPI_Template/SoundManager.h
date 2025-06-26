#pragma once
#include "SingletonBase.h"

#pragma region ���� (FMOD + Ʈ������ + ���͸� ����)
/*
FMOD

- ���� ���� ���̺귯��
	���� ���� �����̱� ������ �Ϲ����� Ȯ���ڴ� ���� �����Ѵ�
	�پ��� �÷������� ������ �Ѵ�.

- WinAPI / DirectX ���� ��쿡�� ��ü ���̺귯���� ������ ������ ������ �ʿ��� ��찡 ���� �����ϴ�.
	���� �Ⱓ ���� (������ ������� �и��Ǿ� ���� Ȱ���ϱ� ��������.)

�� ��� ����

- �𸮾� + ����Ƽ������ ���̼��� ������� �⺻ ����Ǿ��ִ�.
	�׷��� ������ ������ ��찡 ���� ��ø� ��ǥ�� �Ҷ��� ���̼����� �ʿ�� �Ѵ�.

- �𸮾� ����
	�ſ� ���̱� ������ ���̼��� ������� (�⺻ �÷�������)����Ǿ��ִ�.
	�÷����� �߰��ؼ� ����.
	�� EX) .bank  - fmod visualizer

- ����Ƽ ����
	�⺻������ FMODä��, ��� ����� ä�������� �ʴ´�.
	�߰� ����� ����ϱ� ���ؼ��� �߰� ������ ��ġ�ؾ� �Ѵ�.
	�� EX) .bank  - fmod visualizer

- �̿��� �÷���
	����ϱ� ���� ����ó���� �ʿ��ϴ�.
	���, Ŭ����, �̸� ����, ���̺귯�� ��ũ ->  ����??

- ����, �Ϳ�, ���̿���ũ �ø���, DJMAX RespectV ��� ���� ���ӿ��� ����ϰ��ִ�.

�� FMOD ����

- ũ�� 3������ ������.
�� ���̺귯�� + ���α׷�

1. FMOD Ex
	��StudioAPI / CoreAPI
	�� �ο췹�� ���� ����(Native ���� ä��Ǵ� API)
	�� API ���� - ������ ������.
	�� �ڵ��� ���ϸ� ���� ������ ����. (����)
	�� �Ϲ����� ���� ������ ����ϰų� �����̳ʰ� �������� �����̵Ǵ� ��찡 ����. (wav, mp3, mid)


2. FMOD �̺�Ʈ �ý���
	�� Ex�� ���� ���̾�
	�� �����̳ʰ� �۾��� ���� �������� ����ϴ� Data ��� Driven API
	�� �����̳��� ������� ���� ����ȭ�� �ڵ�� ��������� �븱 �� �ִ�.
	�� �����̳ʿ� ���� ���� Ʃ���� �����ϱ� ������ ���α׷��Ӱ� ���忡 �Ű澲�� �ʾƵ� �ȴ�. -> ���߼ӵ� ���

	�� ��Ȳ�� ���带 �����̳ʿ� �־�ΰ�
	�� �̺�Ʈ�� ���� �ε����� ���ڷ� �־��ְ� �÷��̸� ���ָ� �Ǵ� ���


3. FMOD �����̳�
	�� ���� �̺�Ʈ�� ������ ��
	�� ��ȹ + ���� + ���⼺ �ܰ迡�� FMOD�� ä���� �Ǹ� ���� �����̳ʰ� �ַ� ����Ѵ�.
	�� ��� ����, �����̳� ���̴� Ʈ������ ���踦 �� �����̱� ������ ���α׷��ӷμ��� ���ϴ�.

�����̳ʿ� ������ �ϵ��� ���� �ϵ��� ������� �˾ƾ� �ϴ� ������̴�.

FMOD ���� �ܺα�� ��ü�� ���̺귯���� ���� �ش� �÷����� �� �°Բ� Ŀ���ҵǱ� ������
�ܺ� ���̺귯���� ����ϱ� ���ؼ��� ���̺귯���� ���� ���ذ� �ʿ��ϴ�.

	�� ���� ���̺귯�� - .dll
		��Ÿ�ӿ��� ã�Ƽ� ���� ������ �����н� �Ű澲��.


	�� ���� ���̺귯�� - .lib
		�� ���ԵǾ��ֱ� ������ ���� ã�� �ʾƵ� �ȴ�.	(����)
		�� ���̺귯���� ũ�� ������Ʈ�� ���ſ����� �ִ�.(����)

	������ �ʿ��� ����̴�? ->���� ���̺귯���� �ӵ��� ì����.



*/
#pragma endregion

using namespace FMOD;

// ���� ���۸� �� 30�� + 10���� ���������� �غ�
#define SOUNDBUFFER 64
#define EXTRACHANNELBUFFER 10

#define TOTALSOUNDBUFFER SOUNDBUFFER + EXTRACHANNELBUFFER

class SoundManager : public SingletonBase<SoundManager>
{
private:
	struct ChannelInfo
	{
		string soundName;
		Channel* chaneel;
	};

	typedef map<string, Sound*>					mapSoundList;
	typedef map<string, Sound*>::iterator		mapSoundIter;

private:
	// FMOD�� ����ϱ� ���� ��������, ������
	System* _system;

	Channel* _chanel;

	// ���� ����Ʈ
	mapSoundList _mSoundList;

	// ���� Ȱ��ȭ�� ä��
	vector<ChannelInfo> _mActiveChannels;

public:
	HRESULT init();
	void release();
	void update();

	void addSound(string strKey, const char* fileName, bool bgm, bool loop);

	void play(string strKey, float volume = 1.0f);
	void stop(string strKey);
	void pause(string strKey);

	SoundManager();
	~SoundManager() {}
};
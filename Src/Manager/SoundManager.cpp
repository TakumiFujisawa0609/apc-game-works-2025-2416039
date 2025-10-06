#include <DxLib.h>
#include "SoundManager.h"

SoundManager* SoundManager::instance_ = nullptr;

void SoundManager::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new SoundManager();
	}
	instance_->Init();

}

SoundManager& SoundManager::GetInstance(void)
{
	// TODO: return ステートメントをここに挿入します
	if (instance_ == nullptr)
	{
		SoundManager::CreateInstance();
	}
	return *instance_;
}

void SoundManager::Init(void)
{
	se_ = -1;
	slowSE_ = -1;
	bgm_ = -1;
}


void SoundManager::PlayBGM(int handle)
{
	
}

void SoundManager::PlaySlowBGM(int handle)
{
}

void SoundManager::StopBGM(int handle)
{
}

void SoundManager::PlaySE(int handle)
{
	se_= DuplicateSoundMem(handle);
	// 複製したハンドルを再生する
	if (se_ != -1) 
	{
		PlaySoundMem(se_, DX_PLAYTYPE_BACK);
	}

}

void SoundManager::PlaySlowSE(int handle)
{
	se_ = DuplicateSoundMem(handle);
	slowSE_ = GetFrequencySoundMem(handle);
	// 複製したハンドルを再生する
	if (se_ != -1)
	{
		SetFrequencySoundMem(slowSE_/2, se_);
		PlaySoundMem(se_, DX_PLAYTYPE_BACK);
	}
}

void SoundManager::StopSE(int handle)
{

}



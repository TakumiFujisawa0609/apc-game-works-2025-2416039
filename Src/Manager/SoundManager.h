#pragma once
class SoundManager
{
public:

	


	// インスタンスの生成
	static void CreateInstance(void);

	// インスタンスの取得
	static SoundManager& GetInstance(void);

	void Init(void);

	
	void PlayBGM(int handle);
	void PlaySlowBGM(int handle);
	void StopBGM(int handle);
	void PlaySE(int handle);
	void PlaySlowSE(int handle);
	void StopSE(int handle);

private:
	static SoundManager* instance_;

	int se_;
	int slowSE_;

	int bgm_;
	

};


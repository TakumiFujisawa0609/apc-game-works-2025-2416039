#include <string>
#include <DxLib.h>
#include "../Application.h"
#include "../Utility/AsoUtility.h"
#include "../Manager/SceneManager.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/InputManager.h"
#include "TitleScene.h"

TitleScene::TitleScene(void)
{

}

TitleScene::~TitleScene(void)
{
	
}

void TitleScene::Init(void)
{


	count_ = 0;
	sousa_ = false;
}

void TitleScene::Update(void)
{
	InputManager& ins = InputManager::GetInstance();
	count_++;
	if (!sousa_)
	{
		
		if (count_ >= 3)
		{
			if (ins.IsTrgDown(KEY_INPUT_SPACE)|| ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN))
			{
				SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME);
				count_ = 0;
			}
			if (ins.IsTrgDown(KEY_INPUT_RETURN) || ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::RIGHT))
			{
				sousa_ = true;
				count_ = 0;
			}
			
		}
	}
	else if(sousa_)
	{
		if (ins.IsTrgDown(KEY_INPUT_RETURN) || ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::RIGHT))
		{
			sousa_ = false;
			count_ = 0;
		}

	}
	
}

void TitleScene::Draw(void)
{
	if (!sousa_)
	{

		DrawString(0, 100, "Title Scene", 0x000000);
		DrawString(0, 130, "スベース(Aボタン)でゲームスタート", 0x000000);
		DrawString(0, 160, "ENTER(Bボタン)で操作方法", 0x000000);
	}
	else if (sousa_)
	{
		DrawString(0, 100, "操作方法", 0x000000);
		DrawString(0, 130, "移動         ：Lスティック　/　WASD", 0x000000);
		DrawString(0, 160, "カメラ操作   ：Rスティック　/　←→", 0x000000);
		DrawString(0, 190, "ガード       ：RT長押し　/　スペース長押し", 0x000000);
		DrawString(0, 220, "パリ―       ：RTを離す　/　スペースを離す", 0x000000);
		DrawString(0, 250, "回避         ：A　/　Lシフト", 0x000000);
		DrawString(0, 280, "攻撃         ：B　/　Kキー", 0x000000);
		DrawString(0, 310, "ENTER(Bボタン)でタイトルへ戻る", 0x000000);
	}
}


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
	
	

}

void TitleScene::Update(void)
{

	
	// シーン遷移
	InputManager& ins = InputManager::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME);
	}
	
}

void TitleScene::Draw(void)
{
	DrawString(0, 100, "Title Scene", 0x000000);
	DrawString(0, 130, "スベースでゲームに", 0x000000);
}


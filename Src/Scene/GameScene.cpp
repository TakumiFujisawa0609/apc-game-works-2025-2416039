#include <DxLib.h>
#include "../Application.h"
#include "../Utility/AsoUtility.h"
#include "../Manager/SceneManager.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/EnemyManager.h"
#include "../Object/Collision/Collision.h"
#include "../Object/Camera/Camera.h"
#include "../Object/Grid/Grid.h"
#include "../Object/Player/Player.h"
#include "GameScene.h"

GameScene::GameScene(void)
{
	
}

GameScene::~GameScene(void)
{
	
}

void GameScene::Init(void)
{
	//インストラクター
	//カメラ機能の初期化
	camera_ = new Camera();

	//グリッド機能の初期化
	grid_ = new Grid();

	//プレイヤー機能の初期化
	player_ = new Player();

	//エネミー管理機能の初期化
	enemyManager_ = new EnemyManager(player_,this);

	//当たり判定機能の初期化
	collision_ = new Collision();

	//Init
	camera_->Init(player_);
	grid_->Init();
	player_->Init(camera_);
	enemyManager_->Init();
	collision_->Init(player_,enemyManager_);

	camera_->ChangeMode(Camera::MODE::FOLLOW);
}

void GameScene::Update(void)
{
	InputManager& ins = InputManager::GetInstance();
	player_->Update();
	enemyManager_->Update();
	collision_->Update();
	// シーン遷移
	if (ins.IsTrgDown(KEY_INPUT_R)||ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::BACK))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::TITLE);
	}

}

void GameScene::Draw(void)
{
	// カメラ設定
	camera_->SetBeforeDraw();
	//グリッド線
	grid_->Draw();
	//プレイヤー
	player_->Draw();

	//エネミー
	enemyManager_->Draw();

	DrawString(0, 100, "Game Scene", 0x000000);
}



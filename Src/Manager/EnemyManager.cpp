
#include <DXLib.h>
#include "../Application.h"
#include "../Utility/AsoUtility.h"
#include "ResourceManager.h"
#include "../Scene/GameScene.h"
#include "../Object/Player/Player.h"
#include "../Object/Enemy/EnemyBase.h"
#include "../Object/Enemy/EnemyM.h"
#include "../Object/Enemy/EnemyR.h"
#include "../Object/Enemy/EnemyU.h"
#include "../Object/Shot/ShotBase.h"
#include "EnemyManager.h"

EnemyManager::EnemyManager(Player* player, GameScene* gameScene)
{
	player_ = player;
	gameScene_ = gameScene;
}

EnemyManager::~EnemyManager(void)
{
}

void EnemyManager::Init(void)
{
	// 画像の読み込み
	ResourceManager& res = ResourceManager::GetInstance(); // リソースマネージャのインスタンス取得

	enemyModelIds_.emplace_back(
		res.Load(ResourceManager::SRC::ENEMYM).handleId_);

	enemyModelIds_.emplace_back(
		res.Load(ResourceManager::SRC::ENEMYR).handleId_);

	enemyModelIds_.emplace_back(
		res.Load(ResourceManager::SRC::ENEMYU).handleId_);

	// 攻撃エフェクト用のモデルのロード
	attackEffectModelIds_.emplace_back(
		res.Load(ResourceManager::SRC::EFFCT1).handleId_);

	sponCuntW_ = 0;
	sponDilayM_ = 0;
	sponR_ = 0;
	sponDilayR_ = 0;
	sponU_ = 0;
	sponDilayU_ = 0;
}

void EnemyManager::Update(void)
{
	sponDilayM_++;
	sponDilayR_++;
	sponDilayU_++;



	if (sponCuntW_ < MAX_W)
	{
		if (sponDilayM_ > MAX_DILAY)
		{

			EnemyBase* enemy_ = new EnemyM();
			enemy_->Init(EnemyBase::TYPE::ENEMYM,
				enemyModelIds_[static_cast<int>(EnemyBase::TYPE::ENEMYM)], attackEffectModelIds_[static_cast<int>(ShotBase::TYPE::STRAIGHT)], player_);
			enemys_.push_back(enemy_);
			sponCuntW_++;
			sponDilayM_ = 0;
		}
	}
	if (sponU_ < MAX_W)
	{
		if (sponDilayR_ > MAX_DILAY)
		{

			EnemyBase* enemy_ = new EnemyR();
			enemy_->Init(EnemyBase::TYPE::ENEMYR,
				enemyModelIds_[static_cast<int>(EnemyBase::TYPE::ENEMYR)], attackEffectModelIds_[static_cast<int>(ShotBase::TYPE::STRAIGHT)], player_);
			enemys_.push_back(enemy_);
			sponU_++;
			sponDilayR_ = 0;
		}
	}
	if (sponR_ < MAX_W)
	{
		if (sponDilayU_ > MAX_DILAY)
		{

			EnemyBase* enemy_ = new EnemyU();
			enemy_->Init(EnemyBase::TYPE::ENEMYU,
				enemyModelIds_[static_cast<int>(EnemyBase::TYPE::ENEMYU)], -1, player_);
			enemys_.push_back(enemy_);
			sponR_++;
			sponDilayU_ = 0;
		}
	}

	for (EnemyBase* enemy : enemys_)
	{
		enemy->Update();
	}
}

void EnemyManager::Draw(void)
{
	for (EnemyBase* enemy : enemys_)
	{
		enemy->Draw();
	}
	
}



void EnemyManager::WAVE01()
{
}

void EnemyManager::WAVE02()
{
}

void EnemyManager::WAVE03()
{
}

void EnemyManager::END()
{
}

void EnemyManager::ChangeWave(WAVE wave)
{
}

std::vector<EnemyBase*> EnemyManager::GetEnemys()
{
	return enemys_;
}

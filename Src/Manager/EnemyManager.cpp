
#include <DXLib.h>
#include "../Application.h"
#include "../Utility/AsoUtility.h"
#include "ResourceManager.h"
#include "../Scene/GameScene.h"
#include "../Object/Player/Player.h"
#include "../Object/Enemy/EnemyBase.h"
#include "../Object/Enemy/EnemyWizard.h"
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
		res.Load(ResourceManager::SRC::EnemyW).handleId_);

	// 攻撃エフェクト用のモデルのロード
	attackEffectModelIds_.emplace_back(
		res.Load(ResourceManager::SRC::EFFCT1).handleId_);

	sponCuntW_ = 0;
	sponDilay_ = 0;
}

void EnemyManager::Update(void)
{
	sponDilay_++;
	if (sponCuntW_ < MAX_W)
	{
		if (sponDilay_ > MAX_DILAY)
		{

			EnemyBase* enemy_ = new EnemyWizard();
			enemy_->Init(EnemyBase::TYPE::WIZARD,
				enemyModelIds_[static_cast<int>(EnemyBase::TYPE::WIZARD)], attackEffectModelIds_[static_cast<int>(ShotBase::TYPE::STRAIGHT)], player_);
			enemys_.push_back(enemy_);
			sponCuntW_++;
			sponDilay_ = 0;
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


#include <DxLib.h>

#include "../../Manager/EnemyManager.h"
#include "../../Object/Player/Player.h"
#include "../../Object/Enemy/EnemyBase.h"
#include "../../Object/Shot/ShotBase.h"

#include "Collision.h"

Collision::Collision()
{


}

Collision::~Collision()
{
}

void Collision::Init(Player* player, EnemyManager* enemyManager)
{
	player_ = player;
	enemyManager_ = enemyManager;

}

void Collision::Update(void)
{
	if (!player_->IsCollisionState())
	{
		return;
	}


	enemys_ = enemyManager_->GetEnemys();
	for (EnemyBase* enemy : enemys_)
	{
		if (!enemy->IsCollisionState())
		{
			continue;
		}

		shots_ = enemy->GetShot();
		for (ShotBase* shot : shots_)
		{
			if (HitSphere(player_->GetPos(), player_->GetCollisionRadius(), shot->GetPos(), shot->GetRadius()))
			{
				if (shot->IsAlive())
				{
					shot->SetIsAlive(false);
					player_->Hit(true);
				}
			}
		}

	}

	
	
}

bool Collision::HitSphere(VECTOR pos1, float radius1, VECTOR pos2, float radius2)
{
	VECTOR Hit;
	Hit.x = pos1.x - pos2.x;
	Hit.y = pos1.y - pos2.y;
	Hit.z = pos1.z - pos2.z;

	float dis =Hit.x * Hit.x + Hit.y * Hit.y + Hit.z * Hit.z;
	if (dis <= (radius1 + radius2) * (radius1 + radius2))
	{
		return true;
	}
	return false;
	
}

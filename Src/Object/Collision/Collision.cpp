
#include <DxLib.h>

#include "../../Manager/EnemyManager.h"
#include "../../Object/Player/Player.h"

#include "Collision.h"

Collision::Collision()
{
}

Collision::~Collision()
{
}

void Collision::Init(void)
{
}

void Collision::Update(void)
{
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

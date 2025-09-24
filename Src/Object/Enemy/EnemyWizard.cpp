#include "EnemyWizard.h"

EnemyWizard::EnemyWizard(void)
{
}

EnemyWizard::~EnemyWizard(void)
{
}

void EnemyWizard::SetParam(void)
{
	hp_ = 1;
	scales_ = { 0.5f, 0.5f, 0.5f };
	moveSpeed_ = 0.0f;
	spaen_ = 0.8f;

	collisionRadius_ = 40.0f;
	isAlive_ = true;
}

void EnemyWizard::UpdateStandby(void)
{
	LookPlayer();

	cntAttack_++;
	if (cntAttack_ > TERM_ATTACK)
	{
		cntAttack_ = 0;
		ChangeState(STATE::ATTACK);

	}
}

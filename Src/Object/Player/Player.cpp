#include <DxLib.h>
#include "../../Manager/InputManager.h"
#include "../../Manager/ResourceManager.h"
#include "Player.h"

Player::Player()
{

}
Player::~Player()
{

}
// 初期化
void Player::Init()
{
	// 初期ステイト
	state_ = STATE::STANDBY;
	ChangeState(state_);
	//モデル読み込み
	//model_ = ;
	// 初期位置
	pos_ = { 0.0f, 0.0f, 0.0f };
	// 初期回転
	rot_ = { 0.0f, 0.0f, 0.0f };
	// 初期大きさ
	scale_ = { 1.0f, 1.0f, 1.0f };
	
	// 初期体力
	hp_ = MAX_HP;
	// 初期スタミナ
	sp_ = MAX_SP;
	// 初期ガード
	gp_ = MAX_GP;
	
	MV1SetPosition(model_, pos_);
	MV1SetRotationXYZ(model_, rot_);
	MV1SetScale(model_, scale_);

}
// ステイトチェンジ
void Player::ChangeStandby()
{
}
void Player::ChangeMove()
{
}
void Player::ChangeAvoid()
{
}
void Player::ChangeGuard()
{
}
void Player::ChangeParry()
{
}
void Player::ChangeDamage()
{
}
void Player::ChangeDead()
{
}
// アプデ
void Player::Update()
{
	switch (state_)
	{
	case Player::STATE::STANDBY:
		StandbyUpdate();
		break;
	case Player::STATE::MOVE:
		MoveUpdate();
		break;
	case Player::STATE::AVOID:
		AvoidUpdate();
		break;
	case Player::STATE::GUARD:
		GuardUpdate();
		break;
	case Player::STATE::PARRY:
		ParryUpdate();
		break;
	case Player::STATE::DAMAGE:
		DamageUpdate();
		break;
	case Player::STATE::DEAD:
		DeadUpdate();
		break;
	default:
		break;
	}

}
// ステイトアプデ
void Player::StandbyUpdate()
{
}
void Player::MoveUpdate()
{
}
void Player::AvoidUpdate()
{
}
void Player::GuardUpdate()
{
}
void Player::ParryUpdate()
{
}
void Player::DamageUpdate()
{
}
void Player::DeadUpdate()
{
}
// ドロー
void Player::Draw()
{
	switch (state_)
	{
	case Player::STATE::STANDBY:
		StandbyDraw();
		break;
	case Player::STATE::MOVE:
		MoveDraw();
		break;
	case Player::STATE::AVOID:
		AvoidDraw();
		break;
	case Player::STATE::GUARD:
		GuardDraw();
		break;
	case Player::STATE::PARRY:
		ParryDraw();
		break;
	case Player::STATE::DAMAGE:
		DamageDraw();
		break;
	case Player::STATE::DEAD:
		DeadDraw();
		break;
	default:
		break;
	}

}
// ステイトドロー
void Player::StandbyDraw()
{
}

void Player::MoveDraw()
{
}

void Player::AvoidDraw()
{
}

void Player::GuardDraw()
{
}

void Player::ParryDraw()
{
}

void Player::DamageDraw()
{
}

void Player::DeadDraw()
{
}
// ステイトチェンジ
void Player::ChangeState(STATE state)
{
	state_ = state;
	switch (state_)
	{
	case Player::STATE::STANDBY:
		ChangeStandby();
		break;
	case Player::STATE::MOVE:
		ChangeMove();
		break;
	case Player::STATE::AVOID:
		ChangeAvoid();
		break;
	case Player::STATE::GUARD:
		ChangeGuard();
		break;
	case Player::STATE::PARRY:
		ChangeParry();
		break;
	case Player::STATE::DAMAGE:
		ChangeDamage();
		break;
	case Player::STATE::DEAD:
		ChangeDead();
		break;
	default:
		break;
	}
}

// ゲッターセッター
VECTOR Player::GetPos()
{
	return VECTOR();
}

void Player::SetPos(VECTOR pos)
{
}

int Player::GetHp()
{
	return 0;
}

void Player::SetHp(int hp)
{
}

int Player::GetSp()
{
	return 0;
}

void Player::SetSp(int sp)
{
}

int Player::GetGp()
{
	return 0;
}

void Player::SetGp(int gp)
{
}


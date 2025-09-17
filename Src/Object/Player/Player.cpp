#include <DxLib.h>
#include "../../Utility/AsoUtility.h"
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
	model_ = MV1LoadModel("Data/Model/Player/無題.mv1");
	// 初期位置
	pos_ = { 0.0f, 50.0f, 0.0f };
	// 初期回転
	rot_ = { 0.0f, 0.0f, 0.0f };
	// 初期大きさ
	scale_ = { 0.5f, 0.5f, 0.5f };
	
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

void Player::ChangeAvoid()
{
}
void Player::ChangeGuard()
{
}
void Player::ChangeParry()
{
	count_ = 0.0f;
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
	MV1SetPosition(model_, pos_);
	MV1SetRotationXYZ(model_, rot_);

}
// ステイトアプデ
void Player::StandbyUpdate()
{
	auto& ins = InputManager::GetInstance();
	Move();
	if (ins.IsTrgDown(KEY_INPUT_LSHIFT))
	{
		ChangeState(STATE::AVOID);
	}
	if (ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN))
	{
		ChangeState(STATE::AVOID);
	}
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		ChangeState(STATE::GUARD);
	}
	if (ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::R_TRIGGER))
	{
		ChangeState(STATE::GUARD);
	}

	
}

void Player::AvoidUpdate()
{
	rot_.x += AsoUtility::Deg2RadF(-20.0f);
	AvoidMove();
	
	if (rot_.x <= AsoUtility::Deg2RadF(-360.0f))
	{
		rot_.x = 0.0f;
		ChangeState(STATE::STANDBY);
	}
}

	
void Player::GuardUpdate()
{
	auto& ins = InputManager::GetInstance();
	HalfMove();
	if (ins.IsTrgUp(KEY_INPUT_SPACE))
	{
		ChangeState(STATE::PARRY);
	}
	if (ins.IsPadBtnTrgUp(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::R_TRIGGER))
	{
		ChangeState(STATE::PARRY);
	}
}
void Player::ParryUpdate()
{
	count_ += 0.5f;
	HalfMove();

	if (count_ >= MAX_COUNT)
	{
		ChangeState(STATE::STANDBY);
	}
	
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
	DrawSphere3D(pos_, 60, TEN + SIX, 0x0000ff, 0x0000ff, false);
}
// ステイトドロー
void Player::StandbyDraw()
{
	MV1DrawModel(model_);
}

void Player::AvoidDraw()
{
	MV1DrawModel(model_);
}

void Player::GuardDraw()
{
	DrawSphere3D(pos_, GUARD_RADIUS, TEN+SIX, 0x0000ff, 0x0000ff, false);
	MV1DrawModel(model_);
}

void Player::ParryDraw()
{
	DrawSphere3D(pos_, PARRY_RADIUS, TEN + SIX, 0x0000ff, 0x0000ff, false);
	MV1DrawModel(model_);
}

void Player::DamageDraw()
{
	MV1DrawModel(model_);
}

void Player::DeadDraw()
{
	MV1DrawModel(model_);
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



//機能＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
void Player::Move()
{
	InputManager& ins = InputManager::GetInstance();
	//
	VECTOR moveDir = AsoUtility::VECTOR_ZERO;
	if (ins.IsNew(KEY_INPUT_W)) { moveDir = VAdd(moveDir, AsoUtility::DIR_F); }
	if (ins.IsNew(KEY_INPUT_S)) { moveDir = VAdd(moveDir, AsoUtility::DIR_B); }
	if (ins.IsNew(KEY_INPUT_A)) { moveDir = VAdd(moveDir, AsoUtility::DIR_L); }
	if (ins.IsNew(KEY_INPUT_D)) { moveDir = VAdd(moveDir, AsoUtility::DIR_R); }
	if (ins.GetJPadInputState(InputManager::JOYPAD_NO::PAD1).AKeyLX < 0){moveDir = VAdd(moveDir, AsoUtility::DIR_L);}
	if (ins.GetJPadInputState(InputManager::JOYPAD_NO::PAD1).AKeyLX > 0){moveDir = VAdd(moveDir, AsoUtility::DIR_R);}
	if (ins.GetJPadInputState(InputManager::JOYPAD_NO::PAD1).AKeyLY < 0){moveDir = VAdd(moveDir, AsoUtility::DIR_F);}
	if (ins.GetJPadInputState(InputManager::JOYPAD_NO::PAD1).AKeyLY > 0){moveDir = VAdd(moveDir, AsoUtility::DIR_B);}

	if (!AsoUtility::EqualsVZero(moveDir))
	{
		
		moveDir = VNorm(moveDir);

		moveDir_ = moveDir;
		rot_.y = atan2(moveDir_.x, moveDir_.z) + DX_PI_F;

		//
		VECTOR movePos = VScale(moveDir_, MOVE_SPEED);
		//
		pos_ = VAdd(pos_, movePos);

		//angles_.y = AsoUtility::Deg2RadF(180.0f);
		MV1SetPosition(model_, pos_);

		MV1SetRotationXYZ(model_, rot_);
	}

}
void Player::HalfMove()
{
	InputManager& ins = InputManager::GetInstance();
	//
	VECTOR moveDir = AsoUtility::VECTOR_ZERO;
	if (ins.IsNew(KEY_INPUT_W)) { moveDir = VAdd(moveDir, AsoUtility::DIR_F); }
	if (ins.IsNew(KEY_INPUT_S)) { moveDir = VAdd(moveDir, AsoUtility::DIR_B); }
	if (ins.IsNew(KEY_INPUT_A)) { moveDir = VAdd(moveDir, AsoUtility::DIR_L); }
	if (ins.IsNew(KEY_INPUT_D)) { moveDir = VAdd(moveDir, AsoUtility::DIR_R); }
	if (ins.GetJPadInputState(InputManager::JOYPAD_NO::PAD1).AKeyLX < 0) { moveDir = VAdd(moveDir, AsoUtility::DIR_L); }
	if (ins.GetJPadInputState(InputManager::JOYPAD_NO::PAD1).AKeyLX > 0) { moveDir = VAdd(moveDir, AsoUtility::DIR_R); }
	if (ins.GetJPadInputState(InputManager::JOYPAD_NO::PAD1).AKeyLY < 0) { moveDir = VAdd(moveDir, AsoUtility::DIR_F); }
	if (ins.GetJPadInputState(InputManager::JOYPAD_NO::PAD1).AKeyLY > 0) { moveDir = VAdd(moveDir, AsoUtility::DIR_B); }

	if (!AsoUtility::EqualsVZero(moveDir))
	{

		moveDir = VNorm(moveDir);

		moveDir_ = moveDir;
		rot_.y = atan2(moveDir_.x, moveDir_.z) + DX_PI_F;

		//
		VECTOR movePos = VScale(moveDir_, MOVE_SPEED_HALF);
		//
		pos_ = VAdd(pos_, movePos);

		//angles_.y = AsoUtility::Deg2RadF(180.0f);
		MV1SetPosition(model_, pos_);

		MV1SetRotationXYZ(model_, rot_);
	}

}
void Player::AvoidMove()
{
	InputManager& ins = InputManager::GetInstance();
	//
	VECTOR moveDir = AsoUtility::VECTOR_ZERO;
	if (ins.IsNew(KEY_INPUT_W)) { moveDir = VAdd(moveDir, AsoUtility::DIR_F); }
	if (ins.IsNew(KEY_INPUT_S)) { moveDir = VAdd(moveDir, AsoUtility::DIR_B); }
	if (ins.IsNew(KEY_INPUT_A)) { moveDir = VAdd(moveDir, AsoUtility::DIR_L); }
	if (ins.IsNew(KEY_INPUT_D)) { moveDir = VAdd(moveDir, AsoUtility::DIR_R); }
	if (ins.GetJPadInputState(InputManager::JOYPAD_NO::PAD1).AKeyLX < 0) { moveDir = VAdd(moveDir, AsoUtility::DIR_L); }
	if (ins.GetJPadInputState(InputManager::JOYPAD_NO::PAD1).AKeyLX > 0) { moveDir = VAdd(moveDir, AsoUtility::DIR_R); }
	if (ins.GetJPadInputState(InputManager::JOYPAD_NO::PAD1).AKeyLY < 0) { moveDir = VAdd(moveDir, AsoUtility::DIR_F); }
	if (ins.GetJPadInputState(InputManager::JOYPAD_NO::PAD1).AKeyLY > 0) { moveDir = VAdd(moveDir, AsoUtility::DIR_B); }

	if (!AsoUtility::EqualsVZero(moveDir))
	{

		moveDir = VNorm(moveDir);

		moveDir_ = moveDir;
		rot_.y = atan2(moveDir_.x, moveDir_.z) + DX_PI_F;

		//
		VECTOR movePos = VScale(moveDir_, AVOID_SPEED);
		//
		pos_ = VAdd(pos_, movePos);

		//angles_.y = AsoUtility::Deg2RadF(180.0f);
		MV1SetPosition(model_, pos_);

		MV1SetRotationXYZ(model_, rot_);
	}

}
// ゲッターセッター＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
VECTOR Player::GetPos()
{
	return pos_;
}

void Player::SetPos(VECTOR pos)
{
	pos_ = pos;
}

int Player::GetHp()
{
	return hp_;
}

void Player::SetHp(int hp)
{
	hp_ = hp;
}

int Player::GetSp()
{
	return sp_;
}

void Player::SetSp(int sp)
{
	sp_ = sp;
}

int Player::GetGp()
{
	return gp_;
}

void Player::SetGp(int gp)
{
	gp_ = gp;
}


#include <DxLib.h>
#include "../../Utility/AsoUtility.h"
#include "../../Utility/MatrixUtility.h"
#include "../../Manager/InputManager.h"
#include "../../Manager/ResourceManager.h"
#include "../Camera/Camera.h"
#include "Player.h"

Player::Player()
{

}
Player::~Player()
{

}
// 初期化
void Player::Init(Camera* camera)
{

	camera_ = camera;

	// 初期ステイト
	state_ = STATE::STANDBY;
	ChangeState(state_);
	//モデル読み込み
	// 画像の読み込み
	ResourceManager& res = ResourceManager::GetInstance(); // リソースマネージャのインスタンス取得

	model_ = res.Load(ResourceManager::SRC::PlayerModel).handleId_;
	// 初期位置
	pos_ = { 0.0f, 50.0f, 0.0f };
	// 初期回転
	rot_ = { 0.0f, 0.0f, 0.0f };

	localrot_ = { 0.0f, AsoUtility::Deg2RadF(180.0f), 0.0f};
	// 初期大きさ
	scale_ = { 0.5f, 0.5f, 0.5f };

	// 初期体力
	hp_ = MAX_HP;
	// 初期スタミナ
	sp_ = MAX_SP;
	// 初期ガード
	gp_ = MAX_GP;

	MV1SetPosition(model_, pos_);
	MV1SetRotationMatrix(model_, MatrixUtility::Multiplication(localrot_, rot_));
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
	// 行列の合成(子, 親と指定すると親⇒子の順に適用される)
	MATRIX mat = MatrixUtility::Multiplication(localrot_, rot_);
	// 回転行列をモデルに反映
	MV1SetRotationMatrix(model_, mat);

}
// ステイトアプデ
void Player::StandbyUpdate()
{
	auto& ins = InputManager::GetInstance();
	Move();
	DelayRotate();
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
	rot_.x += AsoUtility::Deg2RadF(20.0f);
	AvoidMove();
	DelayRotate();
	if (rot_.x >= AsoUtility::Deg2RadF(360.0f))
	{
		rot_.x = 0.0f;
		ChangeState(STATE::STANDBY);
	}
}

	
void Player::GuardUpdate()
{
	auto& ins = InputManager::GetInstance();
	HalfMove();
	DelayRotate();
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
	DelayRotate();
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
	DrawSphere3D(pos_, DAMAGE_RADIUS,TEN + SIX, 0x0000ff, 0x0000ff, false);

	collisionRadius_= DAMAGE_RADIUS;
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
	collisionRadius_ = GUARD_RADIUS;
	MV1DrawModel(model_);
}

void Player::ParryDraw()
{
	DrawSphere3D(pos_, PARRY_RADIUS, TEN + SIX, 0x0000ff, 0x0000ff, false);
	collisionRadius_ = PARRY_RADIUS;
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
	VECTOR camPos = camera_->GetPos();
	VECTOR camAngles = camera_->GetAngles();


	auto& ins = InputManager::GetInstance();
	VECTOR dir = AsoUtility::VECTOR_ZERO;

	// ゲームパッドが接続数で処理を分ける
	if (GetJoypadNum() == 0)
	{
		// WASDで移動する
		if (ins.IsNew(KEY_INPUT_W)) { dir = { 0.0f, 0.0f, 1.0f }; }
		if (ins.IsNew(KEY_INPUT_A)) { dir = { -1.0f, 0.0f, 0.0f }; }
		if (ins.IsNew(KEY_INPUT_S)) { dir = { 0.0f, 0.0f, -1.0f }; }
		if (ins.IsNew(KEY_INPUT_D)) { dir = { 1.0f, 0.0f, 0.0f }; }
	}
	else
	{
		// 接続されているゲームパッド１の情報を取得
		InputManager::JOYPAD_IN_STATE padState =
			ins.GetJPadInputState(InputManager::JOYPAD_NO::PAD1);
		// アナログキーの入力値から方向を取得
		dir = ins.GetDirectionXZAKey(padState.AKeyLX, padState.AKeyLY);
	}


	if (!AsoUtility::EqualsVZero(dir))
	{
		// XYZの回転行列
	   // XZ平面移動にする場合は、XZの回転を考慮しないようにする
		MATRIX mat = MGetIdent();
		//mat = MMult(mat, MGetRotX(angles_.x));
		mat = MMult(mat, MGetRotY(camAngles.y));
		//mat = MMult(mat, MGetRotZ(angles_.z));
		// 回転行列を使用して、ベクトルを回転させる
		VECTOR moveDir = VTransform(dir, mat);

		// 回転行列を使用して、ベクトルを回転させる
		moveDir_ = VTransform(dir, mat);
		// 移動方向から角度に変換する
		//angles_.y = atan2f(moveDir_.x, moveDir_.z);
		// 方向×スピードで移動量を作って、座標に足して移動
		pos_ = VAdd(pos_, VScale(moveDir_, MOVE_SPEED));

		//animationController_->Play(static_cast<int>(ANIM_TYPE::WALK));


	}
	else
	{
		//animationController_->Play(static_cast<int>(ANIM_TYPE::IDLE));
	}

}
void Player::HalfMove()
{
	VECTOR camPos = camera_->GetPos();
	VECTOR camAngles = camera_->GetAngles();


	auto& ins = InputManager::GetInstance();
	VECTOR dir = AsoUtility::VECTOR_ZERO;

	// ゲームパッドが接続数で処理を分ける
	if (GetJoypadNum() == 0)
	{
		// WASDで移動する
		if (ins.IsNew(KEY_INPUT_W)) { dir = { 0.0f, 0.0f, 1.0f }; }
		if (ins.IsNew(KEY_INPUT_A)) { dir = { -1.0f, 0.0f, 0.0f }; }
		if (ins.IsNew(KEY_INPUT_S)) { dir = { 0.0f, 0.0f, -1.0f }; }
		if (ins.IsNew(KEY_INPUT_D)) { dir = { 1.0f, 0.0f, 0.0f }; }
	}
	else
	{
		// 接続されているゲームパッド１の情報を取得
		InputManager::JOYPAD_IN_STATE padState =
			ins.GetJPadInputState(InputManager::JOYPAD_NO::PAD1);
		// アナログキーの入力値から方向を取得
		dir = ins.GetDirectionXZAKey(padState.AKeyLX, padState.AKeyLY);
	}


	if (!AsoUtility::EqualsVZero(dir))
	{
		// XYZの回転行列
	   // XZ平面移動にする場合は、XZの回転を考慮しないようにする
		MATRIX mat = MGetIdent();
		//mat = MMult(mat, MGetRotX(angles_.x));
		mat = MMult(mat, MGetRotY(camAngles.y));
		//mat = MMult(mat, MGetRotZ(angles_.z));
		// 回転行列を使用して、ベクトルを回転させる
		VECTOR moveDir = VTransform(dir, mat);

		// 回転行列を使用して、ベクトルを回転させる
		moveDir_ = VTransform(dir, mat);
		// 移動方向から角度に変換する
		//angles_.y = atan2f(moveDir_.x, moveDir_.z);
		// 方向×スピードで移動量を作って、座標に足して移動
		pos_ = VAdd(pos_, VScale(moveDir_, MOVE_SPEED_HALF));

		//animationController_->Play(static_cast<int>(ANIM_TYPE::WALK));


	}
	else
	{
		//animationController_->Play(static_cast<int>(ANIM_TYPE::IDLE));
	}
}
void Player::AvoidMove()
{
	VECTOR camPos = camera_->GetPos();
	VECTOR camAngles = camera_->GetAngles();


	auto& ins = InputManager::GetInstance();
	VECTOR dir = AsoUtility::VECTOR_ZERO;

	// ゲームパッドが接続数で処理を分ける
	if (GetJoypadNum() == 0)
	{
		// WASDで移動する
		if (ins.IsNew(KEY_INPUT_W)) { dir = { 0.0f, 0.0f, 1.0f }; }
		if (ins.IsNew(KEY_INPUT_A)) { dir = { -1.0f, 0.0f, 0.0f }; }
		if (ins.IsNew(KEY_INPUT_S)) { dir = { 0.0f, 0.0f, -1.0f }; }
		if (ins.IsNew(KEY_INPUT_D)) { dir = { 1.0f, 0.0f, 0.0f }; }
	}
	else
	{
		// 接続されているゲームパッド１の情報を取得
		InputManager::JOYPAD_IN_STATE padState =
			ins.GetJPadInputState(InputManager::JOYPAD_NO::PAD1);
		// アナログキーの入力値から方向を取得
		dir = ins.GetDirectionXZAKey(padState.AKeyLX, padState.AKeyLY);
	}


	if (!AsoUtility::EqualsVZero(dir))
	{
		// XYZの回転行列
	   // XZ平面移動にする場合は、XZの回転を考慮しないようにする
		MATRIX mat = MGetIdent();
		//mat = MMult(mat, MGetRotX(angles_.x));
		mat = MMult(mat, MGetRotY(camAngles.y));
		//mat = MMult(mat, MGetRotZ(angles_.z));
		// 回転行列を使用して、ベクトルを回転させる
		VECTOR moveDir = VTransform(dir, mat);

		// 回転行列を使用して、ベクトルを回転させる
		moveDir_ = VTransform(dir, mat);
		// 移動方向から角度に変換する
		//angles_.y = atan2f(moveDir_.x, moveDir_.z);
		// 方向×スピードで移動量を作って、座標に足して移動
		pos_ = VAdd(pos_, VScale(moveDir_, AVOID_SPEED));

		//animationController_->Play(static_cast<int>(ANIM_TYPE::WALK));


	}
	else
	{
		//animationController_->Play(static_cast<int>(ANIM_TYPE::IDLE));
	}

}
bool Player::IsCollisionState(void)
{
	// プレイヤーの状態が衝突判定を行う状態かどうか
	if (state_ == STATE::STANDBY || state_ == STATE::AVOID||state_==STATE::GUARD||state_==STATE::PARRY)
	{
		return true;
	}
	return false;
}


void Player::DelayRotate(void)
{
	// 移動方向から角度に変換する
	float goal = atan2f(moveDir_.x, moveDir_.z);
	// 常に最短経路で補間
	rot_.y = AsoUtility::LerpAngle(rot_.y, goal, 0.2f);
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

float Player::GetCollisionRadius()
{
	return collisionRadius_;
}


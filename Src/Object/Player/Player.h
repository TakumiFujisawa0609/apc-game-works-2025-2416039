#pragma once

class Camera;

class Player
{
public:
	//ステートパターン=========================================================
	enum class STATE
	{
		STANDBY,
		AVOID,
		GUARD,
		PARRY,
		DAMAGE,
		DEAD,

	};


	
	//ナンバー=========================================================

	static constexpr int ONE = 1;
	static constexpr int TWO = 2;
	static constexpr int THREE = 3;
	static constexpr int FOUR = 4;
	static constexpr int FIVE = 5;
	static constexpr int SIX = 6;
	static constexpr int SEVEN = 7;
	static constexpr int EIGHT = 8;
	static constexpr int NINE = 9;
	static constexpr int TEN = 10;

	//定数=========================================================
	static constexpr float MOVE_SPEED = 10.0f; //移動速度
	static constexpr float MOVE_SPEED_HALF = 5.0f; //移動速度半分
	static constexpr float AVOID_SPEED = 30.0f; //回避速度

	static constexpr int MAX_HP = 100; //最大体力
	static constexpr int MAX_SP = 100; //最大スタミナ
	static constexpr int MAX_GP = 100; //最大ガード

	static constexpr float MAX_COUNT = 5.0f; //カウントの最大値
	
	static constexpr float DAMAGE_RADIUS = 60.0f;//ダメージ時の半径
	static constexpr float GUARD_RADIUS = 100.0f;//ガード時の半径
	static constexpr float PARRY_RADIUS = 120.0f;//パリィ時の半径


private:

	int model_;//モデル
	VECTOR pos_;//位置
	VECTOR rot_;//回転
	VECTOR localrot_;//ローカル回転
	VECTOR scale_;//大きさ
	STATE state_;//状態
	int hp_;//体力
	int sp_;//スタミナ
	int gp_;//ガード
	VECTOR moveDir_;//移動方向

	float count_;

	float collisionRadius_;//当たり判定用半径



	Camera* camera_;

public:
	Player();
	~Player();
	//初期化
	void Init(Camera*camera);
	//ステイトチェンジ
	void ChangeStandby();
	void ChangeAvoid();
	void ChangeGuard();
	void ChangeParry();
	void ChangeDamage();
	void ChangeDead();

	//アプデ
	void Update();
	//ステイトアプデ
	void StandbyUpdate();
	void AvoidUpdate();
	void GuardUpdate();
	void ParryUpdate();
	void DamageUpdate();
	void DeadUpdate();

	//ドロー
	void Draw();
	//ステイトドロー
	void StandbyDraw();
	void AvoidDraw();
	void GuardDraw();
	void ParryDraw();
	void DamageDraw();
	void DeadDraw();

	//ステイトチェンジ関数
	void ChangeState(STATE state);

	//機能
	void Move();
	void HalfMove();
	void AvoidMove();
	bool IsCollisionState(void);

	//ゲッターセッター
	VECTOR GetPos();
	void SetPos(VECTOR pos);
	int GetHp();
	void SetHp(int hp);
	int GetSp();
	void SetSp(int sp);
	int GetGp();
	void SetGp(int gp);

	float GetCollisionRadius();


	void DelayRotate();
};


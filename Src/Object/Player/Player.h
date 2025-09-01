#pragma once
class Player
{
public:
	//ステートパターン=========================================================
	enum class STATE
	{
		STANDBY,
		MOVE,
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
	static constexpr float MOVE_SPEED = 0.2f; //移動速度

	static constexpr int MAX_HP = 100; //最大体力
	static constexpr int MAX_SP = 100; //最大スタミナ
	static constexpr int MAX_GP = 100; //最大ガード




private:

	int model_;//モデル
	VECTOR pos_;//位置
	VECTOR rot_;//回転
	VECTOR scale_;//大きさ
	STATE state_;//状態
	int hp_;//体力
	int sp_;//スタミナ
	int gp_;//ガード





public:
	Player();
	~Player();
	void Init();
	//ステイトチェンジ
	void ChangeStandby();
	void ChangeMove();
	void ChangeAvoid();
	void ChangeGuard();
	void ChangeParry();
	void ChangeDamage();
	void ChangeDead();

	void Update();
	//ステイトアプデ
	void StandbyUpdate();
	void MoveUpdate();
	void AvoidUpdate();
	void GuardUpdate();
	void ParryUpdate();
	void DamageUpdate();
	void DeadUpdate();

	void Draw();
	//ステイトドロー
	void StandbyDraw();
	void MoveDraw();
	void AvoidDraw();
	void GuardDraw();
	void ParryDraw();
	void DamageDraw();
	void DeadDraw();

	void ChangeState(STATE state);

	//ゲッターセッター
	VECTOR GetPos();
	void SetPos(VECTOR pos);
	int GetHp();
	void SetHp(int hp);
	int GetSp();
	void SetSp(int sp);
	int GetGp();
	void SetGp(int gp);


};


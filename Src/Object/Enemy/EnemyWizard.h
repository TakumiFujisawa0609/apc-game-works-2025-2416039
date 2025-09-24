#pragma once
#include "EnemyBase.h"
class EnemyWizard : public EnemyBase
{
public:
	static constexpr int TERM_ATTACK = 120.0f;
	// コンストラクタ
	EnemyWizard(void);
	// デストラクタ
	~EnemyWizard(void);
private:

protected:
	// パラメータ設定
	void SetParam(void) override;

	void UpdateStandby(void) override;
};

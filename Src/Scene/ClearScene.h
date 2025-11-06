#pragma once

#include <vector>
#include "SceneBase.h"

class Timer;

class ClearScene : public SceneBase
{
public:
	static constexpr int MAX_COUNT = 5;
	// コンストラクタ
	ClearScene(Timer*timer);

	// デストラクタ
	~ClearScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	
private:
	int count_;

	Timer* timer_;
	
};


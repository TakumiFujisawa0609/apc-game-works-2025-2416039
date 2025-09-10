//#pragma once
#include "SceneBase.h"
#include "../Common/Vector2.h"
#include <vector>

class Player;
class Camera;
class Grid;

class GameScene : public SceneBase
{

public:
	
	// コンストラクタ
	GameScene(void);

	// デストラクタ
	~GameScene(void);

	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;

private:


	//カメラ
	Camera* camera_;

	//グリッド線
	Grid* grid_;

	//プレイヤー
	Player* player_;
	
};

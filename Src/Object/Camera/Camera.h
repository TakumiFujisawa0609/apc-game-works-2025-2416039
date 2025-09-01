#pragma once
#include <DxLib.h>
class Camera
{
public:
	// カメラモード
	enum class MODE
	{
		NONE,
		FIXED_POINT,
		FREE,
	};


	// カメラの初期位置
	static constexpr VECTOR DEFAULT_POS =
	{ 0.0f, 500.0f, -500.0f };
	// カメラの初期角度
	static constexpr VECTOR DEFAULT_ANGLES =
	{ 20.0f * DX_PI_F / 180.0f, 0.0f, 0.0f };
	// カメラクリップ：NEAR
	static constexpr float CAMERA_NEAR = 3.0f;
	// カメラクリップ：FAR
	static constexpr float CAMERA_FAR = 10000.0f;
	// コンストラクタ
	Camera(void);
	// デストラクタ
	~Camera(void);
	// 初期化
	void Init(void);
	// 更新
	void Update(void);
	// 描画前のカメラ設定
	void SetBeforeDraw(void);
	// デバッグ用描画
	void DrawDebug(void);
	// 解放
	void Release(void);

	
	// カメラモードの変更
	void ChangeMode(MODE mode);

private:
	// カメラの位置
	VECTOR pos_;
	// カメラの角度
	VECTOR angles_;

	// カメラモード
	MODE mode_;

	// カメラモード別の制御処理
	void SetBeforeDrawFixedPoint(void);
	void SetBeforeDrawFree(void);
};


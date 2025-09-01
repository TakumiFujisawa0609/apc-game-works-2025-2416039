#include <DxLib.h>
#include "../../Manager/SceneManager.h"
#include "AnimationController.h"
AnimationController::AnimationController(int modelId)
{
	modelId_ = modelId;
	playType_ = -1;
}
AnimationController::~AnimationController(void)
{
}
void AnimationController::Add(int type, float speed, const std::string path)
{
	Animation animation;
	animation.model = MV1LoadModel(path.c_str());
	animation.animIndex = -1;
	Add(type, speed, animation);
}
void AnimationController::AddInFbx(int type, float speed, int animIndex)
{
	Animation animation;
	animation.model = -1;
	animation.animIndex = animIndex;
	Add(type, speed, animation);
	
}


void AnimationController::Play(int type,bool isLoop)
{
	if (playType_ == type)
	{
		// 同じアニメーションだったら再生を継続する
		return;

	}


	if (playType_ != -1)
	{
		// モデルからアニメーションを外す
		MV1DetachAnim(modelId_, playAnim_.attachNo);

	}
	// アニメーション種別を変更
	playType_ = type;
	playAnim_ = animations_[type];
	// 初期化
	playAnim_.step = 0.0f;

	// モデルと同じファイルからアニメーションをアタッチする
	playAnim_.attachNo = MV1AttachAnim(modelId_, playAnim_.animIndex);
	// アニメーション総時間の取得
	totalTime_ = MV1GetAttachAnimTotalTime(modelId_, playAnim_.attachNo);

	isLoop_= isLoop;
}


void AnimationController::Add(int type, float speed, Animation& animation)
{
	animation.speed = speed;

	if (animations_.count(type) == 0)
	{
		animations_.emplace(type, animation);
	}



}
void AnimationController::Update(void)
{
	// 経過時間の取得
	float deltaTime = SceneManager::GetInstance().GetDeltaTime();
	// 再生
	playAnim_.step += (deltaTime * playAnim_.speed);

	// アニメーションのループ処理
	if (playAnim_.step >totalTime_)
	{
		if (isLoop_)
		{
			playAnim_.step = 0.0f;
		}
		else
		{
			playAnim_.step = totalTime_;
		}
	}

	// アニメーション設定
	MV1SetAttachAnimTime(modelId_, playAnim_.attachNo, playAnim_.step);
}
	
void AnimationController::Release(void)
{
	for (const std::pair<int, Animation>& pair : animations_)
	{
		if (pair.second.model != -1)
		{
			MV1DeleteModel(pair.second.model);
		}
	}
	animations_.clear();
}

bool AnimationController::IsEnd(void)
{
	bool ret = false;
	if (isLoop_)
	{
		return ret;
	}
	if (playAnim_.step >= totalTime_)
	{
		return true;
	}
	return ret;
}
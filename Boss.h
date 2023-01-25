#pragma once
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "BossBullet.h"
#include "Input.h"

class TestTarget;

class Boss
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="textureHandle">テクスチャ</param>
	void Initialize(Model* model, Model* modelBullet);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="viewProjection"></param>
	void Draw(ViewProjection& viewProjection);

	//各所関数
	void Shoot();

	void SetTestTarget(TestTarget* testtarget) {
		testTarget_ = testtarget;
	}

	Vector3 GetWorldPosition();

	void Collision();

	const std::list<std::unique_ptr<BossBullet>>& GetBullets() { return bullets_; }
private:
	WorldTransform worldTransform_;

	Model* model_ = nullptr;
	Model* modelBullet_ = nullptr;

	uint32_t textureHandle_ = 0;

	Input* input_;

	DebugText* debugText_;

	Vector3 velocity;
	Vector3 velocity2;
	Vector3 velocity3;
	Vector3 velocity4;

	std::list<std::unique_ptr<BossBullet>> bullets_;
	int shootTimer = 60 * 1;

	TestTarget* testTarget_ = nullptr;

	float Damage;

#pragma region フェーズ用関数

	void FirstPhase();

	void SecondPhase();

	void ThirdPhase();

#pragma endregion

	// 行動フェーズ
	enum class Phase
	{
		First,	//	第一形態
		Second,	//	第二形態
		Third,	//	第三形態
	};

	// フェーズ
	Phase phase_ = Phase::First;
};

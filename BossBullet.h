#pragma once
#include "WorldTransform.h"
#include "Model.h"

class BossBullet
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="position">初期位置</param>
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);

	/// <summary>
	///更新 
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="viewProjection"></param>
	void Draw(const ViewProjection& viewProjection);

	bool IsDead() const {
		return isDead_;
	}

	Vector3 GetWorldPosition();

	void Collision();
private:

	WorldTransform worldTransform_;

	Model* model_ = nullptr;

	uint32_t textureHandle_ = 0;

	Vector3 velocity_;


	static const int32_t kLifeTime = 60 * 5;

	int32_t deathTimer_ = kLifeTime;

	bool isDead_ = false;
};

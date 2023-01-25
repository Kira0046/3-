#include "BossBullet.h"
#include <cassert>
#include "Procession.h"

using namespace MathUtility;

void BossBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity)
{
	assert(model);

	model_ = model;
	velocity_ = velocity;
	//スケール
	worldTransform_.scale_ = { 1.0f,1.0f,1.0f };

	//回転
	worldTransform_.rotation_ = { 0, 0, 0 };

	//位置
	worldTransform_.translation_ = { 0,0,0 };

	worldTransform_.Initialize();

	// 行列更新
	worldTransform_.matWorld_ = Mat_Identity();
	worldTransform_.matWorld_ = MatWorld(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	worldTransform_.TransferMatrix();

	worldTransform_.translation_ = position;
}

void BossBullet::Update()
{
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}

	worldTransform_.translation_ += velocity_;

	// 行列更新
	worldTransform_.matWorld_ = Mat_Identity();
	worldTransform_.matWorld_ = MatWorld(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	worldTransform_.TransferMatrix();

}

void BossBullet::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection);
}



Vector3 BossBullet::GetWorldPosition()
{
	Vector3 worldPos;

	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}

void BossBullet ::Collision()
{
	isDead_ = true;
}

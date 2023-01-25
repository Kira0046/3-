#include "TestTarget.h"
#include <cassert>

using namespace MathUtility;

void TestTarget::Initialize(Model* model, uint32_t textureHandle)
{
	assert(model);

	model_ = model;
	textureHandle_ = textureHandle;

	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();


	worldTransform_.Initialize();

	InitializeTransform();
}

void TestTarget::InitializeTransform()
{
	//スケール
	worldTransform_.scale_ = scale;

	Matrix4 matScale;

	matScale = Matrix4Identity();
	matScale.m[0][0] = worldTransform_.scale_.x;
	matScale.m[1][1] = worldTransform_.scale_.y;
	matScale.m[2][2] = worldTransform_.scale_.z;

	worldTransform_.matWorld_ = Matrix4Identity();
	worldTransform_.matWorld_ *= matScale;

	worldTransform_.TransferMatrix();

	//回転
	worldTransform_.rotation_ = rotation;

	Matrix4 matRot;
	Matrix4 matRotZ;
	Matrix4 matRotX;
	Matrix4 matRotY;

	matRotZ = Matrix4Identity();
	matRotX = Matrix4Identity();
	matRotY = Matrix4Identity();

	matRotZ.m[0][0] = cos(worldTransform_.rotation_.z);
	matRotZ.m[0][1] = sin(worldTransform_.rotation_.z);
	matRotZ.m[1][0] = -sin(worldTransform_.rotation_.z);
	matRotZ.m[1][1] = cos(worldTransform_.rotation_.z);

	matRotX.m[1][1] = cos(worldTransform_.rotation_.x);
	matRotX.m[1][2] = sin(worldTransform_.rotation_.x);
	matRotX.m[2][1] = -sin(worldTransform_.rotation_.x);
	matRotX.m[2][2] = cos(worldTransform_.rotation_.x);

	matRotY.m[0][0] = cos(worldTransform_.rotation_.y);
	matRotY.m[0][2] = sin(worldTransform_.rotation_.y);
	matRotY.m[2][0] = -sin(worldTransform_.rotation_.y);
	matRotY.m[2][2] = cos(worldTransform_.rotation_.y);

	matRot = matRotZ * matRotX * matRotY;

	worldTransform_.matWorld_ = Matrix4Identity();
	worldTransform_.matWorld_ *= matRotZ;
	worldTransform_.matWorld_ *= matRotX;
	worldTransform_.matWorld_ *= matRotY;

	worldTransform_.TransferMatrix();

	//位置
	worldTransform_.translation_ = translation;

	Matrix4 matTrans = Matrix4Identity();

	matTrans.m[3][0] = worldTransform_.translation_.x;
	matTrans.m[3][1] = worldTransform_.translation_.y;
	matTrans.m[3][2] = worldTransform_.translation_.z;

	worldTransform_.matWorld_ = Matrix4Identity();
	worldTransform_.matWorld_ *= matTrans;

	worldTransform_.matWorld_ = matScale * matRot * matTrans;
	worldTransform_.TransferMatrix();
}

void TestTarget::Update()
{
	if (input_->PushKey(DIK_UPARROW)) {
		worldTransform_.translation_.y += 1;
	}
	if (input_->PushKey(DIK_DOWNARROW)) {
		worldTransform_.translation_.y -= 1;
	}
	if (input_->PushKey(DIK_LEFTARROW)) {
		worldTransform_.translation_.x -= 1;
	}
	if (input_->PushKey(DIK_RIGHTARROW)) {
		worldTransform_.translation_.x += 1;
	}
	

	UpdateTransform();
}

void TestTarget::Draw(ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

}

void TestTarget::UpdateTransform()
{
	Matrix4 matScale;

	matScale = MathUtility::Matrix4Identity();
	matScale.m[0][0] = worldTransform_.scale_.x;
	matScale.m[1][1] = worldTransform_.scale_.y;
	matScale.m[2][2] = worldTransform_.scale_.z;

	worldTransform_.matWorld_ = MathUtility::Matrix4Identity();
	worldTransform_.matWorld_ *= matScale;

	Matrix4 matRot;
	Matrix4 matRotZ;
	Matrix4 matRotX;
	Matrix4 matRotY;

	matRotZ = MathUtility::Matrix4Identity();
	matRotX = MathUtility::Matrix4Identity();
	matRotY = MathUtility::Matrix4Identity();

	matRotZ.m[0][0] = cos(worldTransform_.rotation_.z);
	matRotZ.m[0][1] = sin(worldTransform_.rotation_.z);
	matRotZ.m[1][0] = -sin(worldTransform_.rotation_.z);
	matRotZ.m[1][1] = cos(worldTransform_.rotation_.z);

	matRotX.m[1][1] = cos(worldTransform_.rotation_.x);
	matRotX.m[1][2] = sin(worldTransform_.rotation_.x);
	matRotX.m[2][1] = -sin(worldTransform_.rotation_.x);
	matRotX.m[2][2] = cos(worldTransform_.rotation_.x);

	matRotY.m[0][0] = cos(worldTransform_.rotation_.y);
	matRotY.m[0][2] = sin(worldTransform_.rotation_.y);
	matRotY.m[2][0] = -sin(worldTransform_.rotation_.y);
	matRotY.m[2][2] = cos(worldTransform_.rotation_.y);

	matRot = matRotZ * matRotX * matRotY;

	worldTransform_.matWorld_ = MathUtility::Matrix4Identity();
	worldTransform_.matWorld_ *= matRotZ;
	worldTransform_.matWorld_ *= matRotX;
	worldTransform_.matWorld_ *= matRotY;

	Matrix4 matTrans = MathUtility::Matrix4Identity();

	matTrans.m[3][0] = worldTransform_.translation_.x;
	matTrans.m[3][1] = worldTransform_.translation_.y;
	matTrans.m[3][2] = worldTransform_.translation_.z;

	worldTransform_.matWorld_ = MathUtility::Matrix4Identity();
	worldTransform_.matWorld_ *= matTrans;

	worldTransform_.matWorld_ = matScale * matRot * matTrans;

	worldTransform_.TransferMatrix();
}

Vector3 TestTarget::GetWorldPosition()
{
	Vector3 worldPos;

	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}

void TestTarget::Collision()
{
}

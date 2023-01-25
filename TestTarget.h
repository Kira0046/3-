#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include "Input.h"
#include "DebugText.h"

class TestTarget
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="textureHandle">テクスチャ</param>
	void Initialize(Model* model, uint32_t textureHandle);

	void InitializeTransform();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="viewProjection"></param>
	void Draw(ViewProjection& viewProjection);

	void UpdateTransform();

	//各所関数
	Vector3 GetWorldPosition();

	void Collision();
	
private:
	WorldTransform worldTransform_;
	Vector3 scale = { 1.0f,1.0f,1.0f };
	Vector3 rotation = { 0,0,0 };
	Vector3 translation = { 0,0,0 };
	

	Model* model_ = nullptr;

	uint32_t textureHandle_ = 0;

	Input* input_;

	DebugText* debugText_;
};


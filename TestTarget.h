#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include "Input.h"
#include "DebugText.h"

class TestTarget
{
public:
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="model">���f��</param>
	/// <param name="textureHandle">�e�N�X�`��</param>
	void Initialize(Model* model, uint32_t textureHandle);

	void InitializeTransform();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="viewProjection"></param>
	void Draw(ViewProjection& viewProjection);

	void UpdateTransform();

	//�e���֐�
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


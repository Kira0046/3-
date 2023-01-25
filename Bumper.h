#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

/// <summary>
/// �Q�[���V�[��
/// </summary>
class Bumper {


public: // �����o�֐�
	/// <summary>
	/// �R���X�g�N���^
	/// </summary>
	Bumper();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Bumper();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(ViewProjection& viewProjection);
private: // �����o�ϐ�
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;

	/// <summary>
	/// �Q�[���V�[���p
	/// </summary>

	void BumperInitialize();
	void BumperMove();
	void BumperArmInitialize();
	void BumperArmMove();



	Model* modelBumper_ = nullptr;
	Model* modelBumperArmL_ = nullptr;
	Model* modelBumperArmR_ = nullptr;


	uint32_t textureHandleBumper_ = 0;
	uint32_t textureHandleBumperArmL_ = 0;
	uint32_t textureHandleBumperArmR_ = 0;



	WorldTransform worldTransformBumper_ = {};
	WorldTransform worldTransformBumperArmL_ = {};
	WorldTransform worldTransformBumperArmR_ = {};

	


};


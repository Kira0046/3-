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
	/// ������
	/// </summary>
	/// <param name="model">���f��</param>
	/// <param name="textureHandle">�e�N�X�`��</param>
	void Initialize(Model* model, Model* modelBullet);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="viewProjection"></param>
	void Draw(ViewProjection& viewProjection);

	//�e���֐�
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

#pragma region �t�F�[�Y�p�֐�

	void FirstPhase();

	void SecondPhase();

	void ThirdPhase();

#pragma endregion

	// �s���t�F�[�Y
	enum class Phase
	{
		First,	//	���`��
		Second,	//	���`��
		Third,	//	��O�`��
	};

	// �t�F�[�Y
	Phase phase_ = Phase::First;
};

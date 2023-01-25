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
/// ゲームシーン
/// </summary>
class Bumper {


public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	Bumper();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Bumper();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ViewProjection& viewProjection);
private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;

	/// <summary>
	/// ゲームシーン用
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


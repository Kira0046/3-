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

#include "Boss.h"
#include "TestTarget.h"
#include "Dome.h"
#include "Bumper.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

  public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

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
	void Draw();

	void CheckCollision();

	void CollisionTargetBullet();

	void TitleUpdate();
	void Title2D();
	
	void PlayUpdate();
	void Play2D();
	void Play3D();

	void ClearUpdate();
	void Clear2D();

	void OverUpdate();
	void Over2D();


  private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	
	TestTarget* testTarget_ = nullptr;
	Boss* boss_ = nullptr;
	Skydome* skydome_ = nullptr;
	Bumper* bumper_ = nullptr;

	Model* modelTestTarget_ = nullptr;
	uint32_t textureHandleTestTarget_ = 0;

	Model* modelBoss_ = nullptr;
	uint32_t textureHandleBoss_ = 0;

	Model* modelBossBullet_=nullptr;
	uint32_t textureHandleBossBullet = 0;

	Model* modelSkyDome_ = nullptr;

	ViewProjection viewProjection_;

	//サウンド
	uint32_t soundDataGameTitleBGM = 0;
	uint32_t soundDataGamePlayBGM = 0;
	uint32_t soundDataGameClearBGM = 0;
	uint32_t soundDataGameOverBGM = 0;
	uint32_t BGMHandle = 0;

	//シーン
	int scene_ = 0;
	int TitleCount = 0;

};

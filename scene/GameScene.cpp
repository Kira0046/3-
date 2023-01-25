#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete modelBossBullet_;
	delete modelBoss_;
	delete modelSkyDome_;
	delete modelTestTarget_;
	delete testTarget_;
	delete boss_;
	delete skydome_;
	delete bumper_;
}

void GameScene::Initialize() {
	testTarget_ = new TestTarget();
	boss_ = new Boss();
	skydome_ = new Skydome();
	bumper_ = new Bumper();

	boss_->SetTestTarget(testTarget_);

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	modelBoss_ = Model::CreateFromOBJ("Imazin");
	//textureHandleBoss_ = TextureManager::Load("BossBullet.png");

	modelBossBullet_ = Model::CreateFromOBJ("BossBullet");

	modelTestTarget_ = Model::Create();
	textureHandleTestTarget_ = TextureManager::Load("BossBullet/BossBullet.png");

	modelSkyDome_ = Model::CreateFromOBJ("world");

	boss_->Initialize(modelBoss_, modelBossBullet_);
	testTarget_->Initialize(modelTestTarget_,textureHandleTestTarget_);
	skydome_->Initialize(modelSkyDome_);
	bumper_->Initialize();


	viewProjection_.Initialize();
}

void GameScene::Update() {
	CheckCollision();


	boss_->Update();
	testTarget_->Update();
	bumper_->Update();
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	boss_->Draw(viewProjection_);
	testTarget_->Draw(viewProjection_);
	skydome_->Draw(viewProjection_);
	bumper_->Draw();
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::CheckCollision()
{
	CollisionTargetBullet();
}

void GameScene::CollisionTargetBullet()
{
	Vector3 posA, posB;

	const std::list<std::unique_ptr<BossBullet>>& bossBullets = boss_->GetBullets();

	posA = testTarget_->GetWorldPosition();

	for (const std::unique_ptr<BossBullet>& bullet : bossBullets) {
		posB = bullet->GetWorldPosition();
		
		if (
			(posA.x - posB.x) * (posA.x - posB.x) +
			(posA.y - posB.y) * (posA.y - posB.y) +
			(posA.z - posB.z) * (posA.z - posB.z)
			<= (1.0f + 1.0f) * (1.0f + 1.0f)
			) {
			bullet->Collision();
		}
	}
}

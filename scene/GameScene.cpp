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

	soundDataGameTitleBGM = audio_->LoadWave("bgm/title.wav");
	soundDataGamePlayBGM = audio_->LoadWave("bgm/play.wav");
	soundDataGameClearBGM = audio_->LoadWave("bgm/clear.wav");
	soundDataGameOverBGM = audio_->LoadWave("bgm/over.wav");

	BGMHandle = audio_->PlayWave(soundDataGameTitleBGM, true);

	viewProjection_.eye = { 0,0,-6 };
	viewProjection_.target = { 0,1,0 };
	viewProjection_.Initialize();
}

void GameScene::Update() {
	


	/*if (BGMChange == 0) {
		if (input_->TriggerKey(DIK_P)) {
			if (BGMChange == 0) {
				audio_->StopWave(BGMHandle);
				BGMHandle = audio_->PlayWave(soundDataGamePlayBGM, true);
				BGMChange = 1;
			}
		}
	}

	if (BGMChange == 1) {
		if (input_->TriggerKey(DIK_P)) {
			if (BGMChange == 1) {
				audio_->StopWave(BGMHandle);
				BGMHandle = audio_->PlayWave(soundDataGameClearBGM, true);
				BGMChange = 2;
			}
		}
	}

	if (BGMChange == 2) {
		if (input_->TriggerKey(DIK_P)) {
			if (BGMChange == 2) {
				audio_->StopWave(BGMHandle);
				BGMHandle = audio_->PlayWave(soundDataGameTitleBGM, true);
				BGMChange = 0;
			}
		}
	}*/

	switch (scene_) {
	case 0:
		TitleUpdate();
		break;
	case 1:
		PlayUpdate();
		break;
	case 2:
		ClearUpdate();
		break;
	case 3:
		OverUpdate();
		break;
	}

	
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
	
	switch (scene_)
	{
	case 0:
		Title2D();
		break;
	case 1:
		Play2D();
		break;
	case 2:
		Clear2D();
	case 3:
		Over2D();
		break;
	}

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
	
	switch (scene_)
	{
	case 1:
		Play3D();
		break;
	}

	
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

void GameScene::TitleUpdate()
{
	if (input_->TriggerKey(DIK_RETURN)) {
		TitleCount += 1;

		if (TitleCount > 1) {
			audio_->StopWave(BGMHandle);
			BGMHandle = audio_->PlayWave(soundDataGamePlayBGM, true);
			scene_ = 1;
		}
	}
}

void GameScene::Title2D()
{
}

void GameScene::PlayUpdate()
{
	CheckCollision();
	boss_->Update();
	testTarget_->Update();
	bumper_->Update();
}

void GameScene::Play2D()
{
}

void GameScene::Play3D()
{
	boss_->Draw(viewProjection_);
	testTarget_->Draw(viewProjection_);
	skydome_->Draw(viewProjection_);
	bumper_->Draw(viewProjection_);
}

void GameScene::ClearUpdate()
{
}

void GameScene::Clear2D()
{
}

void GameScene::OverUpdate()
{
}

void GameScene::Over2D()
{
}


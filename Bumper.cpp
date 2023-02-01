#include "Bumper.h"
#include "TextureManager.h"
#include <cassert>
using namespace MathUtility;


Bumper::Bumper() {}

Bumper::~Bumper() {
	delete modelBumper_;
	delete modelBumperArmL_;
	delete modelBumperArmR_;

}

void Bumper::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	textureHandleBumper_ = TextureManager::Load("blocktest.png");
	textureHandleBumperArmL_ = TextureManager::Load("blocktest.png");
	textureHandleBumperArmR_ = TextureManager::Load("blocktest.png");



	modelBumper_ = Model::Create();
	modelBumperArmL_ = Model::Create();
	modelBumperArmR_ = Model::Create();

	//バンパー
	BumperInitialize();
	//バンパーアーム
	BumperArmInitialize();

	//////////////////////////////////////////////////////////////////:カメラ

	//viewProjection_.eye = { 0,0,-6 };
	//viewProjection_.target = { 0,1,0 };
	//viewProjection_.Initialize();
}

void Bumper::Update()
{
	if (Fase == 0) {

		if (input_->PushKey(DIK_SPACE))
		{
			if (Fase == 0) {
				Fase = 1;
			}

		}

		if (input_->PushKey(DIK_A))
		{
			worldTransformBumper_.translation_.x -= armspeed;
			worldTransformBumperArmL_.translation_.x -= armspeed;
			worldTransformBumperArmR_.translation_.x -= armspeed;
		}

		if (input_->PushKey(DIK_D))
		{
			worldTransformBumper_.translation_.x += armspeed;
			worldTransformBumperArmL_.translation_.x += armspeed;
			worldTransformBumperArmR_.translation_.x += armspeed;
		}

		if (input_->PushKey(DIK_S))
		{
			worldTransformBumper_.translation_.z -= armspeed;
			worldTransformBumperArmL_.translation_.z -= armspeed;
			worldTransformBumperArmR_.translation_.z -= armspeed;
		}

		if (input_->PushKey(DIK_W))
		{
			worldTransformBumper_.translation_.z += armspeed;
			worldTransformBumperArmL_.translation_.z += armspeed;
			worldTransformBumperArmR_.translation_.z += armspeed;
		}
	}


	//降下中
	if (Fase == 1) {
		FallTime -= 1;
		worldTransformBumper_.translation_.y -= armspeed;
		worldTransformBumperArmL_.translation_.y -= armspeed;
		worldTransformBumperArmR_.translation_.y -= armspeed;
		if (FallTime < 0) {
			shutspeed = 0.5f;
			Fase = 2;
			FallTime = Fallsecond * 60;
		}
	}

	//アームが閉まる
	if (Fase == 2) {
		worldTransformBumperArmL_.translation_.x += shutspeed;
		worldTransformBumperArmR_.translation_.x -= shutspeed;
		if (fabs(worldTransformBumperArmL_.translation_.x - worldTransformBumperArmR_.translation_.x) < 1.0f) {
			shutspeed = 0;
			Fase = 3;
		}
	}

	//上昇後再び待機
	if (Fase == 3) {
		FallTime -= 1;
		worldTransformBumper_.translation_.y += armspeed;
		worldTransformBumperArmL_.translation_.y += armspeed;
		worldTransformBumperArmR_.translation_.y += armspeed;
		if (FallTime < 0) {
			armspeed = 0;
			shutspeed = 0.5f;
			worldTransformBumperArmL_.translation_.x -= shutspeed;
			worldTransformBumperArmR_.translation_.x += shutspeed;
			if (fabs(worldTransformBumper_.translation_.x - worldTransformBumperArmL_.translation_.x) > 1.3f) {
				worldTransformBumperArmL_.translation_.x = worldTransformBumper_.translation_.x - 1.3f;
				worldTransformBumperArmR_.translation_.x = worldTransformBumper_.translation_.x + 1.3f;

				Fase = 0;
				FallTime = Fallsecond * 60;
				armspeed = 0.5f;
			}
		}
	}


	BumperMove();
	BumperArmMove();
	

}

void Bumper::Draw(ViewProjection& viewProjection)
{

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	modelBumper_->Draw(worldTransformBumper_, viewProjection, textureHandleBumper_);

	modelBumperArmL_->Draw(worldTransformBumperArmL_, viewProjection, textureHandleBumperArmL_);

	modelBumperArmR_->Draw(worldTransformBumperArmR_, viewProjection, textureHandleBumperArmR_);

}






void Bumper::BumperInitialize() {

	worldTransformBumper_.Initialize();

	//スケール                 
	worldTransformBumper_.scale_ = { 1.0f,12.5f,1.0f };

	Matrix4 matScaleL;

	matScaleL = MathUtility::Matrix4Identity();
	matScaleL.m[0][0] = worldTransformBumper_.scale_.x;
	matScaleL.m[1][1] = worldTransformBumper_.scale_.y;
	matScaleL.m[2][2] = worldTransformBumper_.scale_.z;

	worldTransformBumper_.matWorld_ = MathUtility::Matrix4Identity();
	worldTransformBumper_.matWorld_ *= matScaleL;

	worldTransformBumper_.TransferMatrix();

	//回転
	worldTransformBumper_.rotation_ = { 0,0,0 };

	Matrix4 matRotL;
	Matrix4 matRotZL;
	Matrix4 matRotXL;
	Matrix4 matRotYL;

	matRotZL = MathUtility::Matrix4Identity();
	matRotXL = MathUtility::Matrix4Identity();
	matRotYL = MathUtility::Matrix4Identity();

	matRotZL.m[0][0] = cos(worldTransformBumper_.rotation_.z);
	matRotZL.m[0][1] = sin(worldTransformBumper_.rotation_.z);
	matRotZL.m[1][0] = -sin(worldTransformBumper_.rotation_.z);
	matRotZL.m[1][1] = cos(worldTransformBumper_.rotation_.z);

	matRotXL.m[1][1] = cos(worldTransformBumper_.rotation_.x);
	matRotXL.m[1][2] = sin(worldTransformBumper_.rotation_.x);
	matRotXL.m[2][1] = -sin(worldTransformBumper_.rotation_.x);
	matRotXL.m[2][2] = cos(worldTransformBumper_.rotation_.x);

	matRotYL.m[0][0] = cos(worldTransformBumper_.rotation_.y);
	matRotYL.m[0][2] = sin(worldTransformBumper_.rotation_.y);
	matRotYL.m[2][0] = -sin(worldTransformBumper_.rotation_.y);
	matRotYL.m[2][2] = cos(worldTransformBumper_.rotation_.y);

	matRotL = matRotZL * matRotXL * matRotYL;

	worldTransformBumper_.matWorld_ = MathUtility::Matrix4Identity();
	worldTransformBumper_.matWorld_ *= matRotZL;
	worldTransformBumper_.matWorld_ *= matRotXL;
	worldTransformBumper_.matWorld_ *= matRotYL;

	worldTransformBumper_.TransferMatrix();

	//位置
	worldTransformBumper_.translation_ = { 0.0f,22.0f,10.0f };

	Matrix4 matTransL = MathUtility::Matrix4Identity();

	matTransL.m[3][0] = worldTransformBumper_.translation_.x;
	matTransL.m[3][1] = worldTransformBumper_.translation_.y;
	matTransL.m[3][2] = worldTransformBumper_.translation_.z;

	worldTransformBumper_.matWorld_ = MathUtility::Matrix4Identity();
	worldTransformBumper_.matWorld_ *= matTransL;

	worldTransformBumper_.matWorld_ = matScaleL * matRotL * matTransL;
	worldTransformBumper_.TransferMatrix();

}

void Bumper::BumperMove() {

	Matrix4 matScaleL;

	matScaleL = MathUtility::Matrix4Identity();
	matScaleL.m[0][0] = worldTransformBumper_.scale_.x;
	matScaleL.m[1][1] = worldTransformBumper_.scale_.y;
	matScaleL.m[2][2] = worldTransformBumper_.scale_.z;

	worldTransformBumper_.matWorld_ = MathUtility::Matrix4Identity();
	worldTransformBumper_.matWorld_ *= matScaleL;

	Matrix4 matRotL;
	Matrix4 matRotZL;
	Matrix4 matRotXL;
	Matrix4 matRotYL;

	matRotZL = MathUtility::Matrix4Identity();
	matRotXL = MathUtility::Matrix4Identity();
	matRotYL = MathUtility::Matrix4Identity();

	matRotZL.m[0][0] = cos(worldTransformBumper_.rotation_.z);
	matRotZL.m[0][1] = sin(worldTransformBumper_.rotation_.z);
	matRotZL.m[1][0] = -sin(worldTransformBumper_.rotation_.z);
	matRotZL.m[1][1] = cos(worldTransformBumper_.rotation_.z);

	matRotXL.m[1][1] = cos(worldTransformBumper_.rotation_.x);
	matRotXL.m[1][2] = sin(worldTransformBumper_.rotation_.x);
	matRotXL.m[2][1] = -sin(worldTransformBumper_.rotation_.x);
	matRotXL.m[2][2] = cos(worldTransformBumper_.rotation_.x);

	matRotYL.m[0][0] = cos(worldTransformBumper_.rotation_.y);
	matRotYL.m[0][2] = sin(worldTransformBumper_.rotation_.y);
	matRotYL.m[2][0] = -sin(worldTransformBumper_.rotation_.y);
	matRotYL.m[2][2] = cos(worldTransformBumper_.rotation_.y);

	matRotL = matRotZL * matRotXL * matRotYL;

	worldTransformBumper_.matWorld_ = MathUtility::Matrix4Identity();
	worldTransformBumper_.matWorld_ *= matRotZL;
	worldTransformBumper_.matWorld_ *= matRotXL;
	worldTransformBumper_.matWorld_ *= matRotYL;

	Matrix4 matTransL = MathUtility::Matrix4Identity();

	matTransL.m[3][0] = worldTransformBumper_.translation_.x;
	matTransL.m[3][1] = worldTransformBumper_.translation_.y;
	matTransL.m[3][2] = worldTransformBumper_.translation_.z;

	worldTransformBumper_.matWorld_ = MathUtility::Matrix4Identity();
	worldTransformBumper_.matWorld_ *= matTransL;

	worldTransformBumper_.matWorld_ = matScaleL * matRotL * matTransL;
	worldTransformBumper_.TransferMatrix();

}


void Bumper::BumperArmInitialize() {

	worldTransformBumperArmL_.Initialize();

	//スケール                 
	worldTransformBumperArmL_.scale_ = { 0.3f,2.5f,1.0f };

	Matrix4 matScaleL;

	matScaleL = MathUtility::Matrix4Identity();
	matScaleL.m[0][0] = worldTransformBumperArmL_.scale_.x;
	matScaleL.m[1][1] = worldTransformBumperArmL_.scale_.y;
	matScaleL.m[2][2] = worldTransformBumperArmL_.scale_.z;

	worldTransformBumperArmL_.matWorld_ = MathUtility::Matrix4Identity();
	worldTransformBumperArmL_.matWorld_ *= matScaleL;

	worldTransformBumperArmL_.TransferMatrix();

	//回転
	worldTransformBumperArmL_.rotation_ = { 0,0,0 };

	Matrix4 matRotL;
	Matrix4 matRotZL;
	Matrix4 matRotXL;
	Matrix4 matRotYL;

	matRotZL = MathUtility::Matrix4Identity();
	matRotXL = MathUtility::Matrix4Identity();
	matRotYL = MathUtility::Matrix4Identity();

	matRotZL.m[0][0] = cos(worldTransformBumperArmL_.rotation_.z);
	matRotZL.m[0][1] = sin(worldTransformBumperArmL_.rotation_.z);
	matRotZL.m[1][0] = -sin(worldTransformBumperArmL_.rotation_.z);
	matRotZL.m[1][1] = cos(worldTransformBumperArmL_.rotation_.z);

	matRotXL.m[1][1] = cos(worldTransformBumperArmL_.rotation_.x);
	matRotXL.m[1][2] = sin(worldTransformBumperArmL_.rotation_.x);
	matRotXL.m[2][1] = -sin(worldTransformBumperArmL_.rotation_.x);
	matRotXL.m[2][2] = cos(worldTransformBumperArmL_.rotation_.x);

	matRotYL.m[0][0] = cos(worldTransformBumperArmL_.rotation_.y);
	matRotYL.m[0][2] = sin(worldTransformBumperArmL_.rotation_.y);
	matRotYL.m[2][0] = -sin(worldTransformBumperArmL_.rotation_.y);
	matRotYL.m[2][2] = cos(worldTransformBumperArmL_.rotation_.y);

	matRotL = matRotZL * matRotXL * matRotYL;

	worldTransformBumperArmL_.matWorld_ = MathUtility::Matrix4Identity();
	worldTransformBumperArmL_.matWorld_ *= matRotZL;
	worldTransformBumperArmL_.matWorld_ *= matRotXL;
	worldTransformBumperArmL_.matWorld_ *= matRotYL;

	worldTransformBumperArmL_.TransferMatrix();

	//位置
	worldTransformBumperArmL_.translation_ = { -1.3f,7.5f,10.0f };

	Matrix4 matTransL = MathUtility::Matrix4Identity();

	matTransL.m[3][0] = worldTransformBumperArmL_.translation_.x;
	matTransL.m[3][1] = worldTransformBumperArmL_.translation_.y;
	matTransL.m[3][2] = worldTransformBumperArmL_.translation_.z;

	worldTransformBumperArmL_.matWorld_ = MathUtility::Matrix4Identity();
	worldTransformBumperArmL_.matWorld_ *= matTransL;

	worldTransformBumperArmL_.matWorld_ = matScaleL * matRotL * matTransL;
	worldTransformBumperArmL_.TransferMatrix();


	worldTransformBumperArmR_.Initialize();

	//スケール                 
	worldTransformBumperArmR_.scale_ = { 0.3f,2.5f,1.0f };

	Matrix4 matScaleR;

	matScaleR = MathUtility::Matrix4Identity();
	matScaleR.m[0][0] = worldTransformBumperArmR_.scale_.x;
	matScaleR.m[1][1] = worldTransformBumperArmR_.scale_.y;
	matScaleR.m[2][2] = worldTransformBumperArmR_.scale_.z;

	worldTransformBumperArmR_.matWorld_ = MathUtility::Matrix4Identity();
	worldTransformBumperArmR_.matWorld_ *= matScaleR;

	worldTransformBumperArmR_.TransferMatrix();

	//回転
	worldTransformBumperArmR_.rotation_ = { 0,0,0 };

	Matrix4 matRotR;
	Matrix4 matRotZR;
	Matrix4 matRotXR;
	Matrix4 matRotYR;

	matRotZR = MathUtility::Matrix4Identity();
	matRotXR = MathUtility::Matrix4Identity();
	matRotYR = MathUtility::Matrix4Identity();

	matRotZR.m[0][0] = cos(worldTransformBumperArmR_.rotation_.z);
	matRotZR.m[0][1] = sin(worldTransformBumperArmR_.rotation_.z);
	matRotZR.m[1][0] = -sin(worldTransformBumperArmR_.rotation_.z);
	matRotZR.m[1][1] = cos(worldTransformBumperArmR_.rotation_.z);

	matRotXR.m[1][1] = cos(worldTransformBumperArmR_.rotation_.x);
	matRotXR.m[1][2] = sin(worldTransformBumperArmR_.rotation_.x);
	matRotXR.m[2][1] = -sin(worldTransformBumperArmR_.rotation_.x);
	matRotXR.m[2][2] = cos(worldTransformBumperArmR_.rotation_.x);

	matRotYR.m[0][0] = cos(worldTransformBumperArmR_.rotation_.y);
	matRotYR.m[0][2] = sin(worldTransformBumperArmR_.rotation_.y);
	matRotYR.m[2][0] = -sin(worldTransformBumperArmR_.rotation_.y);
	matRotYR.m[2][2] = cos(worldTransformBumperArmR_.rotation_.y);

	matRotR = matRotZR * matRotXR * matRotYR;

	worldTransformBumperArmR_.matWorld_ = MathUtility::Matrix4Identity();
	worldTransformBumperArmR_.matWorld_ *= matRotZR;
	worldTransformBumperArmR_.matWorld_ *= matRotXR;
	worldTransformBumperArmR_.matWorld_ *= matRotYR;

	worldTransformBumperArmR_.TransferMatrix();

	//位置
	worldTransformBumperArmR_.translation_ = { 1.3f,7.5f,10.0f };

	Matrix4 matTransR = MathUtility::Matrix4Identity();

	matTransR.m[3][0] = worldTransformBumperArmR_.translation_.x;
	matTransR.m[3][1] = worldTransformBumperArmR_.translation_.y;
	matTransR.m[3][2] = worldTransformBumperArmR_.translation_.z;

	worldTransformBumperArmR_.matWorld_ = MathUtility::Matrix4Identity();
	worldTransformBumperArmR_.matWorld_ *= matTransR;

	worldTransformBumperArmR_.matWorld_ = matScaleR * matRotR * matTransR;
	worldTransformBumperArmR_.TransferMatrix();


}


void Bumper::BumperArmMove() {


	//Lアーム
	Matrix4 matScaleL;

	matScaleL = MathUtility::Matrix4Identity();
	matScaleL.m[0][0] = worldTransformBumperArmL_.scale_.x;
	matScaleL.m[1][1] = worldTransformBumperArmL_.scale_.y;
	matScaleL.m[2][2] = worldTransformBumperArmL_.scale_.z;

	worldTransformBumperArmL_.matWorld_ = MathUtility::Matrix4Identity();
	worldTransformBumperArmL_.matWorld_ *= matScaleL;

	Matrix4 matRotL;
	Matrix4 matRotZL;
	Matrix4 matRotXL;
	Matrix4 matRotYL;

	matRotZL = MathUtility::Matrix4Identity();
	matRotXL = MathUtility::Matrix4Identity();
	matRotYL = MathUtility::Matrix4Identity();

	matRotZL.m[0][0] = cos(worldTransformBumperArmL_.rotation_.z);
	matRotZL.m[0][1] = sin(worldTransformBumperArmL_.rotation_.z);
	matRotZL.m[1][0] = -sin(worldTransformBumperArmL_.rotation_.z);
	matRotZL.m[1][1] = cos(worldTransformBumperArmL_.rotation_.z);

	matRotXL.m[1][1] = cos(worldTransformBumperArmL_.rotation_.x);
	matRotXL.m[1][2] = sin(worldTransformBumperArmL_.rotation_.x);
	matRotXL.m[2][1] = -sin(worldTransformBumperArmL_.rotation_.x);
	matRotXL.m[2][2] = cos(worldTransformBumperArmL_.rotation_.x);

	matRotYL.m[0][0] = cos(worldTransformBumperArmL_.rotation_.y);
	matRotYL.m[0][2] = sin(worldTransformBumperArmL_.rotation_.y);
	matRotYL.m[2][0] = -sin(worldTransformBumperArmL_.rotation_.y);
	matRotYL.m[2][2] = cos(worldTransformBumperArmL_.rotation_.y);

	matRotL = matRotZL * matRotXL * matRotYL;

	worldTransformBumperArmL_.matWorld_ = MathUtility::Matrix4Identity();
	worldTransformBumperArmL_.matWorld_ *= matRotZL;
	worldTransformBumperArmL_.matWorld_ *= matRotXL;
	worldTransformBumperArmL_.matWorld_ *= matRotYL;

	Matrix4 matTransL = MathUtility::Matrix4Identity();

	matTransL.m[3][0] = worldTransformBumperArmL_.translation_.x;
	matTransL.m[3][1] = worldTransformBumperArmL_.translation_.y;
	matTransL.m[3][2] = worldTransformBumperArmL_.translation_.z;

	worldTransformBumperArmL_.matWorld_ = MathUtility::Matrix4Identity();
	worldTransformBumperArmL_.matWorld_ *= matTransL;

	worldTransformBumperArmL_.matWorld_ = matScaleL * matRotL * matTransL;
	worldTransformBumperArmL_.TransferMatrix();


	//Rアーム
	Matrix4 matScaleR;

	matScaleR = MathUtility::Matrix4Identity();
	matScaleR.m[0][0] = worldTransformBumperArmR_.scale_.x;
	matScaleR.m[1][1] = worldTransformBumperArmR_.scale_.y;
	matScaleR.m[2][2] = worldTransformBumperArmR_.scale_.z;

	worldTransformBumperArmR_.matWorld_ = MathUtility::Matrix4Identity();
	worldTransformBumperArmR_.matWorld_ *= matScaleR;

	worldTransformBumperArmR_.TransferMatrix();

	//回転
	Matrix4 matRotR;
	Matrix4 matRotZR;
	Matrix4 matRotXR;
	Matrix4 matRotYR;

	matRotZR = MathUtility::Matrix4Identity();
	matRotXR = MathUtility::Matrix4Identity();
	matRotYR = MathUtility::Matrix4Identity();

	matRotZR.m[0][0] = cos(worldTransformBumperArmR_.rotation_.z);
	matRotZR.m[0][1] = sin(worldTransformBumperArmR_.rotation_.z);
	matRotZR.m[1][0] = -sin(worldTransformBumperArmR_.rotation_.z);
	matRotZR.m[1][1] = cos(worldTransformBumperArmR_.rotation_.z);

	matRotXR.m[1][1] = cos(worldTransformBumperArmR_.rotation_.x);
	matRotXR.m[1][2] = sin(worldTransformBumperArmR_.rotation_.x);
	matRotXR.m[2][1] = -sin(worldTransformBumperArmR_.rotation_.x);
	matRotXR.m[2][2] = cos(worldTransformBumperArmR_.rotation_.x);

	matRotYR.m[0][0] = cos(worldTransformBumperArmR_.rotation_.y);
	matRotYR.m[0][2] = sin(worldTransformBumperArmR_.rotation_.y);
	matRotYR.m[2][0] = -sin(worldTransformBumperArmR_.rotation_.y);
	matRotYR.m[2][2] = cos(worldTransformBumperArmR_.rotation_.y);

	matRotR = matRotZR * matRotXR * matRotYR;

	worldTransformBumperArmR_.matWorld_ = MathUtility::Matrix4Identity();
	worldTransformBumperArmR_.matWorld_ *= matRotZR;
	worldTransformBumperArmR_.matWorld_ *= matRotXR;
	worldTransformBumperArmR_.matWorld_ *= matRotYR;

	worldTransformBumperArmR_.TransferMatrix();

	//位置

	Matrix4 matTransR = MathUtility::Matrix4Identity();

	matTransR.m[3][0] = worldTransformBumperArmR_.translation_.x;
	matTransR.m[3][1] = worldTransformBumperArmR_.translation_.y;
	matTransR.m[3][2] = worldTransformBumperArmR_.translation_.z;

	worldTransformBumperArmR_.matWorld_ = MathUtility::Matrix4Identity();
	worldTransformBumperArmR_.matWorld_ *= matTransR;

	worldTransformBumperArmR_.matWorld_ = matScaleR * matRotR * matTransR;
	worldTransformBumperArmR_.TransferMatrix();
}

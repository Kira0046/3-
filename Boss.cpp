#include "Boss.h"
#include <cassert>
#include "TestTarget.h"
#include "Procession.h"
using namespace MathUtility;


void Boss::Initialize(Model* model, Model* modelBullet)
{
	assert(model);

	model_ = model;
	modelBullet_ = modelBullet;

	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	worldTransform_.scale_ = { 5.0f,5.0f,5.0f };
	worldTransform_.rotation_ = { 0,0,0 };
	worldTransform_.translation_ = { 0,0,50.0f };

	Damage = 1.0f;

	worldTransform_.Initialize();

	// çsóÒçXêV
	worldTransform_.matWorld_ = Mat_Identity();
	worldTransform_.matWorld_ = MatWorld(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	worldTransform_.TransferMatrix();

}

void Boss::Update()
{
	bullets_.remove_if([](std::unique_ptr<BossBullet>& bullet) {
		return bullet->IsDead();
		});

	switch (phase_)
	{
	case Phase::First:
	default:
		FirstPhase();
		break;
	case Phase::Second:
		SecondPhase();
		break;
	case Phase::Third:
		ThirdPhase();
		break;
	}

	
	Shoot();

	for (std::unique_ptr<BossBullet>& bullet : bullets_) {
		bullet->Update();
	}

	if (input_->TriggerKey(DIK_SPACE))
	{
		Damage += 1;
	}

	// çsóÒçXêV
	worldTransform_.matWorld_ = Mat_Identity();
	worldTransform_.matWorld_ = MatWorld(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	worldTransform_.TransferMatrix();
}

void Boss::Draw(ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection);

	for (std::unique_ptr<BossBullet>& bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
}

void Boss::Shoot()
{
	shootTimer -= 1;
	if (shootTimer < 0) {
		assert(testTarget_);

		Vector3 distance(0, 0, 0);
		float ALLdistance = 0;

		distance.x = testTarget_->GetWorldPosition().x - GetWorldPosition().x;
		distance.y = testTarget_->GetWorldPosition().y - GetWorldPosition().y;
		distance.z = testTarget_->GetWorldPosition().z - GetWorldPosition().z;

		ALLdistance = sqrt(distance.x * distance.x + distance.y * distance.y + distance.z * distance.z);

		velocity.x = distance.x / ALLdistance;
		velocity.y = distance.y / ALLdistance;
		velocity.z = distance.z / ALLdistance;

		switch (phase_)
		{
		case Phase::First:
		default:
			FirstPhase();
			break;
		case Phase::Second:
			SecondPhase();
			break;
		case Phase::Third:
			//íe2
			Vector3 distance2(0, 0, 0);
			float ALLdistance2 = 0;

			distance2.x = (testTarget_->GetWorldPosition().x - rand() % 7 + 1) - GetWorldPosition().x;
			distance2.y = (testTarget_->GetWorldPosition().y - rand() % 7 + 1) - GetWorldPosition().y;
			distance2.z = (testTarget_->GetWorldPosition().z - rand() % 7 + 1) - GetWorldPosition().z;

			ALLdistance2 = sqrt(distance2.x * distance2.x + distance2.y * distance2.y + distance2.z * distance2.z);

			velocity2.x = distance2.x / ALLdistance2;
			velocity2.y = distance2.y / ALLdistance2;
			velocity2.z = distance2.z / ALLdistance2;

			velocity2 *= 2;

			std::unique_ptr<BossBullet> newBullet2 = std::make_unique<BossBullet>();
			newBullet2->Initialize(modelBullet_, worldTransform_.translation_, velocity2);

			bullets_.push_back(std::move(newBullet2));

			//íe3
			Vector3 distance3(0, 0, 0);
			float ALLdistance3 = 0;

			distance3.x = (testTarget_->GetWorldPosition().x + rand() % 7 + 1) - GetWorldPosition().x;
			distance3.y = (testTarget_->GetWorldPosition().y + rand() % 7 + 1) - GetWorldPosition().y;
			distance3.z = (testTarget_->GetWorldPosition().z + rand() % 7 + 1) - GetWorldPosition().z;

			ALLdistance3 = sqrt(distance3.x * distance3.x + distance3.y * distance3.y + distance3.z * distance3.z);

			velocity3.x = distance3.x / ALLdistance3;
			velocity3.y = distance3.y / ALLdistance3;
			velocity3.z = distance3.z / ALLdistance3;

			velocity3 *= 2;

			std::unique_ptr<BossBullet> newBullet3 = std::make_unique<BossBullet>();
			newBullet3->Initialize(modelBullet_, worldTransform_.translation_, velocity3);

			bullets_.push_back(std::move(newBullet3));

			//íe4
			Vector3 distance4(0, 0, 0);
			float ALLdistance4 = 0;

			distance4.x = (testTarget_->GetWorldPosition().x - rand() % 7 + 1) - GetWorldPosition().x;
			distance4.y = (testTarget_->GetWorldPosition().y - rand() % 7 + 1) - GetWorldPosition().y;
			distance4.z = (testTarget_->GetWorldPosition().z - rand() % 7 + 1) - GetWorldPosition().z;

			ALLdistance4 = sqrt(distance4.x * distance4.x + distance4.y * distance4.y + distance4.z * distance3.z);

			velocity4.x = distance4.x / ALLdistance4;
			velocity4.y = distance4.y / ALLdistance4;
			velocity4.z = distance4.z / ALLdistance4;

			velocity4 *= 2;

			std::unique_ptr<BossBullet> newBullet4 = std::make_unique<BossBullet>();
			newBullet4->Initialize(modelBullet_, worldTransform_.translation_, velocity4);

			bullets_.push_back(std::move(newBullet4));

			ThirdPhase();
			break;
		}

		std::unique_ptr<BossBullet> newBullet = std::make_unique<BossBullet>();
		newBullet->Initialize(modelBullet_, worldTransform_.translation_, velocity);

		bullets_.push_back(std::move(newBullet));
		if (Damage == 1)
		{
			shootTimer = 60;
		}

		else if (Damage == 2)
		{
			shootTimer = 45;
		}

		else if (Damage == 3)
		{
			shootTimer = 30;
		}
	}
}


Vector3 Boss::GetWorldPosition()
{
	Vector3 worldPos;

	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}

void Boss::Collision()
{

}



void Boss::FirstPhase()
{
	if (Damage == 2)
	{
		phase_ = Phase::Second;
	}
}

void Boss::SecondPhase()
{
	velocity *= 2;

	if (Damage == 3)
	{
		phase_ = Phase::Third;
	}
}

void Boss::ThirdPhase()
{
	velocity *= 3;
}
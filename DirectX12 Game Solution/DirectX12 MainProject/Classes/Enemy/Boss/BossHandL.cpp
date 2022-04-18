#include "Classes/Enemy/Boss/BossHandL.h"
#include "Classes/Enemy/Boss/BossAttack.h"

void BossHandL::Initialize() {
	BossParts::Initialize(
		SimpleMath::Vector3(INITIAL_POS_X, INITIAL_POS_Y, 0.0f),
		SimpleMath::Vector3(XM_PIDIV4, -5.0f, 0.0f)
	);
	slap_time = 0.0f;
	beat_time = 0.0f;
	wait_time = 0.0f;
	time_delta = 0.0f;
	hand_return_flag = false;
	attack_flag = false;
}

void BossHandL::LoadAssets() {
	BossParts::LoadAssets(L"Boss/boss_hand_L.X");

	left_hand_obb = model->GetBoundingOrientedBox();
	left_hand_obb.Extents = SimpleMath::Vector3(left_hand_obb.Extents);

	left_hand_obb_model = DX9::Model::CreateBox(
		DXTK->Device9,
		left_hand_obb.Extents.x,
		left_hand_obb.Extents.y,
		left_hand_obb.Extents.z
	);
	D3DMATERIAL9 material{};
	material.Diffuse = DX9::Colors::Value(0.0f, 1.0f, 0.0f, 0.75f);
	left_hand_obb_model->SetMaterial(material);
}

void BossHandL::Update(const float deltaTime) {
	time_delta = deltaTime;
	left_hand_obb.Center = model->GetPosition();
	left_hand_obb.Orientation = model->GetRotationQuaternion();
}

void BossHandL::Render() {
	BossParts::Render();
	left_hand_obb_model->SetPosition(left_hand_obb.Center);
	left_hand_obb_model->SetRotationQuaternion(left_hand_obb.Orientation);
	left_hand_obb_model->Draw();
}

void BossHandL::LeftSlap(BossAttack* bossattack) {
	if (!hand_return_flag) {
		attack_flag = true;
		slap_time += time_delta;
		position.x += SLAP_SPEED * slap_time - HALF * SLAP_GRAVITY * slap_time * slap_time;
		rotation.x = std::min(rotation.x + 1.0f * time_delta, XM_PIDIV2);
		position.y = std::max(position.y - 10.0f * time_delta, 2.0f);
	}
	else {
		position.x = std::max(position.x - 10.0f * time_delta, INITIAL_POS_X);
		rotation.x = std::max(rotation.x - 10.0f * time_delta, XM_PIDIV4);
		position.y = std::min(position.y + 10.0f * time_delta, INITIAL_POS_Y);
	}


	if (position.x <= -70.0f) {
		position.x = 30.0f;
		attack_flag = false;
		hand_return_flag = true;
	}

	if (position.x <= INITIAL_POS_X && hand_return_flag) {
		position.x = INITIAL_POS_X;
		slap_time = 0.0f;
		hand_return_flag = false;
		bossattack->SetBossState(0);
	}
}

void BossHandL::LeftBeat(BossAttack* bossattack, SimpleMath::Vector3 player_pos) {
	if (!hand_return_flag) {
		attack_flag = true;
		beat_time += time_delta;
		position.y += BEAT_SPEED * beat_time - HALF * BEAT_GRAVITY * beat_time * beat_time;
		rotation.x = std::max(rotation.x - 1.0f * time_delta, -XM_1DIV2PI);
	}
	
	if (position.y <= 0.0f) {
		position.y = 0.0f;
		hand_return_flag = true;
	}

	if (hand_return_flag) {
		attack_flag = false;
		wait_time += time_delta;
	}

	if (wait_time >= 2.0f) {
		position.y = std::min(position.y + 5.0f * time_delta, INITIAL_POS_Y);
		rotation.x = std::min(rotation.x + 1.0f * time_delta, XM_PIDIV4);
	}

	if (position.y >= INITIAL_POS_Y && hand_return_flag) {
		position.y = INITIAL_POS_Y;
		wait_time = 0.0f;
		beat_time = 0.0f;
		hand_return_flag = false;
		bossattack->SetBossState(0);
	}
}
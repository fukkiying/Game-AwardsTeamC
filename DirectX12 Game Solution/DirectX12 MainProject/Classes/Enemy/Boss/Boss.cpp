#include "Classes/Enemy/Boss/Boss.h"
#include "Classes/Collision/ObjectManager.h"
#include "Classes/Enemy/Boss/Parts/Hands/Attack/RightSlap.h"
#include "Classes/Enemy/Boss/Parts/Hands/Attack/RightBeat.h"
#include "Classes/Enemy/Boss/Parts/Hands/Attack/LeftSlap.h"
#include "Classes/Enemy/Boss/Parts/Hands/Attack/LeftBeat.h"
#include "Classes/Enemy/Boss/Parts/Hands/Attack/BeatRushR.h"
#include "Classes/Enemy/Boss/Parts/Hands/Attack/Wait.h"

void Boss::Initialize() {
	body.Initialize();
	core.Initialize();
	hand_l.Initialize();
	hand_r.Initialize();
	std::random_device seed;
	randomEngine = std::mt19937(seed());
	randomDist = std::uniform_int_distribution<>(1, 5);
	attack = new Wait;
	attack->Initialize(&hand_l, &hand_r);
	action_end_flag = false;
}

void Boss::LoadAseets(){
	body.LoadAssets();
	core.LoadAssets();
	hand_l.LoadAssets();
	hand_r.LoadAssets();
	DX12Effect.Create(L"Effect/Eff_shock_001/shock_001.efk", "hit");
}

void Boss::Update(const float deltaTime, ObjectManager* obj_m) {
	core.Update(deltaTime, obj_m->GetBossDmgFlag());
	hand_l.Update(deltaTime);
	hand_r.Update(deltaTime);
	attack->Update(deltaTime, obj_m->GetPlayerPos(), this);
	SwitchStateWait();
}

void Boss::Render(){
	body.Render();
	core.Render();
	hand_l.Render();
	hand_r.Render();
}

void Boss::Render2D() {
	core.Render2D();
}

void Boss::RandomAttackState() {
	attack_state = randomDist(randomEngine);
	SwitchStateAttack();
}

void Boss::SwitchStateAttack() {
	delete attack;
	switch (attack_state)
	{
	case RIGHT_SLAP:
		attack = new RightSlap;
		break;

	case RIGHT_BEAT:
		attack = new RightBeat;	
		break;

	case LEFT_SLAP:
		attack = new LeftSlap;
		break;

	case LEFT_BEAT:
		attack = new LeftBeat;
		break;

	case BEAT_RUSH_R:
		attack = new BeatRushR;
		break;
	}
	attack->Initialize(&hand_l, &hand_r);
}

void Boss::ActionEnd(){
	action_end_flag = true;
}

void Boss::SwitchStateWait(){
	if (action_end_flag) {
		delete attack;
		attack = new Wait;
		attack->Initialize(&hand_l, &hand_r);
		action_end_flag = false;
	}
}

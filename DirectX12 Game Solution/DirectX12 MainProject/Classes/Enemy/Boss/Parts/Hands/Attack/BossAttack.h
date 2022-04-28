#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Classes/Enemy/Boss/Parts/Hands/BossHand.h"

class Boss;

using namespace DirectX;

class BossAttack {
public:
	virtual void Initialize(BossHand* boss_handL, BossHand* bosshandR) {
		boss_handL_ = boss_handL;
		boss_handR_ = bosshandR;
	};
	virtual void Update(const float deltaTime, SimpleMath::Vector3 player_pos, Boss* boss) = 0;

protected:
	BossHand* boss_handL_;
	BossHand* boss_handR_;

	const float HAND_R_INITIAL_POS_X = -13.0f;
	const float HAND_L_INITIAL_POS_X = 13.0f;
	const float HAND_INITIAL_POS_Y = 10.0f;
	const float HAND_INITIAL_POS_Z = 3.0f;

	const float SLAP_SPEED = 1.5f;
	const float SLAP_GRAVITY = 5.0f;

	const float BEAT_SPEED = 1.5f;
	const float BEAT_GRAVITY = 15.0f;
	const float MOVE_SPEED_X = 30.0f;
	const float MOVE_SPEED_Y = 10.0f;

	const float HALF = 0.5f;

};
#include "Classes/Enemy/Boss/Parts/Hands/Attack/LeftSlap.h"
#include "Classes/Enemy/Boss/Boss.h"

void LeftSlap::Update(const float deltaTime, SimpleMath::Vector3 player_pos, Boss* boss){
	SimpleMath::Vector3 pos = boss_handL_->GetHandPos();
	SimpleMath::Vector3 rote = boss_handL_->GetRotation();

	if (!hand_return_flag) {
		boss_handL_->SetAttackFlag(true);
		slap_time += deltaTime;
		pos.x += SLAP_SPEED * slap_time - HALF * SLAP_GRAVITY * slap_time * slap_time;
		pos.y = std::max(pos.y - 10.0f * deltaTime, 2.0f);
		pos.z = std::max(pos.z - 10.0f * deltaTime, 0.0f);
		rote.x = std::min(rote.x + 1.0f * deltaTime, XM_PIDIV2);
	}
	else {
		pos.x = std::max(pos.x - 10.0f * deltaTime, HAND_L_INITIAL_POS_X);
		pos.y = std::min(pos.y + 10.0f * deltaTime, HAND_INITIAL_POS_Y);
		pos.z = std::min(pos.z + 10.0f * deltaTime, HAND_INITIAL_POS_Z);
		rote.x = std::max(rote.x - 10.0f * deltaTime, XM_PIDIV4);
	}


	if (pos.x <= -70.0f) {
		pos.x = 30.0f;
		hand_return_flag = true;
		boss_handL_->SetAttackFlag(false);
	}

	if (pos.x <= HAND_L_INITIAL_POS_X && hand_return_flag) {
		pos.x = HAND_L_INITIAL_POS_X;
		slap_time = 0.0f;
		hand_return_flag = false;
		boss->ActionEnd();
	}

	boss_handL_->SetHandPos(pos);
	boss_handL_->SetHandRote(rote);
}
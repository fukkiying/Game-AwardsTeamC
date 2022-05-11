#include "Classes/Enemy/Boss/Parts/Hands/Attack/RightBeat.h"
#include "Classes/Enemy/Boss/Boss.h"

void RightBeat::Update(const float deltaTime, SimpleMath::Vector3 player_pos, Boss* boss){
	pos  = boss_handR_->GetHandPos();
	rote = boss_handR_->GetRotation();

	time_delta = deltaTime;

	switch (boss_action_state)
	{
	case MOVE:
		HandMove(player_pos);
		break;

	case ATTACK:
		RightBeatAttack();
		break;

	case RETURN_POSITION:
		HandReturn();
		break;

	case ACTION_END:
		boss_action_state = MOVE;
		boss->ActionEnd();
		break;
	}

	boss_handR_->SetHandPos(pos);
	boss_handR_->SetHandRote(rote);

}

void RightBeat::HandMove(SimpleMath::Vector3 player_pos) {
	if (!player_pos_get_flag_) {
		move_pos = player_pos;
		player_pos_get_flag_ = true;
	}

	pos.z = std::max(pos.z - 10.0f * time_delta, 0.0f);

	if (pos.x < move_pos.x)
		pos.x = std::min(pos.x + MOVE_SPEED_X_ * time_delta, move_pos.x);
	else
		pos.x = std::max(pos.x - MOVE_SPEED_X_ * time_delta, move_pos.x);

	if (pos.x == move_pos.x)
		boss_action_state = ATTACK;
}

void RightBeat::RightBeatAttack() {
	boss_handR_->SetAttackFlag(true);
	beat_time_ += time_delta;
	pos.y += BEAT_SPEED_ * beat_time_ - HALF_ * BEAT_GRAVITY_ * beat_time_ * beat_time_;
	rote.x = std::max(rote.x - 1.0f * time_delta, -XM_1DIV2PI);

	if (pos.y <= 0.0f) {
		pos.y = 0.0f;
		DX12Effect.PlayOneShot("hit", pos);
		boss_handR_->SetAttackFlag(false);
		boss_action_state = RETURN_POSITION;
	}	
}

void RightBeat::HandReturn() {
	wait_time_ += time_delta;

	if (wait_time_ >= 0.2f) {
		if (pos.x < HAND_R_INITIAL_POS_X_)
			pos.x = std::min(pos.x + MOVE_SPEED_X_ * time_delta, HAND_R_INITIAL_POS_X_);
		else
			pos.x = std::max(pos.x - MOVE_SPEED_X_ * time_delta, HAND_R_INITIAL_POS_X_);

		pos.y = std::min(pos.y + MOVE_SPEED_Y_ * time_delta, HAND_INITIAL_POS_Y_);
		pos.z = std::min(pos.z + 10.0f * time_delta, HAND_INITIAL_POS_Z_);
		rote.x = std::min(rote.x + 1.0f * time_delta, XM_PIDIV4);
	}

	if (pos.y >= HAND_INITIAL_POS_Y_ && pos.x == HAND_R_INITIAL_POS_X_) {
		wait_time_ = 0.0f;
		beat_time_ = 0.0f;

		player_pos_get_flag_ = false;
		boss_action_state = ACTION_END;
	}
}
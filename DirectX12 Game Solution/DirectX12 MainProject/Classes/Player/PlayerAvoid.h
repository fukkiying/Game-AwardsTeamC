#pragma once

#include "Classes/Player/PlayerState.h"

class PlayerAvoid : public PlayerState {
public:
	PlayerAvoid() {
		action_state_ = READY;

		avoid_speed_	= 0.0f;
		player_dest_x_  = 0.0f;
		cool_time_		= 0.0f;
		avoid_time_		= 0.0f;
		time_delta_		= 0.0f;

		invincible_flag_ = false;

		player_rote_ = SimpleMath::Vector3::Zero;
	}

	~PlayerAvoid() {};

	virtual void Initialize();
	virtual void Update(const float deltaTime, Player& player);

	bool IsInvincible() { return invincible_flag_; }
private:
	void Ready(Player& player);
	void Avoid();
	void CoolTime();

	bool IsPayerRightWard() { return player_rote_.y >= PLAYER_ROTATION_ANGLE_; }

	int action_state_;

	enum ACTION_STATE_ {
		READY,
		AVOID,
		COOL_TIME,
		ACTION_END
	};

	float avoid_speed_;
	float player_dest_x_;
	float avoid_time_;
	float cool_time_;
	float time_delta_;
	bool invincible_flag_;

	SimpleMath::Vector3 player_rote_;
	SimpleMath::Vector3 pos_;
	SimpleMath::Vector3 rot_;

	const float PLAYER_ROTATION_ANGLE_  = 90.0f;
	const float PLAYER_LIMIT_MAX_POS_X_ = 17.0f;
	const float PLAYER_LIMIT_MIN_POS_X_ = -14.0f;
	const float ADD_POS_X_ = 5.5f;
	const float ADD_AVOID_SPEED_ = 100.0f;
	const float AVOID_MAX_SPEED_ = 100.0f;
	const float COOL_TIME_MAX = 0.21f;
};
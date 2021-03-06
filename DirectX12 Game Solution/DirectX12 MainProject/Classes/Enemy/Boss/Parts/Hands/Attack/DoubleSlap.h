#pragma once

#include "Classes/Enemy/Boss/Parts/Hands/Attack/BossAttack.h"

class DoubleSlap : public BossAttack {
public:
	DoubleSlap() {
		action_state_  = HAND_CHECK;
		time_delta_	   = 0.0f;
		r_slap_time_x_ = 0.0f;
		r_slap_time_y_ = 0.0f;
		l_slap_time_x_ = 0.0f;
		l_slap_time_y_ = 0.0f;
		wait_time_	   = 0.0f;
		ready_flag_r_ = false;
		ready_flag_l_ = false;
		atk_end_r_	  = false;
		atk_end_l_	  = false;
		return_end_r_ = false;
		return_end_l_ = false;
		is_l_hand_broke_ = false;
		is_r_hand_broke_ = false;
		hand_state_		 = false;
		r_pos_  = SimpleMath::Vector3::Zero;
		r_rote_ = SimpleMath::Vector3::Zero;
		l_pos_  = SimpleMath::Vector3::Zero;
		l_rote_ = SimpleMath::Vector3::Zero;
	}

	~DoubleSlap() {};
	virtual void Update(const float deltaTime, ObjectManager* obj_m, Boss* boss);

private:
	void HandCheck(Boss* boss);
	void Ready();
	void ReadyR();
	void ReadyL();
	void Attack();
	void SlapR();
	void SlapL();
	void Reset();
	void HandReturn();

	int action_state_;

	float time_delta_;
	float r_slap_time_x_;
	float r_slap_time_y_;
	float l_slap_time_x_;
	float l_slap_time_y_;
	float wait_time_;

	bool ready_flag_r_;
	bool ready_flag_l_;
	bool atk_end_r_;
	bool atk_end_l_;
	bool return_end_r_;
	bool return_end_l_;
	bool is_r_hand_broke_;
	bool is_l_hand_broke_;
	bool hand_state_;

	SimpleMath::Vector3 r_pos_;
	SimpleMath::Vector3 r_rote_;
	SimpleMath::Vector3 l_pos_;
	SimpleMath::Vector3 l_rote_;

	const float R_HAND_DEST_Y_  = 2.0f;
	const float L_HAND_DEST_Y_  = 8.0f;
	const float ATTACK_START_TIME_R_ = 1.0f;
	const float WAIT_TIME_MAX_		 = 1.5f;
};
#pragma once

#include "Classes/Enemy/Boss/Parts/Hands/Attack/BossAttack.h"

class Wait : public BossAttack {
public:
	Wait() {
		wait_time_	   = 0.0f;
		max_wait_time_ = 0.0f;
		first_processed_flag_ = false;
	}
	virtual void Update(const float deltaTime, ObjectManager* obj_m, Boss* boss);

private:
	float wait_time_;
	float max_wait_time_;
	bool first_processed_flag_;
	const float HP_NORMAL_MAX_ = 30.0f;
	const float HP_NORMAL_MIN_ = 20.0f;
	const float HP_HARD_MIN_   = 10.0f;
	const float MAX_WAIT_TIME_NORMAL_	 = 0.5f;
	const float MAX_WAIT_TIME_HARD_		 = 0.3f; 
	const float MAX_WAIT_TIME_VERY_HARD_ = 0.1f;
};
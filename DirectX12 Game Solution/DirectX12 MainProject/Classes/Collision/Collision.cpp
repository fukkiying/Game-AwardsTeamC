#include "Classes/Collision/Collision.h"

Collision::Collision() {
	hit_flg_ = false;
	hit_attack_flg_ = false;
}

void Collision::Initialize() {
	hit_flg_ = false;
	hit_attack_flg_ = false;
}

void Collision::LoadAssets() {
	font = DX9::SpriteFont::CreateDefaultFont(DXTK->Device9);
}

void Collision::Update(const float deltaTime, ObjectManager& obj_m_) {
	bool boss_r_atk_flag_ = obj_m_.GetBossRAttackFlag();
	bool boss_l_atk_flag_ = obj_m_.GetBossLAttackFlag();
	bool player_atk_flag_ = obj_m_.GetPlayerAttackFlag();
	BoundingOrientedBox player_col_		 = obj_m_.GetPlayerCollision();
	BoundingOrientedBox player_atk_col_	 = obj_m_.GetPlayerAttackCollision();
	BoundingOrientedBox boss_core_col_	 = obj_m_.GetBossCoreCollision();
	BoundingOrientedBox boss_r_hand_col_ = obj_m_.GetBossRHandCollision();
	BoundingOrientedBox boss_l_hand_col_ = obj_m_.GetBossLHandCollision();

	if (boss_r_atk_flag_) {
		hit_flg_ = player_col_.Intersects(boss_r_hand_col_);
	}

	if (boss_l_atk_flag_) {
		hit_flg_ = player_col_.Intersects(boss_l_hand_col_);
	}
	
	if (player_atk_flag_)
		hit_attack_flg_ = player_atk_col_.Intersects(boss_core_col_);
	else
		hit_attack_flg_ = false;
}

void Collision::Render2D() {
	if (hit_flg_)
		DX9::SpriteBatch->DrawString(
			font.Get(),
			SimpleMath::Vector2(0.0f, 0.0f),
			DX9::Colors::Red,
			L"当たってる"
		);
	else
		DX9::SpriteBatch->DrawString(
			font.Get(),
			SimpleMath::Vector2(0.0f, 0.0f),
			DX9::Colors::Red,
			L"当たってない"
		);
}
#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class ObjectManager;

class UI {
public:
	UI();
	~UI() {};

	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime, ObjectManager* obj_m);
	void Render();

private:
	DX9::SPRITE player_hp_top_;
	DX9::SPRITE player_hp_bottom_;

	float player_hp_width_;

	const int PLAYER_HP_HIGHT_ = 71;
	const float PLAYER_HP_MAX_WIDTH_ = 1021.0f;
	const float PLAYER_HP_WIDTH_DIVIDE_ = 34.0f;	//HPQ[W1/30Ì
	const float PLAYER_HP_TOP_POS_Z_ = -1.0f;
};
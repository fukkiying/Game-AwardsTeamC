#include "Classes/Player/PlayerMove.h"

void PlayerMove::Update(const float deltaTime, SimpleMath::Vector3& pos_, SimpleMath::Vector3& rot_) {

    if (DXTK->KeyState->D) {
        pos_.x += PLAYER_MOVE_SPEED_ * deltaTime;
        rot_.y = -PLAYER_ROTATION_ANGLE_;
    }

    if (DXTK->KeyState->A) {
        pos_.x -= PLAYER_MOVE_SPEED_ * deltaTime;
        rot_.y =  PLAYER_ROTATION_ANGLE_;
    }
}
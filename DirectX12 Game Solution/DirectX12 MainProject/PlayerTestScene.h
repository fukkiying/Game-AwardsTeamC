//
// PlayerTestScene.h
//

#pragma once

#include "Scene.h"
#include "Classes/My_Camera/My_Camera.h"

using Microsoft::WRL::ComPtr;
using std::unique_ptr;
using std::make_unique;
using namespace DirectX;

class PlayerTestScene final : public Scene {
public:
	PlayerTestScene();
	virtual ~PlayerTestScene() { Terminate(); }

	PlayerTestScene(PlayerTestScene&&) = default;
	PlayerTestScene& operator= (PlayerTestScene&&) = default;

	PlayerTestScene(PlayerTestScene const&) = delete;
	PlayerTestScene& operator= (PlayerTestScene const&) = delete;

	// These are the functions you will implement.
	void Initialize() override;
	void LoadAssets() override;

	void Terminate() override;

	void OnDeviceLost() override;
	void OnRestartSound() override;

	NextScene Update(const float deltaTime) override;
	void Render() override;

private:
	DX12::DESCRIPTORHEAP descriptorHeap;
	DX12::SPRITEBATCH    spriteBatch;
	DX12::HGPUDESCRIPTOR dx9GpuDescriptor;

	My_Camera camera;

};
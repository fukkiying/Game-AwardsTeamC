//
// ResultScene.h
//

#pragma once

#include "Scene.h"

using Microsoft::WRL::ComPtr;
using std::unique_ptr;
using std::make_unique;
using namespace DirectX;

class ResultScene final : public Scene {
public:
	ResultScene();
	virtual ~ResultScene() { Terminate(); }

	ResultScene(ResultScene&&) = default;
	ResultScene& operator= (ResultScene&&) = default;

	ResultScene(ResultScene const&) = delete;
	ResultScene& operator= (ResultScene const&) = delete;

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

private:
	DX9::SPRITE result_;
};
#pragma once
#include <GameManager.hpp>
#include <SiteHome.hpp>
#include <Menu.hpp>
#include <raymath.h>
#include <iostream>

class Game {
public:
	Game();
	~Game();
private:
	GameManager* gameManager = GameManager::GetInstance();
	Model model = LoadModel("./assets/Lab/hydrogen.glb");
	Camera camera = { 0 };
	void SetCameraSettings(Camera &camera);
	float yaw = 0.0f;
	void Update3D();
};
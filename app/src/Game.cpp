#include <Game.hpp>
#include <Site.hpp>
#include <iostream>
#include <raymath.h>

Game::Game() {
	gameManager->LoadScene(gameManager->SCENE::GAME, { "Lab/Lab.png" }, { {0, 0} });
	gameManager->LoadButtons({ "Lab/PC.png" }, { "Lab/PCHover.png" }, { { 1580, 575 } });
	Model model = LoadModel("./assets/Lab/hydrogen.glb");
	unsigned int animsCount = 0;
	Camera camera = { 0 };
	camera.position = Vector3{ 0.0f, 10.0f, 10.0f };
	camera.target = Vector3{ 0.0f, 0.0f, 0.0f };
	camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
	camera.fovy = 10.0f;
	camera.projection = CAMERA_PERSPECTIVE;
	Camera* cam = &camera;
	SetCameraMode(camera, CAMERA_FREE);
	float yaw = 0.0f;

	while (gameManager->CurrentScene == gameManager->SCENE::GAME && !gameManager->GetShouldClose())
	{
		model.transform = MatrixRotateXYZ(Vector3{ DEG2RAD * 1, DEG2RAD * yaw, DEG2RAD * 1 });
		UpdateCamera(&camera);
		camera.position = Vector3{ 0.0f, 10.0f, 10.0f };

		yaw += 0.2f;
		BeginDrawing();
		ClearBackground(BLUE);
		gameManager->Update();

		BeginMode3D(camera);
		DrawModel(model, { 1.8f, 1.0f, 0.0f }, 0.5, WHITE);

		EndMode3D();

		EndDrawing();

		if (IsKeyPressed(KEY_ESCAPE))
		{
			delete this;
			Menu* menu = new Menu();
			break;
		}

		if (gameManager->IsButtonClicked(0))
		{
			delete this;
			Site* site = new Site();
			break;
		}
	}
}

Game::~Game() {}
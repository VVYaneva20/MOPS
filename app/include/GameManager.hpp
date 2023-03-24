#pragma once
#include <iostream>
#include <raylib.h>
#include <vector>

class GameManager
{
public:
	enum SCENE {
		NO_SCENE,
		MENU,
		GAME
	};

	SCENE CurrentScene = NO_SCENE;
	static GameManager* GetInstance();
	void Update();
	void LoadScene(SCENE sceneID, std::vector<std::string> textures, std::vector<std::string> hoverEffects, std::vector<Vector2> positions);
	void DrawTextures();
	void DrawButtons();
	void UnloadScene();
	~GameManager();
private:
	static GameManager* instance;
	std::vector<Texture2D> m_Textures;
	std::vector<Vector2> m_TexturePositions;
	std::vector<Texture2D> m_Buttons;
	std::vector<Texture2D> m_OnHoverButtons;
	std::vector<Vector2> m_ButtonPositions;
	GameManager();
};
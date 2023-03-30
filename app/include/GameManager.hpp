#pragma once
#include <iostream>
#include <raylib.h>
#include <vector>
#include <algorithm>

class GameManager
{
public:
    enum SCENE {
        NO_SCENE,
        MENU,
        GAME,
        REGISTER,
        SITEHOME
    };

    Font Arial;
	Font ArialBold;
    SCENE CurrentScene = NO_SCENE;
    static GameManager* GetInstance();
    void Update();
    void LoadScene(SCENE sceneID, std::vector<std::string> textures, std::vector<Vector2> positions);
    void LoadButtons(std::vector<std::string> textureFiles, std::vector<std::string> onHoverTextures, std::vector<Vector2> positions, std::vector<std::string> names);
    void DrawMousePos();
    void DrawTextures();
    void DrawButtons();
    void UnloadButtonByID(size_t ID);
    void UnloadScene();
    bool GetShouldClose();
    bool IsButtonClicked(size_t buttonID);
    bool IsButtonClicked(std::string buttonName);
    std::string GetAssetPath();
    Vector2 GetScreenSize();
    ~GameManager();
private:
    static GameManager* instance;
    const std::string m_AssetPath = "./assets/";
    const Vector2 m_ScreenSize = { 1920, 1080 };
    Vector2 m_MousePos = { 0, 0 };
	struct BUTTON {
		std::string name;
		Texture2D texture;
		Texture2D onHoverTexture;
		Vector2 pos;
	};
	std::vector<BUTTON> m_Buttons;
    std::vector<Texture2D> m_Textures;
    std::vector<Vector2> m_TexturePositions;
    GameManager();
};
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
        GAME,
        REGISTER
    };

    SCENE CurrentScene = NO_SCENE;
    static GameManager* GetInstance();
    void Update();
    void LoadScene(SCENE sceneID, std::vector<std::string> textures, std::vector<Vector2> positions);
    void LoadButtons(std::vector<std::string> textureFiles, std::vector<std::string> onHoverTextures, std::vector<Vector2> positions);
    void DrawMousePos();
    void DrawTextures();
    void DrawButtons();
    void UnloadScene();
    bool GetShouldClose();
    bool IsButtonClicked(size_t buttonID);
    std::string GetAssetPath();
    Vector2 GetScreenSize();
    ~GameManager();
private:
    static GameManager* instance;
    const std::string m_AssetPath = "./assets/";
    const Vector2 m_ScreenSize = { 1920, 1080 };
    Vector2 m_MousePos = { 0, 0 };
    std::vector<Texture2D> m_Textures;
    std::vector<Vector2> m_TexturePositions;
    std::vector<Texture2D> m_Buttons;
    std::vector<Texture2D> m_OnHoverButtons;
    std::vector<Vector2> m_ButtonPositions;
    GameManager();
};
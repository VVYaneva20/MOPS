#pragma once
#include <iostream>
#include <raylib.h>
#include <vector>
#include <algorithm>
#include <json.h>
#include <fstream>
#include <chrono>

class GameManager
{
public:

    enum SCENE {
        NO_SCENE,
        MENU,
        GAME,
        SITEHOME,
        RULES,
        SECONDRULES,
        SETTINGS_LIGHT,
        SETTINGS_DARK,
    };
    SCENE CurrentScene = NO_SCENE;

    enum THEME {
        THEME_LIGHT,
        THEME_DARK
    };
    THEME currentTheme;

    enum CURSOR {
        DEFAULT,
        FLASK,
        MOPS
    };
    CURSOR currentCursor;
    
    Font Arial;
	Font ArialBold;
    static GameManager* GetInstance();
    void Update();
    void LoadScene(SCENE sceneID, std::vector<std::string> textures, std::vector<Vector2> positions, std::vector<bool> hasTheme);
    void LoadButtons(std::vector<std::string> textureFiles, std::vector<std::string> onHoverTextures, std::vector<Vector2> positions, std::vector<std::string> names, std::vector<bool> hasTheme);
    void DrawMousePos();
    void DrawTextures();
    void DrawButtons();
    void UnloadButton(size_t ID);
    void UnloadButton(std::string name);
    void UnloadScene();
    void PassiveIncome();
    bool GetShouldClose();
    bool IsButtonClicked(size_t buttonID);
    bool IsButtonClicked(std::string buttonName);
    std::string GetAssetPath(bool hasTheme = false);
    Vector2 GetScreenSize();
    ~GameManager();
    int GetBalance();
	void SetBalance(int balance);
    bool IncomeUpgrade = false;
	bool OrderFrequencyUpgrade = false;
    bool CursorUpgrade = false;
    void SetCursor(CURSOR cursor);
    void DrawCursor();
private:
    static GameManager* instance;
    const std::string m_AssetPath = "./assets/";
    const Vector2 m_ScreenSize = { 1920, 1080 };
    Texture2D CursorTexture;
    std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();
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
    int m_Balance;
    GameManager();
};
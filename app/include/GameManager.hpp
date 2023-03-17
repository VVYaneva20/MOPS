#pragma once


class GameManager
{
public:
	static GameManager* GetInstance();
	~GameManager();
private:
	static GameManager* instance;
	GameManager();
};
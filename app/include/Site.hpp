#include <GameManager.hpp>
#include <Menu.hpp>

class Site {
public:
	Site();
	~Site();
private:
	GameManager* gameManager = GameManager::GetInstance();
	void DrawSite();
};
#pragma once

#include "GameObject.h"
#include "fSingleton.h"
class SaveManager : public fSingleton<SaveManager>
{
private:
	FILE* m_playerInfo = nullptr;
	FILE* m_objects	   = nullptr;
	FILE* m_gameStats  = nullptr;
public:
	void SaveObjects();
	void WriteObjectInfo(GameObject* obj);
	void SavePlayer();
	void SaveGameStats();
	void LoadObjects();
	void LoadPlayer();
	void LoadGameStats();
	void LoadGame();

#define SAVE_MANAGER SaveManager::Instance()
};


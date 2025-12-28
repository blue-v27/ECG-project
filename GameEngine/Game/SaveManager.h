#pragma once

#include "GameObject.h"
class SaveManager
{
private:
	SaveManager() = default;
	~SaveManager() = default;

	FILE* m_playerInfo = nullptr;
	FILE* m_objects	   = nullptr;
	FILE* m_gameStats  = nullptr;
public:
	static SaveManager& Instance()
	{
		static SaveManager instance;
		return instance;
	}

	SaveManager(const SaveManager&) = delete;
	SaveManager& operator=(const SaveManager&) = delete;
	SaveManager(SaveManager&&) = delete;
	SaveManager& operator=(SaveManager&&) = delete;

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


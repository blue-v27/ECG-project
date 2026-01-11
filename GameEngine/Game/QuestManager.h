#pragma once

#include "fSingleton.h"
class QuestManager : public fSingleton<QuestManager>
{
#define MAX_QUESTS 6

#pragma region QuestText

#define QUEST0 "GRAB YOUR GUN FROM THE GROUND"
#define QUEST1 "Go to the camp fire and find tour watch"
#define QUEST2
#define QUEST3
#define QUEST4
#define QUEST5
#define QUEST_COMPLETE

#pragma endregion 



private:
	int m_currentQuest;
	int m_totalQuests = 6;
	int m_quests[MAX_QUESTS];
public:
	void Start();
	void CompleteQuest(int quest);
	void GoToNextQuest();
	int  GetCurrentQuest();

	void RenderQuestText();

#define QUEST_MANAGER QuestManager::Instance()
};


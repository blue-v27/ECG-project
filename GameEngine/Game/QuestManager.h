#pragma once

#include "fSingleton.h"
class QuestManager : public fSingleton<QuestManager>
{
#define MAX_QUESTS 6

#pragma region QuestText

#define QUEST0 "GRAB YOUR GUN FROM THE GROUND"
#define QUEST1 "GO TO THE CAMPFIRE AND PICK UP YOUR WATCH"
#define QUEST2 "PRESS 'T' TO TRAVEL BACK TO THE FUTURE"
#define QUEST3 "RIGHT CLICK ON THE CUBES TO SWING FROM THEM"
#define QUEST4 "CLIMB TO THE TOP OF THE BUILDING TO SAVE THE WORLD"
#define QUEST5 "YOU HAVE SAVED THE WORLD!!"
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


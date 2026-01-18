#include "QuestManager.h"
#include "GUI/GUIManager.h"

void QuestManager::Start()
{
	m_currentQuest = 0;

	for (int i = 0; i < MAX_QUESTS; ++i)
		m_quests[i] = 0;
}

void QuestManager::CompleteQuest(int quest)
{
	if (m_currentQuest)
	{
		if (!m_quests[m_currentQuest - 1])
			return;
	}

	m_quests[m_currentQuest] = 1;
	m_currentQuest++;
}

void QuestManager::GoToNextQuest()
{
	if (m_quests[m_currentQuest] == 1)
	{
		m_currentQuest++;
	}
}

int QuestManager::GetCurrentQuest()
{
	return m_currentQuest;
}
 
void QuestManager::RenderQuestText()
{
	if(m_currentQuest == 0)
		GUI.DrawText(QUEST0, 0, 700, 1.f);
	else
		GUI.DrawText(QUEST1, 0, 700, 1.f);
}
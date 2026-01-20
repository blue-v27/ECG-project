#include "Watch.h"
#include "GameContext.h"
#include "Inventory.h"
#include "QuestManager.h"

Watch::Watch()
{
	m_type = ObjectType::Watch;
}

void Watch::ProcessInput(Window* window, float deltaTime)
{
	if (m_isActive && INVETORY.GetWatch())
	{
		if (window->IsReleased(GLFW_KEY_T))
		{
			if (QUEST_MANAGER.GetCurrentQuest() == 2)
				QUEST_MANAGER.CompleteQuest(2);

			GAMECONTEXT.TimeTravel();
		}		

		Weapon::ProcessInput(window, deltaTime);
	}
}

void Watch::Render()
{
	if (!IsPickable())
		return;

	InteractiveGameObject::Render();
}

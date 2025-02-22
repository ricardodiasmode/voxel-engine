#include "component-owner/componentOwner.h"

void ComponentOwner::updateComponentsLocation(const glm::vec3 position)
{
	for (std::shared_ptr<Component> currentComp : allComponents)
	{
		if (currentComp)
			currentComp->onParentMove(position);
	}
}

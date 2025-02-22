#pragma once

#include <memory>
#include <components/component.h>
#include <glm/glm.hpp>

class ComponentOwner {
private:
	std::vector<std::shared_ptr<Component>> allComponents;

protected:
	template <typename T, typename... Args>
	std::shared_ptr<T> initializeComponent(Args&&... args) {
		auto component = std::make_shared<T>(std::forward<Args>(args)...);  // Forward args
		allComponents.push_back(component);
		return component;
	}

	void updateComponentsLocation(const glm::vec3 position);

public:
	inline std::vector<std::shared_ptr<Component>> getAllComponents() const { return allComponents; }
};

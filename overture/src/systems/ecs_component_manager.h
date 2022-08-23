#pragma once

#include <defines.h>
#include "ecs_types.h"

#include "ecs_component_array.h"
#include <any>
#include <memory>

namespace ecs {
	class ComponentManager {
		public:
			template<typename T>
			void registerComponent() {
				const char* typeName = typeid(T).name();
				ASSERT_MSG(m_componentTypes.find(typeName) == m_componentTypes.end(), "Registering component type more than once.");
				m_componentTypes.insert({typeName, m_nextComponentType});
				m_componentArrays.insert({typeName, std::make_shared<ComponentArray<T>>()});
				++m_nextComponentType;
			}

			template<typename T>
			ComponentType getComponentType() {
				const char* typeName = typeid(T).name();
				ASSERT_MSG(m_componentTypes.find(typeName) != m_componentTypes.end(), "Component not registered before use.");
				return m_componentTypes[typeName];
			}

			template<typename T>
			void addComponent(Entity entity, T component) {
				getComponentArray<T>()->insertData(entity, component);
			}

			template<typename T>
			void removeComponent(Entity entity) {
				getComponentArray<T>()->removeData(entity);
			}

			template<typename T>
			T& getComponent(Entity entity) {
				return getComponentArray<T>()->getData(entity);
			}

			void entityDestroyed(Entity entity) {
				for (auto const& pair : m_componentArrays) {
					auto const& component = pair.second;
					component->entityDestroyed(entity);
				}
			}

		private:
			std::unordered_map<const char*, ComponentType> m_componentTypes{};
			std::unordered_map<const char*, std::shared_ptr<IComponentArray>> m_componentArrays{};
			ComponentType m_nextComponentType{};

			template<typename T>
			std::shared_ptr<ComponentArray<T>> getComponentArray() {
				const char* typeName = typeid(T).name();
				ASSERT_MSG(m_componentTypes.find(typeName) != m_componentTypes.end(), "Component not registered before use.");
				return std::static_pointer_cast<ComponentArray<T>>(m_componentArrays[typeName]);
			}
	};
}

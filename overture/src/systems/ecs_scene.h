#pragma once

#include <defines.h>
#include "ecs_types.h"

#include "ecs_component_array.h"
#include "ecs_component_manager.h"
#include "ecs_entity_manager.h"
#include "ecs_system_manager.h"

#include <memory>

namespace ecs {
	class Scene {
		public:
			void init() {
				m_componentManager = std::make_unique<ComponentManager>();
				m_entityManager = std::make_unique<EntityManager>();
				m_systemManger = std::make_unique<SystemManager>();
			}

			Entity createEntity() {
				return m_entityManager->createEntity();
			}

			void destroyEntity(Entity entity) {
				m_entityManager->destroyEntity(entity);
				m_componentManager->entityDestroyed(entity);
				m_systemManger->entityDestroyed(entity);
			}

			template<typename T>
			void registerComponent() {
				m_componentManager->registerComponent<T>();
			}

			template<typename T>
			void addComponent(Entity entity, T component) {
				m_componentManager->addComponent<T>(entity, component);

				auto signature = m_entityManager->getSignature(entity);
				signature.set(m_componentManager->getComponentType<T>(), true);
				m_entityManager->setSignature(entity, signature);

				m_systemManger->entitySignatureChanged(entity, signature);
			}

			template<typename T>
			void removeComponent(Entity entity) {
				m_componentManager->removeComponent<T>(entity);

				auto signature = m_entityManager->getSignature(entity);
				signature.set(m_componentManager->getComponentType<T>(), false);
				m_entityManager->setSignature(entity, signature);

				m_systemManger->entitySignatureChanged(entity, signature);
			}

			template<typename T>
			T& getComponent(Entity entity) {
				return m_componentManager->getComponent<T>(entity);
			}

			template<typename T>
			bool hasComponent(Entity entity) {
				ComponentType type = m_componentManager->getComponentType<T>();
				auto signature = m_entityManager->getSignature(entity);
				
				return signature[type];
			}

			template<typename T>
			ComponentType getComponentType() {
				return m_componentManager->getComponentType<T>();
			}

			template<typename T>
			std::shared_ptr<T> registerSystem() {
				return m_systemManger->registerSystem<T>();
			}

			template<typename T>
			void setSystemSignature(Signature signature) {
				m_systemManger->setSignature<T>(signature);
			}

		private:
			std::unique_ptr<ComponentManager> m_componentManager;
			std::unique_ptr<EntityManager> m_entityManager;
			std::unique_ptr<SystemManager> m_systemManger;
	};
};

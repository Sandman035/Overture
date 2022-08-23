#pragma once

#include <defines.h>
#include "ecs_types.h"

#include <queue>
#include <array>
#include <core/asserts.h>

namespace ecs {
	class EntityManager {
		public:
			EntityManager() {
				for (Entity entity = 0; entity < MAX_ENTITIES; ++entity) {
					m_availableEntities.push(entity);
				}
			}

			Entity createEntity() {
				ASSERT_MSG(m_livingEntityCount < MAX_ENTITIES, "Too many entities in existence.");
				Entity id = m_availableEntities.front();
				m_availableEntities.pop();
				++m_livingEntityCount;
				return id;
			}

			void destroyEntity(Entity entity) {
				ASSERT_MSG(entity < MAX_ENTITIES, "Entity out of range.");
				m_signatures[entity].reset();
				m_availableEntities.push(entity);
				--m_livingEntityCount;
			}

			void setSignature(Entity entity, Signature signature) {
				ASSERT_MSG(entity < MAX_ENTITIES, "Entity out of range.");
				m_signatures[entity] = signature;
			}

			Signature getSignature(Entity entity) {
				ASSERT_MSG(entity < MAX_ENTITIES, "Entity out of range.");
				return m_signatures[entity];
			}

		private:
			std::queue<Entity> m_availableEntities{};
			std::array<Signature, MAX_ENTITIES> m_signatures{};
			uint32_t m_livingEntityCount{};
	};
}

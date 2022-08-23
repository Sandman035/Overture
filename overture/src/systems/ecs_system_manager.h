#pragma once

#include <defines.h>
#include "ecs_types.h"

#include <set>
#include <memory>
#include <unordered_map>
#include <core/asserts.h>

namespace ecs {
	class System {
		public:
			std::set<Entity> m_entities;
	};

	class SystemManager {
		public:
			template<typename T>
			std::shared_ptr<T> registerSystem() {
				const char* typeName = typeid(T).name();
				ASSERT_MSG(m_systems.find(typeName) == m_systems.end(), "Registering system more than once.");
				auto system = std::make_shared<T>();
				m_systems.insert({typeName, system});
				return system;
			}

			template<typename T>
			void setSignature(Signature signature) {
				const char* typeName = typeid(T).name();
				ASSERT_MSG(m_systems.find(typeName) != m_systems.end(), "System used before registered.");
				m_signatures.insert({typeName, signature});
			}

			void entityDestroyed(Entity entity) {
				for (auto const& pair : m_systems) {
					auto const& system = pair.second;
					system->m_entities.erase(entity);
				}
			}

			void entitySignatureChanged(Entity entity, Signature entitySignature) {
				for (auto const& pair : m_systems) {
					auto const& type = pair.first;
					auto const& system = pair.second;
					auto const& system_signature = m_signatures[type];
					if ((entitySignature & system_signature) == system_signature) {
						system->m_entities.insert(entity);
					} else {
						system->m_entities.erase(entity);
					}
				}
			}

		private:
			std::unordered_map<const char*, Signature> m_signatures{};
			std::unordered_map<const char*, std::shared_ptr<System>> m_systems{};
	};
}

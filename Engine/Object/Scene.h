#pragma once
#include "core.h"
#include <vector>
#include <list>

namespace AZ {
	class Scene {
	public:
		void Startup();
		void Shutdown();

		void Update(float dt);
		void Draw(Core::Graphics& graphics);

		void AddActor(class Actor* actor);
		void RemoveActor(class Actor* object);

		template <typename T>
		T* GetActor(){
			T* actor = { nullptr };
			for (Actor* a : m_actors){
				actor = dynamic_cast<T*>(a);
				if (actor) break;
			}

			return actor;
		}

		template <typename T>
		std::vector<T*> GetActors(){
			std::vector<T*> actors;
			for (Actor* a : m_actors){
				T* actor = dynamic_cast<T*>(a);
				if (actor){
					actors.push_back(actor);
				}
			}

			return actors;
		}


	private:
		std::list<class Actor*> m_actors;

	};
}
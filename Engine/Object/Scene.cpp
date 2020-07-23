#include "pch.h"
#include "Scene.h"
#include "Actor.h"

namespace AZ
{
	void Scene::Startup() {
		// nothing
	}

	void Scene::Shutdown() {
		for (Actor* actor : m_actors) {
			delete actor;
		}

		m_actors.clear();
	}

	void Scene::Update(float dt) {
		std::vector<Actor*> actors{ m_actors.begin(), m_actors.end() };

		for (size_t i = 0; i < actors.size(); i++) {
			for (size_t j = i + 1; j < actors.size(); j++) {
				float distance = Vector2::distance(actors[i]->GetTransform().position, actors[j]->GetTransform().position);
				if (distance <= (actors[i]->getRadius() + actors[j]->getRadius())) {
					actors[i]->onCollision(actors[j]);
					actors[j]->onCollision(actors[i]);
				}
			}
		}

		auto iter = m_actors.begin();
		while (iter != m_actors.end()) {
			if ((*iter)->isDestroy()) {
				delete* iter;
				iter = m_actors.erase(iter);
			}
			else {
				iter++;
			}
		}

		for (Actor* actor : m_actors) {
			actor->Update(dt);
		}
	}

	void Scene::Draw(Core::Graphics& graphics)
	{
		for (Actor* actor : m_actors) {
			actor->Draw(graphics);
		}
	}

	void Scene::AddActor(Actor* actor)
	{
		actor->SetScene(this);
		m_actors.push_back(actor);
	}

	void Scene::RemoveActor(Actor* actor)
	{
		std::list<Actor*>::iterator iter = std::find(m_actors.begin(), m_actors.end(), actor);
		if (iter != m_actors.end())
		{
			delete* iter;
			m_actors.erase(iter);
		}
	}
}

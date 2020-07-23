#pragma once
#include "../Math/Transform.h"
#include "../Shape.h"

namespace AZ {
	class Scene;

	class Actor {
	public:
		enum class eType {
			PLAYER,
			ENEMY,
			PROJECTILE
		};
	public:
		Actor() {}
		Actor(const Transform& transform, const Shape& shape) : m_transform{ transform }, m_shape{ shape } {}
		virtual ~Actor() {}

		virtual eType getType() = 0;

		virtual bool Load(const std::string& filename);

		virtual void Update(float dt);
		virtual void Draw(Core::Graphics& graphics);

		virtual void onCollision(Actor* actor) {}

		virtual void Load(std::istream& stream);

		void SetScene(Scene* scene) { m_scene = scene; }
		Transform& GetTransform() { return m_transform; }
		Shape& GetShape() { return m_shape; }
		void setDestroy(bool destroy = true) { m_destroy = destroy; }
		bool isDestroy() { return m_destroy; }
		float getRadius();

	protected:
		bool m_destroy{ false };
		Transform m_transform;
		Shape m_shape;
		Scene* m_scene{ nullptr };
	};
}

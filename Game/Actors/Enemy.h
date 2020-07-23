#pragma once
#include "Object/Actor.h"

class Enemy : public AZ::Actor {
public:
	Enemy() = default;
	virtual ~Enemy() {}

	virtual eType getType() { return eType::ENEMY; }

	virtual bool Load(const std::string& filename) override;
	virtual void Update(float dt) override;

	virtual void onCollision(Actor* actor);

	void setThrust(float thrust) { m_thrust = thrust; }
	void setTarget(Actor* actor) { m_target = actor; }


protected:
	float m_thrust{ -200.0f };
	Actor* m_target{ nullptr };
};

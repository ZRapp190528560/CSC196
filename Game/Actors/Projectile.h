#pragma once
#include "Object/Actor.h"

class Projectile : public AZ::Actor {
public:
	Projectile() = default;
	virtual ~Projectile() {}

	virtual eType getType() { return eType::PROJECTILE; }

	virtual bool Load(const std::string& filename) override;
	virtual void Update(float dt) override;

	void SetThrust(float thrust) { m_thrust = thrust; }

	virtual void onCollision(Actor* actor);

protected:
	float m_thrust{ 200.0f };
	float lifetime{ 3.0f };
};

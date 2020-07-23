#pragma once
#include "Object/Actor.h"

class Player : public AZ::Actor {
public:
	Player() = default;
	virtual ~Player() {}

	virtual eType getType() { return eType::PLAYER; }

	virtual bool Load(const std::string& filename) override;

	virtual void Update(float dt) override;

protected:
	float thrust{ 300.0f };
	float rotationRate{ 270.0f };
	float m_fireRate{ 0.1f };
	float m_fireTimer{ 0.0f };
	AZ::Vector2 velocity;
};
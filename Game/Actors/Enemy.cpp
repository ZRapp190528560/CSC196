#include "Enemy.h"
#include "ParticleSystem.h"
#include <fstream>
#include "Math/Math.h"

bool Enemy::Load(const std::string& filename){
	bool success = false;

	std::ifstream stream(filename);
	if (stream.is_open()) {
		success = true;

		Actor::Load(stream);

		stream >> m_thrust;

		stream.close();
	}

	return false;
}

void Enemy::Update(float dt){
	AZ::Vector2 direction = m_target->GetTransform().position - m_transform.position;

	AZ::Vector2 enemyVelocity = direction.normalized() * m_thrust;
	GetTransform().position += enemyVelocity * dt;

	GetTransform().angle = std::atan2(direction.y, direction.x) + AZ::Math::HALF_PI;

	m_transform.update();
}

void Enemy::onCollision(Actor* actor) {
	if (actor->getType() == eType::PROJECTILE) {
		m_destroy = true;

		AZ::Color colors[] = { AZ::Color::red, AZ::Color::yellow, AZ::Color::white };
		AZ::Color color = colors[rand() % 3];

		g_particleSystem.Create(m_transform.position, 0, 180, 30, color, 1, 100, 200);
	}
}

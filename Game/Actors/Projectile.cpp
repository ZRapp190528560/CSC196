#include "Projectile.h"
#include "ParticleSystem.h"
#include <fstream>
#include "Math/Math.h"

bool Projectile::Load(const std::string& filename){
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

void Projectile::Update(float dt){
	lifetime -= dt;

	m_destroy = (lifetime <= 0);

	AZ::Vector2 direction = AZ::Vector2::rotate(AZ::Vector2::forward, m_transform.angle);
	AZ::Vector2 velocity = direction + m_thrust;
	m_transform.position = m_transform.position + velocity * dt;

	g_particleSystem.Create(m_transform.position, m_transform.angle + AZ::Math::PI, 10, 1, AZ::Color::red, 0.3f, 100, 200);

	m_transform.update();
}


void Projectile::onCollision(Actor* actor) {
	if (actor->getType() == eType::ENEMY) {
		m_destroy = true;
	}
}

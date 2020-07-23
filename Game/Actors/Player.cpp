#include "Player.h"
#include "Math/Math.h"
#include "Projectile.h"
#include "Object/Scene.h"
#include "ParticleSystem.h"
#include <fstream>

bool Player::Load(const std::string& filename){
	bool success = false;

	std::ifstream stream(filename);
	if (stream.is_open()) {
		success = true;

		Actor::Load(stream);

		stream >> thrust;
		stream >> rotationRate;

		stream.close();
	}

	return success;
}

void Player::Update(float dt){
	m_fireTimer += dt;

	if (Core::Input::IsPressed(VK_SPACE) && m_fireTimer >= m_fireRate) {
		m_fireTimer = 0;

		Projectile* projectile = new Projectile;
		projectile->Load("Projectile.txt");
		projectile->GetTransform().position = m_transform.position;
		projectile->GetTransform().angle = m_transform.angle;
		m_scene->AddActor(projectile);
	}

	AZ::Vector2 force{ 0, 0 };
	if (Core::Input::IsPressed('W')) { force = AZ::Vector2::forward * thrust; }
	force = AZ::Vector2::rotate(force, m_transform.angle);
	velocity = velocity + force * dt;
	velocity = velocity * 0.985f;

	m_transform.position = m_transform.position + (velocity * dt);

	if (Core::Input::IsPressed('A')) { m_transform.angle = m_transform.angle - (dt * AZ::Math::THREE_HALF_PI); }
	if (Core::Input::IsPressed('D')) { m_transform.angle = m_transform.angle + (dt * AZ::Math::THREE_HALF_PI); }

	if (m_transform.position.x > 800) m_transform.position.x = 0;
	if (m_transform.position.x < 0) m_transform.position.x = 800;

	if (m_transform.position.y > 600) m_transform.position.y = 0;
	if (m_transform.position.y < 0) m_transform.position.y = 600;

	if (force.lengthsqr() > 0) {
		g_particleSystem.Create(m_transform.position, m_transform.angle + AZ::Math::PI, 20, 1, AZ::Color{ 1, 1, 1 }, 1, 100, 200);
	}

	m_transform.update();
}

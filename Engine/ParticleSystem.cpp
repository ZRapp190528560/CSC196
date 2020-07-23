#include "pch.h"
#include "ParticleSystem.h"
#include "Math/Random.h"
#include "Math/Math.h"
#include "core.h"

AZ::ParticleSystem g_particleSystem;

void AZ::ParticleSystem::startup(){
	m_size = 3000;
	m_particles = new Particle[m_size];
}

void AZ::ParticleSystem::shutdown(){
	delete[] m_particles;
}

void AZ::ParticleSystem::Update(float dt){
	for (size_t i = 0; i < m_size; i++) {
		Particle* p = &m_particles[i];
		if (p->active) {
			p->lifetime = p->lifetime - dt;
			p->active = (p->lifetime > 0);

			p->prevPosition = p->position;
			p->position = p->position + (p->velocity * dt);
			p->velocity = p->velocity * p->damping;
		}
	}
}

void AZ::ParticleSystem::Draw(Core::Graphics graphics){
	for (size_t i = 0; i < m_size; i++) {
		Particle* p = &m_particles[i];
		if (p->active) {
			graphics.SetColor(p->color);
			graphics.DrawLine(p->position.x, p->position.y, p->prevPosition.x, p->prevPosition.y);
		}
	}
}

void AZ::ParticleSystem::Create(const Vector2& position, float angle, float angleRange, float count, Color color, float lifetime, float speedMin, float speedMax){
	for (size_t i = 0; i < count; i++) {
		Particle* p = getFreeParticle();
		if (p) {
			p->active = true;
			p->lifetime = lifetime;
			p->position = position;
			p->prevPosition = position;
			p->color = color;

			float angleRandom = AZ::Math::deg_to_rad(AZ::random(-angleRange, angleRange));
			Vector2 direction = Vector2::rotate(Vector2::forward, angle + angleRandom);
			p->velocity = direction * AZ::random(speedMin, speedMax);
		}
	}
}

AZ::Particle* AZ::ParticleSystem::getFreeParticle() {
	Particle* freeParticle{ nullptr };

	for (size_t i = 0; i < m_size; i++) {
		Particle* p = &m_particles[i];
		if (p->active == false) {
			freeParticle = p;
			break;
		}
	}
	return freeParticle;
}
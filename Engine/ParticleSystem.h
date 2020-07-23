#pragma once
#include "Object/Particle.h"
#include "core.h"

namespace AZ {
	class ParticleSystem {
	public:
		void startup();
		void shutdown();

		void Update(float dt);
		void Draw(Core::Graphics graphics);

		void Create(const Vector2& position, float angle, float angleRange, float count, Color color, float lifetime, float speedMin, float speedMax);
	protected:
		Particle* getFreeParticle();

	protected:
		Particle* m_particles;
		size_t m_size;
	};
}

extern AZ::ParticleSystem g_particleSystem;
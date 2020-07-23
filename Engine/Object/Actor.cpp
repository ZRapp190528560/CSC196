#include "pch.h"
#include "Actor.h"
#include <fstream>

namespace AZ {
	bool AZ::Actor::Load(const std::string& filename) {
		bool success = false;

		std::ifstream stream(filename);
		if (stream.is_open()) {
			success = true;

			Load(stream);

			stream.close();
		}

		return success;
	}

	void AZ::Actor::Update(float dt) {
	}

	void AZ::Actor::Draw(Core::Graphics& graphics) {
		m_shape.Draw(graphics, m_transform);
	}

	void AZ::Actor::Load(std::istream& stream) {
		stream >> m_transform;

		std::string shapeName;
		stream >> shapeName;
		m_shape.Load(shapeName);
	}

	float Actor::getRadius() {
		return m_shape.getRadius() * m_transform.scale;
	}
}
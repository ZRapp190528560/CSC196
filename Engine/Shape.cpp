#include "pch.h"
#include "Shape.h"
#include <fstream>

void AZ::Shape::Draw(Core::Graphics& Graphics, AZ::Vector2 position, float angle, float scale) {
	Graphics.SetColor(m_color);
	//graphics.DrawLine(static_cast<float>(rand() % 800), static_cast<float>(rand() % 600), static_cast<float>(rand() % 800), static_cast<float>(rand() % 600));
	for (size_t i = 0; i < m_points.size() - 1; i++) {
		AZ::Vector2 p1 = (m_points[i]);
		AZ::Vector2 p2 = (m_points[i + 1]);

		p1 = p1 * scale;
		p2 = p2 * scale;

		p1 = AZ::Vector2::rotate(p1, angle);
		p2 = AZ::Vector2::rotate(p2, angle);

		p1 = p1 + position;
		p2 = p2 + position;

		Graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
	}
}

void AZ::Shape::Draw(Core::Graphics& Graphics, const Transform& transform){
	Draw(Graphics, transform.position, transform.angle, transform.scale);
}

bool AZ::Shape::Load(const std::string& filename) {
	bool success = false;

	std::ifstream stream(filename);
	if (stream.is_open()) {
		success = true;

		stream >> m_color;

		while (!stream.eof()) {
			Vector2 point;
			stream >> point;

			if (!stream.eof()) {
				m_points.push_back(point);
			}
		}

		stream.close();
	}

	return success;
}
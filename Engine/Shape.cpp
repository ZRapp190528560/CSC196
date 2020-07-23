#include "pch.h"
#include "Shape.h"
#include "Math/Matrix22.h"
#include "Math/Matrix33.h"
#include <fstream>

void AZ::Shape::Draw(Core::Graphics& Graphics, AZ::Vector2 position, float angle, float scale) {
	Graphics.SetColor(m_color);

	matrix33 mxScale;
	mxScale.scale(scale);

	matrix33 mxRotate;
	mxRotate.rotate(angle);

	matrix33 mxTranslate;
	mxTranslate.translate(position);

	matrix33 mx = mxScale * mxRotate * mxTranslate;

	//graphics.DrawLine(static_cast<float>(rand() % 800), static_cast<float>(rand() % 600), static_cast<float>(rand() % 800), static_cast<float>(rand() % 600));
	for (size_t i = 0; i < m_points.size() - 1; i++) {
		AZ::Vector2 p1 = (m_points[i]);
		AZ::Vector2 p2 = (m_points[i + 1]);

		p1 = p1 * mx;
		p2 = p2 * mx;

		Graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
	}
}

void AZ::Shape::Draw(Core::Graphics& Graphics, const Transform& transform){
	Graphics.SetColor(m_color);

	for (size_t i = 0; i < m_points.size() - 1; i++) {
		AZ::Vector2 p1 = (m_points[i]);
		AZ::Vector2 p2 = (m_points[i + 1]);

		p1 = p1 * transform.matrix;
		p2 = p2 * transform.matrix;

		Graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
	}
}

bool AZ::Shape::Load(const std::string& filename) {
	bool success = false;

	std::ifstream stream(filename);
	if (stream.is_open()) {
		success = true;

		stream >> m_color;

		std::string line;
		std::getline(stream, line);
		size_t size;
		size = stoi(line);


		for (size_t i = 0; i < size; i++) {
			Vector2 point;
			stream >> point;
			m_points.push_back(point);
		}

		stream.close();
	}
	radius = 0;

	for (size_t i = 0; i < m_points.size(); i++) {
		AZ::Vector2 p1 = (m_points[i]);
		float length = p1.length();
		if (length > radius) radius = length;
	}

	return success;
}
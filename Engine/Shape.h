#pragma once
#include "pch.h"
#include "core.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Math/Transform.h"

namespace AZ {
	class Shape {
	public:
		Shape() {}
		Shape(const std::vector<Vector2>& points, AZ::Vector2 position, const Color& color) : m_points{ points } {}

		bool Load(const std::string& filename);

		void Draw(Core::Graphics& Graphics, AZ::Vector2 position, float angle = 0.0f, float scale = 1.0f);
		void Draw(Core::Graphics& Graphics, const Transform& transform);

		void setColor(Color& color) { m_color = color; }
		const Color& getColor() const { return m_color; }
		float getRadius() { return radius; }

	private:
		std::vector<Vector2> m_points;
		Color m_color;
		float radius;
	};
}
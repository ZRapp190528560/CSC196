#pragma once
#include "Vector2.h"
#include "Math/Matrix33.h"

namespace AZ {
	struct Transform {
		Vector2 position;
		float scale;
		float angle;

		matrix33 matrix;

		Transform() : position(0,0), scale(1), angle(0) {}
		Transform(const Vector2& pos, const float scale = 1, const float angle = 0) : position(pos), scale(scale), angle(angle) {}

		void update();

		friend std::istream& operator >> (std::istream& stream, Transform& t);
	};
}
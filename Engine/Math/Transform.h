#pragma once
#include "Vector2.h"

namespace AZ {
	struct Transform {
		Vector2 position;
		float scale;
		float angle;

		Transform() : position(0,0), scale(1), angle(0) {}
		Transform(const Vector2& pos, const float scale = 1, const float angle = 0) : position(pos), scale(scale), angle(angle) {}

		friend std::istream& operator >> (std::istream& stream, Transform& t);
	};
}
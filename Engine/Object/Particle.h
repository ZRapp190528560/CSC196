#pragma once
#include "Math/Color.h"
#include "Math/Vector2.h"

namespace AZ {
	struct Particle
	{
		Vector2 position;
		Vector2 prevPosition;
		Vector2 velocity;
		Color color;
		float damping{ 0.98f };
		float lifetime;
		bool active{ false };
	};
}
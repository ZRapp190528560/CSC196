#include <iostream>
#include "core.h"
#include <vector>
#include "Math/Math.h"
#include "Math/Random.h"
//#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Math/Transform.h"
#include "Shape.h"
#include "pch.h"

float speed = 300.0f;

AZ::Shape shape;
AZ::Transform transform{ {400, 300}, 4, 0 };

float t{ 0 };

float frametime;
float roundtime{ 0 };
bool gameOver{ false };

DWORD prevTime;
DWORD deltaTime;

bool Update(float dt) {
	DWORD time = GetTickCount();
	deltaTime = time - prevTime;
	prevTime = time;

	t = t + (dt) * 5.0f;

	frametime = dt;
	roundtime += dt;

	//if (roundtime >= 5.0f) { gameOver = true; }

	//if (gameOver) { dt = dt * 0.25f; }

	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	int x;
	int y;
	Core::Input::GetMousePos(x, y);

	/*AZ::Vector2 target = AZ::Vector2{ x, y };
	AZ::Vector2 direction = target - position;*/

	//position += direction.normalized() * speed;

	if (Core::Input::IsPressed('A')) { transform.angle = transform.angle - (dt * AZ::Math::THREE_HALF_PI); }
	if (Core::Input::IsPressed('D')) { transform.angle = transform.angle + (dt * AZ::Math::THREE_HALF_PI); }

	transform.position = AZ::Math::Clamp(transform.position, { 0,0 }, { 800,600 });

	/*if (Core::Input::IsPressed('A')) { position += AZ::Vector2{ -1.0f, 0.0f } * speed * dt; }
	if (Core::Input::IsPressed('D')) { position += AZ::Vector2{ 1.0f, 0.0f } * speed * dt; }
	if (Core::Input::IsPressed('W')) { position += AZ::Vector2{ 0.0f, -1.0f } *speed * dt; }
	if (Core::Input::IsPressed('S')) { position += AZ::Vector2{ 0.0f, 1.0f } *speed * dt; }*/

	/*for (AZ::Vector2& point : points) {
		point = { AZ::random(-10.0f, 10.0f), AZ::random(-10.0f, 10.0f) };
	}*/

	AZ::Vector2 force;
	if (Core::Input::IsPressed('W')) { force = AZ::Vector2::forward * speed * dt; }
	AZ::Vector2 direction = force;
	direction = AZ::Vector2::rotate(direction, transform.angle);
	transform.position = transform.position + direction;

	return quit;
}

void Draw(Core::Graphics& graphics){
	graphics.DrawString(10, 10, std::to_string(frametime).c_str());
	graphics.DrawString(10, 20, std::to_string(1.0f/frametime).c_str());
	graphics.DrawString(10, 30, std::to_string(deltaTime).c_str());
	
	float v = (std::sin(t) + 1dddd) * 0.5f;

	AZ::Color c = AZ::Math::Lerp(AZ::Color{ 1, 1, 0 }, AZ::Color{ 1, 0, 1 }, v);
	graphics.SetColor(c);

	AZ::Vector2 pos = AZ::Math::Lerp(AZ::Vector2{ 400, 200 }, AZ::Vector2{ 400, 100 }, v);
	graphics.DrawString(pos.x, pos.y, "Never gonna give you up");

	if (gameOver) graphics.DrawString(400, 300, "Game Over");

	shape.Draw(graphics, transform);
}

int main(){
	DWORD ticks = GetTickCount();
	std::cout << ticks << std::endl;
	prevTime = GetTickCount();

	shape.Load("Ship.txt.txt");

	char name[] = "Anastasia";
	Core::Init(name, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();
}
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

const size_t NUM_POINTS = 40;
float speed = 200.0f;

std::vector<AZ::Vector2> points = { { 0, -3 }, { 3, 3 }, { 0, 1 }, { -3, 3 }, { 0, -3 } };
AZ::Color color { 1, 0.55f, 0.73f };
AZ::Shape shape;

AZ::Transform transform{ {400, 300}, 4, 0 };

float frametime;
float roundtime{ 0 };
bool gameOver{ false };

DWORD prevTime;
DWORD deltaTime;

bool Update(float dt) {
	DWORD time = GetTickCount();
	deltaTime = time - prevTime;
	prevTime = time;

	frametime = dt;
	roundtime += dt;

	if (roundtime >= 5.0f) { gameOver = true; }

	if (gameOver) { dt = dt * 0.25f; }

	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	int x;
	int y;
	Core::Input::GetMousePos(x, y);

	/*AZ::Vector2 target = AZ::Vector2{ x, y };
	AZ::Vector2 direction = target - position;*/

	//position += direction.normalized() * speed;

	if (Core::Input::IsPressed('A')) { transform.angle = transform.angle - dt * 5; }
	if (Core::Input::IsPressed('D')) { transform.angle = transform.angle + dt * 5; }

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
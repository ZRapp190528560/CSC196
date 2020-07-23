#include <iostream>
#include "core.h"
#include "Math/Math.h"
#include "Math/Color.h"
#include "Math/Random.h"
#include "Object/Actor.h"
#include "Object/Scene.h"
#include "ParticleSystem.h"
#include "pch.h"
#include "Actors/Player.h"
#include "Actors/Enemy.h"

AZ::Scene scene;

float t{ 0 };

float spawnTime{ 0 };

bool Update(float dt) {
	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	spawnTime += dt;

	if (spawnTime > 3) {
		spawnTime = 0;

		Enemy* enemy = new Enemy();
		enemy->Load("Enemy.txt");
		enemy->setTarget(scene.GetActor<Player>());
		enemy->GetTransform().position = { AZ::random(600, 0), AZ::random(800,0) };
		scene.AddActor(enemy);
	}

	Player* player = scene.GetActor<Player>();

	if (Core::Input::IsPressed(Core::Input::BUTTON_LEFT)) {
		int x, y;
		Core::Input::GetMousePos(x, y);

		AZ::Color colors[] = { AZ::Color::red, AZ::Color::yellow, AZ::Color::white };
		AZ::Color color = colors[rand() % 3];

		g_particleSystem.Create(AZ::Vector2{x, y}, 0, 180, 30, color, 1, 100, 200);
	}

	g_particleSystem.Update(dt);
	scene.Update(dt);
	return quit;
}

void Draw(Core::Graphics& graphics){
	float v = (std::sin(t) + 1) * 0.5f;

	AZ::Color c = AZ::Math::Lerp(AZ::Color{ 1, 1, 0 }, AZ::Color{ 1, 0, 1 }, v);
	graphics.SetColor(c);

	g_particleSystem.Draw(graphics);
	scene.Draw(graphics);
}

int main(){
	g_particleSystem.startup();
	scene.Startup();

	Player* player = new Player();
	player->Load("Player.txt");
	scene.AddActor(player);

	for (size_t i = 0; i < 5; i++) {
		Enemy* enemy = new Enemy();
		enemy->Load("Enemy.txt");
		enemy->setTarget(scene.GetActor<Player>());
		enemy->GetTransform().position = { AZ::random(600, 0), AZ::random(800,0) };
		scene.AddActor(enemy);
	}

	char name[] = "Anastasia";
	Core::Init(name, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();
	scene.Shutdown();
	g_particleSystem.shutdown();
}
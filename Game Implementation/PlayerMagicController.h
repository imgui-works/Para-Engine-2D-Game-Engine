#pragma once
#include <Component.h>
#include <GameObject.h>
#include <Game.h>
#include <imgui.h>
class PlayerMagicController : public Component
{
public:
	PlayerMagicController() {};
	~PlayerMagicController() {};
	virtual void start()
	{
		activeTransform = GameObject::getGameObjectWithName("Lola")->getComponent<Transform>();
		rotOffset = 0.0f;
		shouldDoCircleMotion = true;
	}
	virtual void update()
	{
		activeTransform->rotation = rotOffset;
		float deltaTime = Game::getDeltaTime();
		if (shouldDoCircleMotion)
		{
			activeTransform->position.x = activeTransform->position.x + (glm::sin(rotOffset) * 0.6f);
			activeTransform->position.y = activeTransform->position.y + (glm::cos(rotOffset) * 0.6f);
			rotOffset += deltaTime * 8.0f;
		}
		if (Game::isKeyPressed(Key::W))
			activeTransform->position.y += 700.0f * deltaTime;
		if (Game::isKeyPressed(Key::S))
			activeTransform->position.y -= 700.0f * deltaTime;
		if (Game::isKeyPressed(Key::A))
			activeTransform->position.x -= 700.0f * deltaTime;
		if (Game::isKeyPressed(Key::D))
			activeTransform->position.x += 700.0f * deltaTime;
		if (Game::isKeyPressed(Key::Q))
			shouldDoCircleMotion = true;
		if (Game::isKeyReleased(Key::Q))
			shouldDoCircleMotion = false;

		ImGui::Text("Application average %.4f ms/frame (%.2f FPS)", deltaTime, 1.0f / deltaTime);

	}
private:
	Transform* activeTransform;
	float rotOffset;
	bool shouldDoCircleMotion;
};
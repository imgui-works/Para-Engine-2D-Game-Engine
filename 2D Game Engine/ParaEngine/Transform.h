#pragma once
#include <GLM\glm.hpp>
#include "Component.h"

class Transform : public Component
{
public:
	Transform(const glm::vec2& position, float rotation, const glm::vec2& scale) noexcept;
	Transform() noexcept;
	Transform(const Transform& copy) noexcept;
	const glm::mat4& getMatrix()const;
	virtual void start();
	virtual void update();
	void setPosition(const glm::vec2& position);
	void setPosition(float xCoord, float yCoord);
	const glm::mat4 getWorldSpaceTransform();
	void setX(float xValue);
	void setY(float yValue);
	void setRotation(float rotation);
	void setScale(const glm::vec2& scale);
	const glm::vec2& getPosition()const noexcept;
	float getRotation()const noexcept;
	const glm::vec2& getScale()const noexcept;
	void setParent(Transform * parentTransform);
	const Transform* getParent();
	void addChild(Transform* child);
	bool operator==(const Transform& transform)const noexcept;
	bool operator!=(const Transform& transform)const noexcept;
private:
	glm::mat4 modelMatrix = glm::mat4(1.0);
	glm::vec2 scale = glm::vec2(1.0f, 1.0f);
	glm::vec2 position = glm::vec2(0.0f, 0.0f);
	Transform* parent = nullptr;
	std::vector<Transform *> children;
	float rotation = 0.0f;
	bool needsUpdate = true;
	void setModelMatrix();
};
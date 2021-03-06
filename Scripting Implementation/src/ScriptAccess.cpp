#include <iostream>
#include <chaiscript\chaiscript.hpp>
#include <chaiscript\chaiscript_stdlib.hpp>
#include <ParaEngine/Game.h>
#include <GLM\glm.hpp>
#include <ParaEngine/TextureLoader.h>
#include <ParaEngine/AudioManager.h>
#include <ParaEngine/InputData.h>
#include <ParaEngine/Sprite.h>

Camera* CreateCamera(float width, float height);
Sprite* CreateSprite(unsigned int width, unsigned int height);
void ConsoleOutput(const std::string & str);
void SetClearColour(float r, float g, float b);
void AddCameraToGameObject(GameObject* gameObj, Camera* camera);
void AddSpriteToGameObject(GameObject* gameObj, Sprite* sprite);
void SetUpdateFunction(std::function<void()> update);
bool IsKeyPressed(char key);
float MathFuncSin(float radian);
float MathFuncCos(float radian);
float MathFuncAbs(float value);
float MathFuncPow(float value, float power);
float MathFuncSqrt(float value);

int main(int argc, char* argv[])
{
	chaiscript::ChaiScript chai(chaiscript::Std_Lib::library());
	//Misc
	chai.add(chaiscript::fun(&AddSpriteToGameObject), "AddSprite");
	chai.add(chaiscript::fun(&AddCameraToGameObject), "AddCamera");
	chai.add(chaiscript::fun(&SetUpdateFunction), "SetUpdateFunction");
	chai.add(chaiscript::fun(&IsKeyPressed), "IsKeyPressed");

	//Debug
	chai.add(chaiscript::fun(&ConsoleOutput), "ConsoleOutput");

	//Math Functions
	chai.add(chaiscript::fun(&MathFuncSin), "Sin");
	chai.add(chaiscript::fun(&MathFuncCos), "Cos");
	chai.add(chaiscript::fun(&MathFuncAbs), "Abs");
	chai.add(chaiscript::fun(&MathFuncPow), "Pow");
	chai.add(chaiscript::fun(&MathFuncSqrt), "Sqrt");

	//Game class static functions
	chai.add(chaiscript::fun(&Game::isKeyPressed), "IsKeyPressed");
	chai.add(chaiscript::fun(&Game::setUpEngine), "SetUpEngine");
	chai.add(chaiscript::fun(&Game::cleanUp), "CleanUp");
	chai.add(chaiscript::fun(&Game::addScene), "AddScene");
	chai.add(chaiscript::fun(&Game::startScene), "StartScene");
	chai.add(chaiscript::fun(&Game::setCursor), "SetCursorImage");
	chai.add(chaiscript::fun(&Game::lockCursor), "LockCursor");
	chai.add(chaiscript::fun(&Game::getTimeSinceStartUp), "TimeSinceStartUp");
	chai.add(chaiscript::fun(&Game::getDeltaTime), "DeltaTime");
	chai.add(chaiscript::fun(&Game::setVsync), "SetVsync");
	chai.add(chaiscript::fun(&SetClearColour), "SetClearColour");

	//Resource managers
	chai.add(chaiscript::fun(&TextureManager::loadTextureFromFile), "LoadTextureFromFile");
	chai.add(chaiscript::fun(&TextureManager::getTextureIdFromReference), "GetTextureFromReference");
	chai.add(chaiscript::fun(&AudioManager::loadAudioFromFile), "LoadAudioFromFile");

	//Game object
	chai.add(chaiscript::user_type<GameObject>(), "GameObject");
	chai.add(chaiscript::fun(&GameObject::getName), "GetName");
	chai.add(chaiscript::fun(&GameObject::createGameObject), "CreateGameObject");
	chai.add(chaiscript::fun(&GameObject::deleteGameObjectWithName), "DeleteGameObject");
	chai.add(chaiscript::fun(&GameObject::getLayerOrder), "GetLayerOrder");
	chai.add(chaiscript::fun(&GameObject::setLayerOrder), "SetLayerOrder");
	chai.add(chaiscript::fun(&GameObject::addComponent), "AddComponent");
	chai.add(chaiscript::fun(&GameObject::getComponent<Transform>), "GetComponentTransform");

	//Sprite component
	chai.add(chaiscript::user_type<Sprite>(), "Sprite");
	chai.add(chaiscript::constructor<Sprite()>(), "Sprite");
	chai.add(chaiscript::fun(&CreateSprite), "CreateSprite");
	chai.add(chaiscript::fun(&Sprite::init), "Init");
	chai.add(chaiscript::fun(&Sprite::setTextureID), "SetTextureID");
	chai.add(chaiscript::fun(&Sprite::getTextureID), "GetTextureID");
	chai.add(chaiscript::fun(&Sprite::getDimensions), "GetDimensions");
	chai.add(chaiscript::fun<void, Sprite, float, float>(&Sprite::setDimension), "SetDimension");

	//Camera component
	chai.add(chaiscript::user_type<Camera>(), "Camera");
	chai.add(chaiscript::constructor<Camera()>(), "Camera");
	chai.add(chaiscript::fun(&CreateCamera), "CreateCamera");
	chai.add(chaiscript::fun<void, Camera, float, float>(&Camera::init), "Init");
	chai.add(chaiscript::fun(&Camera::setScale), "SetScale");

	chai.add(chaiscript::user_type<glm::vec2>(), "Vec2");
	chai.add(chaiscript::constructor<glm::vec2()>(), "Vec2");
	chai.add(chaiscript::fun(&glm::vec2::x), "x");
	chai.add(chaiscript::fun(&glm::vec2::y), "y");

	chai.add(chaiscript::user_type<glm::vec3>(), "Vec3");
	chai.add(chaiscript::constructor<glm::vec3()>(), "Vec3");
	chai.add(chaiscript::fun(&glm::vec3::x), "x");
	chai.add(chaiscript::fun(&glm::vec3::y), "y");
	chai.add(chaiscript::fun(&glm::vec3::z), "z");

	//Transform component
	chai.add(chaiscript::user_type<Transform>(), "Transform");
	chai.add(chaiscript::constructor<Transform()>(), "Transform");
	chai.add(chaiscript::constructor<Transform(const Transform &)>(), "Transform");
	chai.add(chaiscript::fun(&Transform::setX), "SetX");
	chai.add(chaiscript::fun(&Transform::setY), "SetY");
	chai.add(chaiscript::fun(&Transform::setScale), "SetScale");
	chai.add(chaiscript::fun(&Transform::getPosition), "GetPosition");
	chai.add(chaiscript::fun<void, Transform, float, float>(&Transform::setPosition), "SetPosition");
	chai.add(chaiscript::fun(&Transform::setParent), "SetParent");
	chai.add(chaiscript::fun(&Transform::getParent), "GetParent");
	chai.add(chaiscript::fun(&Transform::addChild), "AddChild");

	chai.eval_file("Test Resources\\Chai scripts\\gameData.chai");
	chai.eval("CleanUp();");
	return 0;
}

void ConsoleOutput(const std::string & str)
{
	std::cout << str;
}

void SetClearColour(float r, float g, float b)
{
	Game::setClearColour(glm::vec3(r, g, b));
}

void AddSpriteToGameObject(GameObject* gameObj, Sprite* sprite)
{
	gameObj->addComponent(sprite);
}

void SetUpdateFunction(std::function<void()> update)
{
	Game::scriptedUpdateFunction = update;
}

bool IsKeyPressed(char key)
{
	return Game::isKeyPressed((Key)((int)key));
}

float MathFuncSin(float radian)
{
	return glm::sin(radian);
}

float MathFuncCos(float radian)
{
	return glm::cos(radian);
}

float MathFuncAbs(float value)
{
	return glm::abs(value);
}

float MathFuncPow(float value, float power)
{
	return glm::pow(value, power);
}

float MathFuncSqrt(float value)
{
	return glm::sqrt(value);
}

void AddCameraToGameObject(GameObject* gameObj, Camera* camera)
{
	gameObj->addComponent(camera);
}

Sprite* CreateSprite(unsigned int width, unsigned int height)
{
	Sprite* sp = new Sprite;
	sp->init(width, height);
	return sp;
}

Camera* CreateCamera(float width, float height)
{
	Camera* camera = new Camera;
	camera->init(glm::vec2(width, height));
	return camera;
}
#include "Game.h"
#include "GameObject.h"
#include <random>

Game::Game(unsigned int screenWidth, unsigned int screenHeight, std::string title)
{
	world = std::make_unique<b2World>(b2Vec2(0, -9.81));
	std::mt19937 randGenerator;

	std::uniform_real_distribution<float> x1Pos(-400, 400);
	std::uniform_real_distribution<float> y1Pos(-420, 420);

	glfwInit();
	window = glfwCreateWindow(screenWidth, screenHeight, title.c_str(), NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	GLenum err = glewInit();
	if (GLEW_OK != err)
		std::cout << "Error: %s\n" << glewGetErrorString(err);
	else
		std::cout << " Glew initialsed" << std::endl;
}

void Game::update(void(*updateFunc)())
{
	camera.init(glm::vec2(600, 600));

	GameObject gameObj2(world.get(), glm::vec2(0, 240), glm::vec2(50, 50), b2BodyType::b2_dynamicBody);
	GameObject gameObj1(world.get(), glm::vec2(0, 200), glm::vec2(50, 50), b2BodyType::b2_dynamicBody);
	//Ground
	GameObject ground(world.get(), glm::vec2(0, 120), glm::vec2(50, 50), b2BodyType::b2_staticBody);

	ShaderProgram shaderProgram;
	shaderProgram.compileShaders("F:\\Visual Studio 2017\\Projects\\2D Game Engine\\Debug\\spriteBase.vs", "F:\\Visual Studio 2017\\Projects\\2D Game Engine\\Debug\\spriteBase.fs");
	shaderProgram.addAttribute("vertexPosition");
	shaderProgram.linkShaders();
	unsigned int texVal1 = TextureLoader::loadTextureFromFile("F:\\Visual Studio 2017\\Projects\\2D Game Engine\\Debug\\asteroid.png", false);
	while (!glfwWindowShouldClose(window))
	{
		std::chrono::steady_clock::time_point start = clockTime.now();
		glClear(GL_COLOR_BUFFER_BIT);
		processInput(window);
		camera.update();
		//updateFunc();

		std::chrono::duration<float> frameTime = clockTime.now() - start;
		world->Step(frameTime.count() * 10, 5, 6);
		shaderProgram.use();
		glBindTexture(GL_TEXTURE_2D, texVal1);
		GLint textureLocation = shaderProgram.getUniformLocation("textureOne");

		GLint uniformProjectionMatrixLocation = shaderProgram.getUniformLocation("projection");
		glm::mat4 cameraMatrix = camera.getOrthoMatrix();
		glUniformMatrix4fv(uniformProjectionMatrixLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));
		glUniform1i(textureLocation, 0);

		gameObj1.drawObject(shaderProgram);
		gameObj2.drawObject(shaderProgram);
		ground.drawObject(shaderProgram);

		shaderProgram.unuse();
		glBindTexture(GL_TEXTURE_2D, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return;
}

void Game::processInput(GLFWwindow * window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		world->SetGravity(b2Vec2(0, 9.81));
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		world->SetGravity(b2Vec2(0, -9.81));
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
	{
		for (int i = 0; i < circles.size(); i++)
			circles[i].getBody()->ApplyForce(b2Vec2(0, 1500), circles[i].getBody()->GetPosition(), true);
	}
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
	{
		for (int i = 0; i < boxes.size(); i++)
			boxes[i].getBody()->ApplyForce(b2Vec2(0, 800), boxes[i].getBody()->GetPosition(), true);
	}
	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
		camera.setPosition(camera.getPosition() + glm::vec2(0, 1.0f));
	else if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
		camera.setPosition(camera.getPosition() + glm::vec2(0, -1.0f));
	else if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
		camera.setPosition(camera.getPosition() + glm::vec2(-1.0f, 0));
	else if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		camera.setPosition(camera.getPosition() + glm::vec2(1.0f, 0));
}

Game::~Game()
{
}

void Game::framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-100, 100, -100, 100, 0.1, -10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

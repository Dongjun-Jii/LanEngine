#define LOG_MIN_LEVEL 1
#define USE_CONSOLE
#include <LanEngine.h>
#include <Component/SquareComponent.h>
#include <Component/TransformComponent.h>
#include <Component/SpriteRenderer.h>

using namespace Lan;

class TestObject : public Object
{
public:
	TestObject()
	{
		addComponent(*(new SquareComponent({ 1,1 })));
		addComponent(*(new SpriteRenderer("test")));
	}
protected:
	virtual void onUpdate(Context& context)
	{
		if (Input::getInstance().isKeyDown('A'))
		{
			getTransformComponent().angle += 1.0f;
		}

		if (Input::getInstance().isKeyPressed('B'))
		{
			getTransformComponent().position.x += 0.25f;
		}

		if (Input::getInstance().isKeyPressed('C'))
		{
			getTransformComponent().size.x += 0.25f;
		}
	}
};

class TestGame : public BaseGame
{
public:

protected:
	virtual void onInitialize()
	{
		ResourceManager::getInstance().loadResource("test");
	}

	virtual void onUpdate(Context& context)
	{

	}

	virtual void onDraw()
	{

	}

	virtual void onDestroy()
	{

	}
};

class TestScene : public Scene
{
public:
	TestScene()
	{
		addObject<TestObject>();
	}
protected:
	virtual void onUpdate(Context& context)
	{
		if (Input::getInstance().isButtonDown(MouseButton::Left))
		{
			LOG(LogLevel::Debug, "마우스 클릭함");
		}
	}
};



int CALLBACK WinMain(HINSTANCE instanceHandle, HINSTANCE prevHandle, LPSTR cmdString, int show)
{
	TestGame game;
	Lan::LanEngine::createInstance();
	Lan::LanEngine& lan = Lan::LanEngine::getInstance();

	lan.initialize(instanceHandle, { 800 , 600 }, game);

	SceneManager::getInstance().addScene<TestScene>("Test");

	SceneManager::getInstance().setCurrentScene("Test");

	lan.run();

	return 0;
}
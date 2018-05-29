#define LOG_MIN_LEVEL 1
#define USE_CONSOLE
#include <LanEngine.h>
#include <Component/Square.h>
#include <Component/Transform.h>
#include <Component/SpriteRenderer.h>
#include <Component/Camera.h>

using namespace Lan;

class TestObject : public Object
{
public:
	TestObject(int z, fvec2 pos)
	{
		addComponent<Square>(fvec2(100, 100));
		addComponent<SpriteRenderer>("test");
		getTransform().position = pos;
	}
protected:
	virtual void onUpdate(Context& context)
	{
		if (Input::getInstance().isKeyDown('A'))
		{
			getTransform().angle += 1.0f;
		}

		if (Input::getInstance().isKeyPressed('B'))
		{
			getTransform().position.x += 0.25f;
		}

		if (Input::getInstance().isKeyPressed('C'))
		{
			getTransform().size.x += 0.25f;
		}
	}
};

class TestCamera : public Object
{
public:
	TestCamera()
	{
		addComponent<Camera>(fvec2(800, 600));
	}
protected:
	virtual void onUpdate(Context& context)
	{
		if (Input::getInstance().isKeyDown(VK_UP))
		{
			getTransform().position.y += 0.3f;
		}
		if (Input::getInstance().isKeyDown(VK_DOWN))
		{
			getTransform().position.y -= 0.3f;
		}
		if (Input::getInstance().isKeyDown(VK_LEFT))
		{
			getTransform().position.x -= 0.3f;
		}
		if (Input::getInstance().isKeyDown(VK_RIGHT))
		{
			getTransform().position.x += 0.3f;
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
		addObject<TestObject>(1, fvec2(0, 0));
		addObject<TestObject>(0, fvec2(0.5f, 0.5f));
		addObject<TestCamera>();
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
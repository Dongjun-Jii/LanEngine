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
	TestObject(fvec3 pos)
	{
		AddComponent<Square>(fvec2(500, 500));
		AddComponent<SpriteRenderer>("test");
		GetTransform().SetTranslation(pos);
	}
protected:
	virtual void OnUpdate(Context& context)
	{
		if (Input::GetInstance().IsKeyDown('A'))
		{
			GetTransform().Rotate(0.1);
		}

		if (Input::GetInstance().IsKeyDown('B'))
		{
			GetTransform().Translate({ 1, 0, 0 });
		}
	}
};

class TestObject2 : public Object
{
public:
	TestObject2(fvec3 pos, Object& obj)
	{
		AddComponent<Square>(fvec2(100, 100));
		AddComponent<SpriteRenderer>("test");
		GetTransform().SetTranslation(pos);
		SetParent(&obj);
		GetTransform().SetTranslation({ 100, 100, -1 }, Space::Local);
	}
protected:
	virtual void OnUpdate(Context& context)
	{
		
	}
};

class TestCamera : public Object
{
public:
	TestCamera()
	{
		AddComponent<Camera>(fvec2(800, 600));
	}
protected:
	virtual void OnUpdate(Context& context)
	{

	}
};

class TestGame : public BaseGame
{
public:

protected:
	virtual void OnInitialize()
	{
		ResourceManager::GetInstance().LoadResource("test");
	}

	virtual void OnUpdate(Context& context)
	{

	}

	virtual void OnDraw()
	{

	}

	virtual void OnDestroy()
	{

	}
};

class TestScene : public Scene
{
public:
	TestScene()
	{
		Object& obj = AddObject<TestObject>(fvec3(0, 0, +1));
		AddObject<TestObject2>(fvec3(0.5f, 0.5f, 0), obj);
		AddObject<TestCamera>();
	}
protected:
	virtual void OnUpdate(Context& context)
	{
		if (Input::GetInstance().IsButtonDown(MouseButton::Left))
		{
			LOG(LogLevel::Debug, "마우스 클릭함");
		}
	}
};



int CALLBACK WinMain(HINSTANCE instanceHandle, HINSTANCE prevHandle, LPSTR cmdString, int show)
{
	TestGame game;
	Lan::LanEngine::CreateInstance();
	Lan::LanEngine& lan = Lan::LanEngine::GetInstance();

	lan.Initialize(instanceHandle, { 800 , 600 }, game);

	SceneManager::GetInstance().AddScene<TestScene>("Test");

	SceneManager::GetInstance().SetCurrentScene("Test");

	lan.Run();

	return 0;
}
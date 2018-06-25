#include "Defines.h"
#include "BaseGame.h"

namespace Lan
{
	void BaseGame::Initialize()
	{
		OnInitialize();
	}

	void BaseGame::Update(Context& context)
	{
		OnUpdate(context);
	}

	void BaseGame::Draw()
	{
		OnDraw();
	}

	void BaseGame::Destroy()
	{
		OnDestroy();
	}
}
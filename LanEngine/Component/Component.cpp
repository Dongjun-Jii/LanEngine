#include "Defines.h"
#include "Component.h"
#include "../Object/Object.h"

namespace Lan
{
	Component::Component(Object* parent) :
		m_Parent(parent)
	{

	}

	Component::~Component()
	{

	}

	Object& Component::GetParent() const
	{
		return *(m_Parent);
	}

	void Component::Update(Context& context)
	{
		OnUpdate(context);
	}

	void Component::Draw()
	{
		OnDraw();
	}
}
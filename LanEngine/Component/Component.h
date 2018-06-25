#pragma once


namespace Lan
{
	struct Context;
	class Object;

	class Component
	{
	public:
		Component(Object* parent);
		virtual ~Component();

		Object& GetParent() const;

	protected:
		virtual void OnUpdate(Context& context) {};
		virtual void OnDraw() {};

	private:
		void Update(Context& context);
		void Draw();

		Object* m_Parent;

		friend Object;
	};
}
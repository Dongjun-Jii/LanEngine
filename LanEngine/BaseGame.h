#pragma once

namespace Lan
{
	struct Context;

	class BaseGame
	{
	public:
		BaseGame() = default;
		virtual ~BaseGame() = default;

		void Initialize();
		void Update(Context& context);
		void Draw();
		void Destroy();

	protected:
		virtual void OnInitialize() = 0;
		virtual void OnUpdate(Context& context) = 0;
		virtual void OnDraw() = 0;
		virtual void OnDestroy() = 0;

	private:
		BaseGame & operator=(const BaseGame&) = delete;
		BaseGame & operator=(BaseGame&&) = delete;
		BaseGame(const BaseGame &) = delete;
		BaseGame(BaseGame &&) = delete;

	};
}
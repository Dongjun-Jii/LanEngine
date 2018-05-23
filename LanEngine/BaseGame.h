#pragma once

namespace Lan
{
	struct Context;

	class BaseGame
	{
	public:
		BaseGame() = default;
		virtual ~BaseGame() = default;

		void initialize();
		void update(Context& context);
		void draw();
		void destroy();

	protected:
		virtual void onInitialize() = 0;
		virtual void onUpdate(Context& context) = 0;
		virtual void onDraw() = 0;
		virtual void onDestroy() = 0;

	private:
		BaseGame & operator=(const BaseGame&) = delete;
		BaseGame & operator=(BaseGame&&) = delete;
		BaseGame(const BaseGame &) = delete;
		BaseGame(BaseGame &&) = delete;

	};
}
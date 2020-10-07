#pragma once

namespace ge2d
{
	class State
	{
	public:
		virtual void Init() = 0;

		virtual void Update(float dt) = 0;
		virtual void Draw(float dt) = 0;

		virtual void Pause() {}
		virtual void Resume() {}
	};
}
#pragma once

namespace	gdl
{
	class Game
	{
	public:
		Game();
		virtual ~Game();

		// Pure virtual function used for Initialize, update the game logic and draw the 3D scene
		virtual bool initialize() = 0;
		virtual bool update() = 0;
		virtual void draw() = 0;
	};
}

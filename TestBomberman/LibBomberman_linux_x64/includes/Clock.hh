#pragma once

namespace	gdl
{
	// Class used to get the elapsed time since the last update
	class Clock
	{
	private:
		unsigned int 		_oldTime;
		unsigned int		_curTime;

	public:
		Clock();
		virtual ~Clock();
		// Do not call this function yourself!
		// It is used by the context to update the current time
		void update(unsigned int currentTime);

		// Function used to get the elapsed time since the last update
		double getElapsed() const;
	};

}

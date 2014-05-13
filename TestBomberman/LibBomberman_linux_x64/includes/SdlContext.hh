#pragma once

#include "SDL.h"
#include <IRenderContext.hh>
#undef main

namespace	gdl
{
	// Class for an Sdl Context
	class SdlContext : public IRenderContext
	{
	protected:
		SDL_Window		*_window;
		SDL_GLContext	_glContext;

	public:
		SdlContext() { }
		virtual ~SdlContext() { }

		// Start the context, create a windows
		virtual bool    start(unsigned int swidth, unsigned int sheight, const std::string &name,
							  int initFlags = SDL_INIT_VIDEO, int windowsFlags = SDL_WINDOW_OPENGL);
		// Update the inputs
		virtual void    updateInputs(Input &input) const;
		// Update the game clock
		virtual void    updateClock(Clock &clock) const;
		// Flush the screen to show what has been drawn
		virtual void 	flush() const;
		// Close the context and the window
		virtual void    stop() const;
	};

}

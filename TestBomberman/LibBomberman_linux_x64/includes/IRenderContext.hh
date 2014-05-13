#pragma once

#include <Input.hh>
#include <Clock.hh>
#include <string>

namespace	gdl
{
	// Interface for a context
	class IRenderContext
	{
	public:
		IRenderContext() { }
		virtual ~IRenderContext() { }

		virtual bool start(unsigned int swidth, unsigned int sheight, const std::string &name, int initFlags, int windowsFlags) = 0;
		virtual void updateInputs(Input &input) const = 0;
		virtual void updateClock(Clock &clock) const = 0;
		virtual void flush() const = 0;
		virtual void stop() const = 0;
	};

}
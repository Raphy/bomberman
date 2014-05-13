#pragma once

#include <AShader.hh>

namespace	gdl
{
	// Class used to compile the shaders basic.fp and basic.vp
	class BasicShader : public AShader
	{
	public:
		BasicShader();
		~BasicShader();

		// Function used to build the shaders once they are loaded
		virtual bool build();
	};

}


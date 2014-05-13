#pragma once

#include <list>
#include <glm/gtc/type_precision.hpp>

namespace	gdl
{
	// Handle the inputs
	class Input
	{
	private:
		std::list<int>	_inputs;
		std::list<int>	_keyInputs;
		glm::ivec2		_mousePosition;
		glm::ivec2		_mouseDelta;
		glm::ivec2		_mouseWheelDelta;

	public:
		Input();
		virtual ~Input();

		// Do not use this functions, they are called by the context to update the inputs
		void 				clearInputs();
		void 				addInput(int input);
		void 				addKeyInput(int input);
		void 				removeKeyInput(int input);
		void 				setMousePosition(glm::ivec2 const &pos, glm::ivec2 const &rel);
		void				setMouseWheel(glm::ivec2 const &delta);

		// Returns the mouse position
		glm::ivec2 const  	&getMousePosition();
		// Returns the mouse movement since the last update
		glm::ivec2 const  	&getMouseDelta();
		// Returns the mouse wheel movement since the last update
		glm::ivec2 const  	&getMouseWheel();

		// Returns true if the input passed as parameter has been detected
		bool 				getInput(int input, bool handled = false);
		// Returns true if the Key passed as parameter is currently pressed
		bool 				getKey(int input, bool handled = false);
		// Returns true if the key passed as parameter as been pressed during the last frame
		bool				getKeyDown(int input, bool handled = false);
		// Returns true if the key passed as parameter as been released during the last frame
		bool				getKeyUp(int input, bool handled = false);
	};

}

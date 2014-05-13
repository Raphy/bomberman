#pragma once

#include <AShader.hh>

#include <glm/glm.hpp>

#include <list>
#include <map>

class FbxModel;

namespace gdl
{

	struct	SSubAnimationDatas;
	struct	SFbxModelHandler;

	// Represents a Fbx, Obj or Collada model
	class Model
	{
	public:
		Model();
		~Model();

		// Pause the current animation
		void		pause(bool pauseAnim);

		// Set the current animation by it's index or by it's name
		bool		setCurrentAnim(int stack, bool loop = true);
		bool		setCurrentAnim(std::string const &name, bool loop = true);

		// Get the number of frame of the currently played animation
		int			getAnimationFrameNumber(int stack);
		int			getAnimationFrameNumber(std::string const &name);

		// Get the time of one animation frame
		float		getFrameDuration();

		// Create a sub animation depending on the name or index of a model animation
		bool		createSubAnim(int stack, std::string const &subAnimName,
								  int frameStart, int frameEnd);
		bool		createSubAnim(std::string const &name, std::string const &subAnimName,
								  int frameStart, int frameEnd);

		// Set the current sub animation
		bool		setCurrentSubAnim(std::string const &name, bool loop = true);

		// Load an Fbx, Obj or collada model
		bool		load(std::string const &path);
		// Draw the current model with the shader and the transform passed as parameter
		// You should pass the input.getElpasedTime() as the deltaTime parameter
		void		draw(AShader &shader, glm::mat4 const &transform, double deltaTime);

	private:
		static std::map<std::string, SFbxModelHandler*>	_meshManager;

		void	removeFromManager();

		FbxModel			*_model;
		SFbxModelHandler	*_modelHandler;
		bool				_loop;
		double				_timeSinceLastFrame;

		std::map<std::string, SSubAnimationDatas>	_subAnims;
	};

}

#ifndef SCENES_MANAGER_H_
# define SCENES_MANAGER_H_

# include "ScenesStack.hh"
# include "IScene.hh"

// Manage scenes : ordering, stacking up,
// creating, destroying ...
// It works with the class ScenesStack.
class ScenesManager {

private:
	ScenesStack m_scenes_stack;

public:
	ScenesManager(IScene *first_scene);
	~ScenesManager();

	// Get the scene in the foreground.
	IScene& getCurrentScene();
	// Check the status of the foreground scene
	// and do something according to it.
	bool applyChanges();
};

#endif // !SCENES_MANAGER_H_
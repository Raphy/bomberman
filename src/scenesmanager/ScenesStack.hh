#ifndef SCENES_STACK_H_
# define SCENES_STACK_H_

# include <stack>

# include "IScene.hh"
# include "SceneFactory.hpp"
# include "SceneId.hh"

// A stack dedicated for scenes.
class ScenesStack {

private:
    std::stack<IScene*> m_stack;

public:
    // Get the foregroud scene.
    IScene* top(); // no const because it returns a no const reference.

    // Instantiate a new Scene with the scene factory,
    // and put it at the foregroud.
    bool push(FunctSceneFactory factory, SceneArguments const& args);

    // Remove the current foreground scene and give
    // the hand back to the previous scene.
    bool pop();

    // Pop until that the closure return true.
    template<typename Funct>
    bool rewind(Funct closure) {
        while (!m_stack.empty() && !closure(m_stack.top()->getId())) {
            m_stack.pop();
        }
        return m_stack.empty() ? false : true;
    }

    // Call the previous "rewind" with a closure which
    // check the scenes ids equality.
    bool rewind(SceneId const& scene_id);
};

#endif // !SCENES_STACK_H_
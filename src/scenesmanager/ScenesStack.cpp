#include "ScenesStack.hh"

IScene* ScenesStack::top() {
    return m_stack.empty() ? NULL : m_stack.top();
}

bool ScenesStack::push(FunctSceneFactory factory, SceneArguments const& args) {
    m_stack.push(factory(args));
    return true;
}

bool ScenesStack::pop() {
    if (m_stack.empty()) {
        return false;
    }
    else {
        m_stack.pop();
        return true;
    }
}

bool ScenesStack::rewind(SceneId const& scene_id) {
    return this->rewind([&](SceneId const& other_id) -> bool {
        return scene_id == other_id ? true : false;
    });
}

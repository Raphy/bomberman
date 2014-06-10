#include "ScenesStack.hh"

ScenesStack::~ScenesStack() {
    while (this->top()) {
        this->pop();
    }
}

IScene* ScenesStack::top() {
    return m_stack.empty() ? NULL : m_stack.top();
}

bool ScenesStack::push(FunctSceneFactory factory, SceneArguments const& args) {
    IScene *scene = factory(args);

    if (!scene->initialize()) {
        delete scene;
        return false;
    }
    else {
        m_stack.push(scene);
        return true;
    }
}

bool ScenesStack::pop() {
    if (m_stack.empty()) {
        return false;
    }
    else {
        delete m_stack.top();
        m_stack.pop();
        return true;
    }
}

bool ScenesStack::rewind(SceneId const& scene_id) {
    return this->rewind([&](SceneId const& other_id) -> bool {
        return scene_id == other_id ? true : false;
    });
}

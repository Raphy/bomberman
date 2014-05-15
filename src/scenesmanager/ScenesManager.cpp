#include <cassert>

#include "ScenesManager.hh"

ScenesManager::ScenesManager(FunctSceneFactory factory, SceneArguments const& args)
    : m_scenes_stack()
{
    if (!m_scenes_stack.push(factory, args)) {
        // TODO: runtime error -> throw excpetion
    }
}

ScenesManager::~ScenesManager() {
}

IScene& ScenesManager::getCurrentScene() {
    IScene* scene = m_scenes_stack.top();

    if (!scene) {
        // TODO: runtime error -> throw exeption
    }
    return *scene;
}

bool ScenesManager::applyChanges() {

    bool retval = true;
    SceneStatus const& status = this->getCurrentScene().getStatus();

    switch (status.getType()) {
        case SceneStatus::None: break;

        case SceneStatus::Back: {
            retval = m_scenes_stack.pop();
            break;
        }

        case SceneStatus::GoOn: {
            SceneStatus::PairFactory const& pf = status.getGoOnFactory();
            assert(pf.first != NULL);
            assert(pf.second != NULL);
            retval = m_scenes_stack.push(pf.first, *pf.second);
            break;
        }

        case SceneStatus::Rewind: {
            retval = m_scenes_stack.rewind(status.getRewindId());
            break;
        }

        default: /* unreachable */ break;
    }
    return retval;
}
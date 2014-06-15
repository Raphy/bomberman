#include <cassert>
#include <string>

#include "ScenesManager.hh"
#include "Exception.hh"

ScenesManager::ScenesManager()
    : m_scenes_stack()
{
}

ScenesManager::~ScenesManager() {
}

IScene& ScenesManager::getCurrentScene() {
    IScene* scene = m_scenes_stack.top();

    if (!scene) {
        throw Exception("the scene statck is empty.");
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
            if (!empty()) {
                getCurrentScene().resume();
            }
            break;
        }

        case SceneStatus::GoOn: {
            SceneStatus::PairFactory const& pf = status.getGoOnFactory();
            assert(pf.first != nullptr);
            assert(pf.second != nullptr);
            retval = m_scenes_stack.push(pf.first, *pf.second);
            break;
        }

        case SceneStatus::Rewind: {
            retval = m_scenes_stack.rewind(status.getRewindId());
            if (!empty()) {
                getCurrentScene().resume();
            }
            break;
        }
        
        case SceneStatus::Leave: {
            while (m_scenes_stack.pop() == true);
            break;
        }

        default: /* unreachable */ break;
    }

    if (!empty()) {
        this->getCurrentScene().consumeStatus();
    }
    return retval;
}
#ifndef SCENE_STATUS_H_
# define SCENE_STATUS_H_

# include <string>
# include <utility>

# include "SceneFactory.hpp"
# include "SceneId.hh"
# include "SceneArguments.hh"

class SceneStatus {

public:
    enum Type {
        None,
        GoOn,
        Back,
        Rewind,
        Leave
    };

    // Encapsule the fonction pointer and the his argument.
    typedef std::pair<FunctSceneFactory, SceneArguments*> PairFactory;

    SceneStatus();
    ~SceneStatus();

    // Get the type of the status.
    Type getType() const;
    // Get the id of the scene to rewind to.
    SceneId const& getRewindId() const;
    // Get the factory of the scene to go on.
    PairFactory const& getGoOnFactory() const;

    // Set the type of the status and fill
    // its corresponding parameters.
    void setNone();
    void setBack();
    void setRewind(SceneId const& scene_id);
    void setGoOn(FunctSceneFactory factory, SceneArguments& args);
    void setLeave() { m_type = Leave; }

private:
    Type m_type;
    SceneId m_rewind_id;
    PairFactory m_go_on_factory;
};

#endif // SCENE_STATUS_H_
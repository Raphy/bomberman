#ifndef ASCENE_H_
# define ASCENE_H_

# include <string>

# include "IScene.hh"
# include "SceneId.hh"
# include "SceneStatus.hh"
# include "SceneArguments.hh"

class AScene : public IScene {

private:
    SceneStatus m_status;
    SceneId m_id;

protected:
    // Help children scenes to manage their status.
    void setStatusNone();
    void setStatusBack();
    void setStatusRewind(std::string const& id_tag);

    template <typename T>
    void setStatusGoOn(SceneArguments& args) {
        m_status.setGoOn(&sceneFactory<T>, args);
    }

public:
    AScene(std::string const& id_tag);

    virtual SceneStatus const& getStatus() const;
    virtual SceneId const& getId() const;
};


#endif // !ASCENE_H_
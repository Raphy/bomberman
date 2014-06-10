#ifndef ASCENE_H_
# define ASCENE_H_

# include <string>

# include "IScene.hh"
# include "SceneId.hh"
# include "SceneStatus.hh"
# include "SceneArguments.hh"
# include "Camera.hh"
# include <map>

class AScene : public IScene {

private:
    SceneStatus m_status;
    SceneId m_id;
    std::map<std::string, Camera*> m_camera;

protected:
    // The constructor is called only in child classes's construtors.
    // It take a string which will be used for the scene id.
    //! Warning: children classes has to take only a
    // "SceneArguments const&" as parameter.
    AScene(std::string const& id_tag);

    // Help children scenes to manage their status.
    void setStatusNone();
    void setStatusBack();
    void setStatusRewind(std::string const& id_tag);

    template <typename T>
    void setStatusGoOn(SceneArguments& args) {
        m_status.setGoOn(&sceneFactory<T>, args);
    }

    // set a Camera
    // managed in metaDraw
    // Each cameras will be considered every game frames
    void addCamera(std::string const& label, Camera *camera) { m_camera.insert(std::pair<std::string, Camera *>(label, camera)); }
    void removeCamera(std::string label);
    
    // return false if the label is not find
    Camera * getCamera(std::string const& label);
    
    
    
public:
    // Do not overload these methods in children.
    virtual SceneStatus const& getStatus() const;
    virtual SceneId const& getId() const;
    virtual bool metaDraw(gdl::AShader& shader, gdl::Clock const& clock);
};


#endif // !ASCENE_H_
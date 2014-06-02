#ifndef ISCENE_H_
# define ISCENE_H_

# include <SdlContext.hh>
# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>
# include <iostream>
# include <OpenGL.hh>
# include <Game.hh>
# include <Clock.hh>
# include <Input.hh>
# include <SdlContext.hh>
# include <Geometry.hh>
# include <Texture.hh>
# include <BasicShader.hh>
# include <Model.hh>

# include "SceneId.hh"
# include "SceneStatus.hh"

// Avoid includes conflicts. 
class SceneStatus;
class SceneId;

class IScene {

public:
    virtual ~IScene() {};

    virtual bool initialize() = 0;
    virtual bool update(gdl::Clock const& clock, gdl::Input& input) = 0;
    virtual bool draw(gdl::AShader& shader, gdl::Clock const& clock) = 0;

    virtual SceneStatus const& getStatus() const = 0;
    virtual SceneId const& getId() const = 0;
};

#endif // !ISCENE_H_
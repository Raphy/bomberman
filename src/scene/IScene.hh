#ifndef ISCENE_H_
# define ISCENE_H_

# include "SceneId.hh"
# include "SceneStatus.hh"

// Avoid includes conflicts. 
class SceneStatus;
class SceneId;

class IScene {

public:
    virtual ~IScene() {};

	virtual bool initialize() = 0;
	virtual bool update() = 0;
	virtual bool draw() = 0;

	virtual SceneStatus const& getStatus() const = 0;
	virtual SceneId const& getId() const = 0;
};

#endif // !ISCENE_H_
#ifndef SCENE_FACTORY_H_
# define SCENE_FACTORY_H_

// Do not import all the headers.
class IScene;
class SceneArguments;

typedef IScene* (*FunctSceneFactory)(SceneArguments const& args);

template <typename T>
IScene* sceneFactory(SceneArguments const& args) {
	return new T(args);
}

#endif // !SCENE_FACTORY_H_
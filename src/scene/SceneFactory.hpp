#ifndef SCENE_FACTORY_H_
# define SCENE_FACTORY_H_

// Do not import all the header.
class IScene;

typedef IScene* (*FunctSceneFactory)(/* args */);

template <typename T>
IScene* sceneFactory(/* args */) {
	return new T();
}

#endif // SCENE_FACTORY_H_
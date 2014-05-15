#ifndef SCENE_ID_H_
# define SCENE_ID_H_

# include <string>

class SceneId {

private:
	std::string m_tag;

public:
	SceneId(std::string const& tag="");
	SceneId(SceneId const& other);
	void operator=(SceneId const& other);
	void operator=(std::string const& tag);

	bool operator==(SceneId const& other) const;
	bool operator!=(SceneId const& other) const;
};

#endif // !SCENE_ID_H_
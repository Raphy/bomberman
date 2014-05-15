#ifndef SCENE_ARGUMENTS_H_
# define SCENE_ARGUMENTS_H_

# include <map>
# include <string>

// A generic data type to store scene constructor
// arguments. It is a map of strings (key and value).
class SceneArguments {

private:
    std::map<std::string, std::string> m_map;

public:
    SceneArguments() {};
    ~SceneArguments() {};

    void set(std::string const& key, std::string const& value);
    // Return an empty string if the key doesn't exist.
    std::string const& get(std::string const& key) const;
};


#endif // !SCENE_ARGUMENTS_H_
#ifndef RESOURCES_PATH_HH_
# define RESOURCES_PATH_HH_

# include <string> 

class ResourcesPath {
private:
    ResourcesPath();
    ResourcesPath(ResourcesPath const&);
    void operator=(ResourcesPath const&);

    static std::string s_root;
    static std::string s_sounds;
    static std::string s_shaders;
    static std::string s_assets;
    static std::string s_scripts_ia;

    static std::string makePath(std::string const& folder, std::string const& file);

public:
    static void setRootDir(std::string const& pathname);
    static std::string const& rootDir();

    static std::string sound(std::string const& file="");
    static std::string shader(std::string const& file="");
    static std::string asset(std::string const& file="");
    static std::string scriptIA(std::string const& file="");
};


#endif // !RESOURCES_PATH_HH_
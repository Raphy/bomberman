#include "ResourcesPath.hh"

std::string ResourcesPath::s_root =  ".";
std::string ResourcesPath::s_sounds = "sounds";
std::string ResourcesPath::s_shaders = "shaders";
std::string ResourcesPath::s_assets = "assets";
std::string ResourcesPath::s_scripts_ia = "ia";

std::string ResourcesPath::makePath(std::string const& folder, std::string const& file) {
    return s_root + "/" + folder + "/" + file;
}

void ResourcesPath::setRootDir(std::string const& pathname) {
    s_root = pathname;
}

std::string const& ResourcesPath::rootDir() {
    return s_root;
}

std::string ResourcesPath::sound(std::string const& file)   {
    return makePath(s_sounds, file); 
}

std::string ResourcesPath::shader(std::string const& file)  {
    return makePath(s_shaders, file); 
}

std::string ResourcesPath::asset(std::string const& file)   {
    return makePath(s_assets, file); 
}

std::string ResourcesPath::scriptIA(std::string const& file){
    return makePath(s_scripts_ia, file); 
}

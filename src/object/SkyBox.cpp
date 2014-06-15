/* 
 * File:   SkyBox.cpp
 * Author: svirch_n
 * 
 * Created on 14 June 2014, 20:53
 */

#include "SkyBox.hh"
#include "ResourcesPath.hh"

std::string const SkyBox::Tag = "skybox";

bool SkyBox::initialize() {     
    return this->setTexture(ResourcesPath::asset("textures/skybox.tga"));
}

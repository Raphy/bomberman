/* 
 * File:   Camera.hh
 * Author: svirch_n
 *
 * Created on 06 June 2014, 14:31
 */

#ifndef CAMERA_HH
#define	CAMERA_HH

# include   "AObject.hh"

class Camera: public AObject {
public:
    // can take the object to follow
    Camera(AObject const* object = nullptr): _follow(object), _lookAt(0,0,0), _offset(0, 0, 0) {}
    virtual ~Camera() {}
    
    virtual bool initialize() { return true; }
    virtual void update(gdl::Clock const& clock, gdl::Input& input);
    virtual void draw(gdl::AShader & shader, gdl::Clock const& clock);
    
    // Define the point to lookAt
    // Do not work if a setFollow object has been set
    void setLookAt(glm::vec3 const& lookAt) { this->_lookAt = lookAt; };
    
    // Define the offset from the follow position and the camera
    void setOffset(glm::vec3 offset) { this->_offset = offset; }
    
    // Force update should only be used in the IScene::metadraw
    void forceUpdate(gdl::AShader &, unsigned int cameraNumber = 1) const;
    
private:

    AObject const*     _follow;
    glm::vec3           _lookAt;
    glm::vec3           _offset;
    glm::vec3           _lastPosition;
    
    void updateCamera(gdl::AShader &, unsigned int cameraNumber = 1) const;
    bool needToMoveCamera() const;
    glm::vec3 getLookAt() const;
    glm::vec3 getPosition() const;
    
};

#endif	/* CAMERA_HH */


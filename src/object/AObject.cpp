#include "AObject.hh"

glm::mat4	AObject::getTransformation()
{
	glm::mat4 transform(1);
	
	/*
	 * With a matrix transform the first calcul is applied at the end
	 * In this case the transformation is scale, rotation and translation
	 */

	transform = glm::translate(transform,_position);
	
	transform = glm::rotate(transform, _rotation.x, glm::vec3(1,0,0));
 transform = glm::rotate(transform, _rotation.y, glm::vec3(0,1,0));
 transform = glm::rotate(transform, _rotation.z, glm::vec3(0,0,1));

 transform = glm::scale(transform,_scale);

 return(transform);
}
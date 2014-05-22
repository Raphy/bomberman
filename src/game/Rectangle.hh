
#ifndef RECTANGLE_HH_
# define RECTANGLE_HH_

#include <glm/glm.hpp>

class Rectangle {

private:
    glm::vec3 m_position;
    glm::vec3 m_scale;

public:
    Rectangle() : m_position(0,0,0), m_scale(0,0,0) {}

    Rectangle(glm::vec3 const& position, glm::vec3 const& scale)
        : m_position(position), m_scale(scale) {}

    Rectangle(double x, double y, double w, double h)
        : m_position(x, y, 0), m_scale(w, h, 0) {}

    glm::vec3 const& getPosition() const { return m_position; }
    glm::vec3 const& getScale() const { return m_scale; }
};


#endif // !RECTANGLE_HH_